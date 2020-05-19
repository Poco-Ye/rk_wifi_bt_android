/*
 * Copyright (C) 2018 Fuzhou Rockchip Electronics Co. Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of The Linux Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    voice_preprocess.c
 * @author  Sun Mingjun <smj@rock-chips.com>
 * @date    2017-05-08
 */

//#define LOG_NDEBUG 0

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <dlfcn.h>  // for dlopen/dlclose
#include <fcntl.h>
#include <string.h>

#include <cutils/log.h>
#include <cutils/properties.h>
#include <cutils/str_parms.h>

#include <speex/speex.h>
#include <speex/speex_preprocess.h>
#include <speex/speex_resampler.h>


#include "voice_preprocess.h"

#define LOG_TAG "voice_process"


#define MAX_BUFFER_SIZE (500 * 1024)
#define PROCESS_BUFFER_SIZE (256)
#define FILE_PATH "/etc/RK_VoicePara.bin"
#define false (0)
#define true  (1)
#define bool  int

//#define ALSA_3A_DEBUG
#ifdef ALSA_3A_DEBUG
FILE *in_capture_debug;
FILE *out_capture_debug;
FILE *in_playback_debug;
FILE *out_playback_debug;
#endif

typedef struct voiceThread_t_ {
    bool            running;
    pthread_t       thread;
    sem_t           sem;
    int             threadStatus;
    pthread_mutex_t queueCapLock;
    pthread_mutex_t queuePlyLock;
    pthread_mutex_t getCapOutLock;
    pthread_mutex_t getPlyOutLock;
} voiceThread_t;

typedef struct rk_voice_api_ {
    int (*init)(char *para);
    void  (*processCapture)(short  *in, short *ref, short *out, int len);
    void  (*processPlayback)(short *in, short *out, int len);
    void  (*deinit)();
} rk_voice_api;


typedef struct rk_voice_handle_ {
    void*   voiceLibHandle;
    rk_voice_api *voiceApi;
    rk_process_api *processApi;
    char*  playBackBuffer;
    char*  captureBuffer;
    char*  outPlayBuffer;
    char*  outCaptureBuffer;
    SpeexResamplerState* speexCapureDownResample;
    SpeexResamplerState* speexCapureUpResample;
    SpeexResamplerState* speexPlaybackDownResample;
    SpeexResamplerState* speexPlaybackUpResample;
    voiceThread_t voice_thread;
    int    playbackBufferSize;
    int    captureBufferSize;
    int    outPlaybackBufferSize;
    int    outCaptureBufferSize;
    int    captureInSamplerate;
    int    processSamplerate;
    int    playbackInSamplerate;
    int    captureInChannels;
    int    processChannels;
    int    playbackInChannels;
    int    processBuffersize;
    int    minPlaybackBuffersize;
    int    minCaptureBuffersize;
} rk_voice_handle;


static rk_voice_handle *voice_handle = NULL;
static int prop_pcm_record = 0;

static void thread_loop(rk_voice_handle* handle);
static void*  thread_start(void* argv);
static void dump_out_data(const void* buffer,size_t bytes, int *size)
{
    static FILE* fd = NULL;
    static int offset = 0;
    if(fd == NULL) {
        fd=fopen("/data/1.pcm","wb+");
        if(fd == NULL) {
            ALOGD("DEBUG open  error =%d ,errno = %d",fd,errno);
            offset = 0;
        }
    }
    fwrite(buffer,bytes,1,fd);
    offset += bytes;
    fflush(fd);
    if(offset >= (*size)*1024*1024) {
        *size = 0;
        fclose(fd);
        offset = 0;
    }
}

static inline rk_voice_handle* getHandle()
{
    return voice_handle;
}


static int start()
{
    rk_voice_handle* voiceHandle = getHandle();

    sem_init(&voice_handle->voice_thread.sem, 0, 1);
    voiceHandle->voice_thread.running = true;

    if (voiceHandle->voice_thread.threadStatus == -1)
        voiceHandle->voice_thread.threadStatus = pthread_create(&voiceHandle->voice_thread.thread, NULL, thread_start, voiceHandle);

    ALOGD("voice process start !, ret = %d", voiceHandle->voice_thread.threadStatus);

    return 0;
}

static int queueCaputureBuffer(void *buf, int size)
{
    rk_voice_handle* voiceHandle = getHandle();

    if (voiceHandle->playbackBufferSize <= 0) {
        ALOGV("not queue capture buffer until playback buffer queued");
        return -1;
    }

    pthread_mutex_lock(&voiceHandle->voice_thread.queueCapLock);
    if (voiceHandle->captureBufferSize + size >= MAX_BUFFER_SIZE) {
        ALOGW("capture buffer size out of range, flush");
        memset(voiceHandle->captureBuffer, 0x00, MAX_BUFFER_SIZE);
        voiceHandle->captureBufferSize = 0;
    }
    memcpy((char *)voiceHandle->captureBuffer + voiceHandle->captureBufferSize, (char *)buf, size);
    voiceHandle->captureBufferSize += size;
    pthread_mutex_unlock(&voiceHandle->voice_thread.queueCapLock);


    if ((voiceHandle->captureBufferSize >= voiceHandle->minCaptureBuffersize)
            && (voiceHandle->playbackBufferSize >= voiceHandle->minPlaybackBuffersize)) {
        sem_post(&voiceHandle->voice_thread.sem);
    }
    return 0;
}

static int queuePlaybackBuffer(void *buf, int size)
{
    rk_voice_handle* voiceHandle = getHandle();

    pthread_mutex_lock(&voiceHandle->voice_thread.queuePlyLock);
    if (voiceHandle->playbackBufferSize + size >= MAX_BUFFER_SIZE) {
        ALOGW("capture buffer size out of range, flush");
        memset(voiceHandle->playBackBuffer, 0x00, MAX_BUFFER_SIZE);
        voiceHandle->playbackBufferSize = 0;
    }
    memcpy((char *)voiceHandle->playBackBuffer+ voiceHandle->playbackBufferSize, (char *)buf, size);
    voiceHandle->playbackBufferSize+= size;
    pthread_mutex_unlock(&voiceHandle->voice_thread.queuePlyLock);

    if ((voiceHandle->captureBufferSize >= voiceHandle->minCaptureBuffersize)
            && (voiceHandle->playbackBufferSize >= voiceHandle->minPlaybackBuffersize)) {
        sem_post(&voiceHandle->voice_thread.sem);
    }
    return 0;
}

static int getCapureBuffer(void *buf, int size)
{
    rk_voice_handle* voiceHandle = getHandle();

    if (voiceHandle->outCaptureBufferSize < size) {
        ALOGW("cannot get caputre buffer currently, try next time");
        return -1;
    }
    pthread_mutex_lock(&voiceHandle->voice_thread.getCapOutLock);
    memcpy((char *)buf, voiceHandle->outCaptureBuffer, size);
    memcpy(voiceHandle->outCaptureBuffer, voiceHandle->outCaptureBuffer+size, MAX_BUFFER_SIZE-size);
    voiceHandle->outCaptureBufferSize -= size;
    pthread_mutex_unlock(&voiceHandle->voice_thread.getCapOutLock);
    return 0;
}

static int getPlaybackBuffer(void *buf, int size)
{
    rk_voice_handle* voiceHandle = getHandle();

    if (voiceHandle->outPlaybackBufferSize < size) {
        ALOGW("cannot get playback buffer currently, try next time");
        return -1;
    }
    pthread_mutex_lock(&voiceHandle->voice_thread.getPlyOutLock);
    memcpy((char *)buf, (char *)voiceHandle->outPlayBuffer, size);
    memcpy((char *)voiceHandle->outPlayBuffer, (char *)voiceHandle->outPlayBuffer+size, MAX_BUFFER_SIZE-size);
    voiceHandle->outPlaybackBufferSize -= size;
    pthread_mutex_unlock(&voiceHandle->voice_thread.getPlyOutLock);

    return 0;
}

static int flush()
{
    rk_voice_handle* voiceHandle = getHandle();

    pthread_mutex_lock(&voiceHandle->voice_thread.queuePlyLock);
    memset((char *)voiceHandle->playBackBuffer, 0x00, MAX_BUFFER_SIZE);
    voiceHandle->playbackBufferSize = 0;
    pthread_mutex_unlock(&voiceHandle->voice_thread.queuePlyLock);

    pthread_mutex_lock(&voiceHandle->voice_thread.queueCapLock);
    memset((char *)voiceHandle->captureBuffer, 0x00, MAX_BUFFER_SIZE);
    voiceHandle->captureBufferSize = 0;
    pthread_mutex_unlock(&voiceHandle->voice_thread.queueCapLock);

    return 0;
}


rk_process_api* rk_voiceprocess_create(int ply_sr, int ply_ch, int cap_sr, int cap_ch)
{
    if (voice_handle != NULL) {
        ALOGW(" voice handle has already opened, return");
        return voice_handle->processApi;
    }

    voice_handle = (rk_voice_handle *)malloc(sizeof(rk_voice_handle));

    if (voice_handle== NULL) {
        ALOGE("voice Handle malloc failed!");
        goto failed;
    }

    voice_handle->voiceLibHandle        = NULL;
    voice_handle->voiceApi              = NULL;
    voice_handle->processApi            = NULL;
    voice_handle->playBackBuffer        = NULL;
    voice_handle->captureBuffer         = NULL;
    voice_handle->speexCapureDownResample   = NULL;
    voice_handle->speexCapureUpResample     = NULL;
    voice_handle->speexPlaybackDownResample = NULL;
    voice_handle->speexPlaybackUpResample   = NULL;
    voice_handle->playbackBufferSize     = 0;
    voice_handle->captureBufferSize      = 0;
    voice_handle->outPlaybackBufferSize  = 0;
    voice_handle->outCaptureBufferSize   = 0;
    voice_handle->captureInSamplerate    = cap_sr;
    voice_handle->processSamplerate      = 16000;
    voice_handle->playbackInSamplerate   = ply_sr;
    voice_handle->captureInChannels      = cap_ch;
    voice_handle->processChannels        = 1;
    voice_handle->playbackInChannels     = ply_ch;

    voice_handle->minPlaybackBuffersize = PROCESS_BUFFER_SIZE * 2 * voice_handle->playbackInSamplerate / voice_handle->processSamplerate * voice_handle->playbackInChannels;
    voice_handle->minCaptureBuffersize = PROCESS_BUFFER_SIZE * 2 * voice_handle->captureInSamplerate / voice_handle->processSamplerate * voice_handle->captureInChannels;

    voice_handle->voice_thread.running = false;
    voice_handle->voice_thread.threadStatus = -1;

    // open the voice process lib
    voice_handle->voiceLibHandle = dlopen("/system/lib/libvoiceprocess.so", RTLD_LAZY);
    if (voice_handle->voiceLibHandle == NULL) {
        ALOGW("dlopen libvoiceprocess lib error!");
        goto failed;
    }
    voice_handle->voiceApi = (rk_voice_api *)malloc(sizeof(rk_voice_api));
    if (voice_handle->voiceApi == NULL) {
        ALOGE("voiceApi malloc error!  return");
        goto failed;
    }

    memset(voice_handle->voiceApi, 0, sizeof(rk_voice_api));

    voice_handle->voiceApi->init = (int (*)(char *))dlsym(voice_handle->voiceLibHandle,
                                   "RK_VOICE_Init");
    voice_handle->voiceApi->processCapture = (void (*)(short  *in,
            short *ref, short *out,
            int len))dlsym(voice_handle->voiceLibHandle,
                           "RK_VOICE_ProcessTx");
    voice_handle->voiceApi->processPlayback = (void (*)(short  *in,
            short *out,
            int len))dlsym(voice_handle->voiceLibHandle,
                           "RK_VOICE_ProcessRx");
    voice_handle->voiceApi->deinit= (void (*)())dlsym(voice_handle->voiceLibHandle,
                                    "RK_VOICE_Destory");

    if ((voice_handle->voiceApi->init == NULL)
            || (voice_handle->voiceApi->processCapture == NULL)
            || (voice_handle->voiceApi->processPlayback == NULL)
            || (voice_handle->voiceApi->deinit == NULL)) {
        ALOGE("dlsym voice process lib failed, return");
        goto failed;
    }

    // init the voice process lib
    int ret = 0;
    ret = voice_handle->voiceApi->init(FILE_PATH);
    ALOGD("voice api init ret = %d", ret);
    if (ret != 0) {
        ALOGE("init %s failed", FILE_PATH);
    }

    // init the processApi interface
    voice_handle->processApi = (rk_process_api *)malloc(sizeof(rk_process_api));
    voice_handle->processApi->start = start;
    voice_handle->processApi->getCapureBuffer = getCapureBuffer;
    voice_handle->processApi->getPlaybackBuffer = getPlaybackBuffer;
    voice_handle->processApi->queuePlaybackBuffer = queuePlaybackBuffer;
    voice_handle->processApi->quueCaputureBuffer = queueCaputureBuffer;
    voice_handle->processApi->flush = flush;

    // malloc process buffers
    voice_handle->playBackBuffer = (char *)malloc(MAX_BUFFER_SIZE);
    voice_handle->captureBuffer = (char *)malloc(MAX_BUFFER_SIZE);
    voice_handle->outPlayBuffer = (char *)malloc(MAX_BUFFER_SIZE);
    voice_handle->outCaptureBuffer = (char *)malloc(MAX_BUFFER_SIZE);

    if ((voice_handle->playBackBuffer == NULL) || (voice_handle->captureBuffer == NULL)
            ||(voice_handle->outPlayBuffer == NULL) || (voice_handle->outCaptureBuffer == NULL)) {
        ALOGE("malloc playback or capure buffer falied!");
        goto failed;
    }

    pthread_mutex_init(&voice_handle->voice_thread.queuePlyLock, NULL);
    pthread_mutex_init(&voice_handle->voice_thread.queueCapLock, NULL);
    pthread_mutex_init(&voice_handle->voice_thread.getCapOutLock, NULL);
    pthread_mutex_init(&voice_handle->voice_thread.getPlyOutLock, NULL);

    if (voice_handle->captureInSamplerate != voice_handle->processSamplerate) {
        voice_handle->speexCapureDownResample = speex_resampler_init(1, voice_handle->captureInSamplerate, voice_handle->processSamplerate, SPEEX_RESAMPLER_QUALITY_DESKTOP, NULL);
        voice_handle->speexCapureUpResample = speex_resampler_init(1, voice_handle->processSamplerate, voice_handle->captureInSamplerate, SPEEX_RESAMPLER_QUALITY_DESKTOP, NULL);
    }

    if (voice_handle->playbackInSamplerate!= voice_handle->processSamplerate) {
        voice_handle->speexPlaybackDownResample = speex_resampler_init(1, voice_handle->playbackInSamplerate, voice_handle->processSamplerate, SPEEX_RESAMPLER_QUALITY_DESKTOP, NULL);
        voice_handle->speexPlaybackUpResample = speex_resampler_init(1, voice_handle->processSamplerate, voice_handle->playbackInSamplerate, SPEEX_RESAMPLER_QUALITY_DESKTOP, NULL);
    }

    ALOGD("voice proceess handle create success!");

    return voice_handle->processApi;

failed :

    rk_voiceprocess_destory();
    ALOGD("voice process handle create failed");
    return NULL;
}


int rk_voiceprocess_destory()
{
    ALOGD("voiceprocess_destory");
    if (voice_handle == NULL) {
        ALOGD("voiceprocess_destory return");
        return 0;
    }
    if (voice_handle->voice_thread.threadStatus >= 0) {
        voice_handle->voice_thread.running = false;
        sem_post(&voice_handle->voice_thread.sem);
        ALOGD("join thread in");
        pthread_join(voice_handle->voice_thread.thread, NULL);
        voice_handle->voice_thread.threadStatus = -1;
        ALOGD("join thread out");

        sem_destroy(&voice_handle->voice_thread.sem);
    }

    if (voice_handle->speexCapureDownResample) {
        speex_resampler_destroy(voice_handle->speexCapureDownResample);
        voice_handle->speexCapureDownResample = NULL;
    }

    if (voice_handle->speexCapureDownResample) {
        speex_resampler_destroy(voice_handle->speexCapureDownResample);
        voice_handle->speexCapureDownResample = NULL;
    }

    if (voice_handle->speexPlaybackUpResample) {
        speex_resampler_destroy(voice_handle->speexPlaybackUpResample);
        voice_handle->speexPlaybackUpResample = NULL;
    }

    if (voice_handle->speexPlaybackDownResample) {
        speex_resampler_destroy(voice_handle->speexPlaybackDownResample);
        voice_handle->speexPlaybackDownResample = NULL;
    }

    if (voice_handle->playBackBuffer != NULL) {
        pthread_mutex_lock(&voice_handle->voice_thread.queuePlyLock);
        free(voice_handle->playBackBuffer);
        voice_handle->playBackBuffer = NULL;
        voice_handle->playbackBufferSize = 0;
        pthread_mutex_unlock(&voice_handle->voice_thread.queuePlyLock);
    }

    if (voice_handle->captureBuffer != NULL) {
        pthread_mutex_lock(&voice_handle->voice_thread.queueCapLock);
        free(voice_handle->captureBuffer);
        voice_handle->captureBuffer = NULL;
        voice_handle->captureBufferSize = 0;
        pthread_mutex_unlock(&voice_handle->voice_thread.queueCapLock);
    }

    if (voice_handle->outPlayBuffer != NULL) {
        pthread_mutex_lock(&voice_handle->voice_thread.getPlyOutLock);
        free(voice_handle->outPlayBuffer);
        voice_handle->outPlayBuffer = NULL;
        voice_handle->outPlaybackBufferSize = 0;
        pthread_mutex_unlock(&voice_handle->voice_thread.getPlyOutLock);
    }

    if (voice_handle->outCaptureBuffer != NULL) {
        pthread_mutex_lock(&voice_handle->voice_thread.getCapOutLock);
        free(voice_handle->outCaptureBuffer);
        voice_handle->outCaptureBuffer = NULL;
        voice_handle->outCaptureBufferSize = 0;
        pthread_mutex_unlock(&voice_handle->voice_thread.getCapOutLock);
    }

    if (voice_handle->processApi) {
        free(voice_handle->processApi);
        voice_handle->processApi = NULL;
    }

    if (voice_handle->voiceApi) {
        voice_handle->voiceApi->deinit();
    }

    if (voice_handle->voiceApi != NULL) {
        free(voice_handle->voiceApi);
        voice_handle->voiceApi = NULL;
    }
    if (voice_handle->voiceLibHandle != NULL) {
        dlclose(voice_handle->voiceLibHandle);
        voice_handle->voiceLibHandle = NULL;
    }

    if (voice_handle != NULL) {
        free(voice_handle);
        voice_handle = NULL;
    }
    ALOGD("voice process handle destory success!");
    return 0;
}


static int processBuffertoMono(void *buffer, int size)
{
    short *in = (short *)buffer;
    short out[size/4];
    int i = 0, j = 0;

    for(i = 0, j = 0; i < size/4; i++) {
        out[i] = (in[j] + in[j+1]) / 2;
        j+=2;
    }
    memset((char *)in, 0x00, size);
    memcpy((char *)in, (char *)out, size/2);
    return 0;
}

static int processBuffertoStereo(void *buffer, int size)
{
    short *in = (short *)buffer;
    short out[size];
    int i = 0,j = 0;;

    for (i = 0, j = 0; i < size/2; i++) {
        out[j] = in[i];
        out[j+1] = in[i];
        j+=2;
    }
    memcpy((char *)in, (char *)out, size * 2);
    return 0;
}


static void thread_loop(rk_voice_handle* handle)
{
    int playback_samplerate = handle->playbackInSamplerate;
    int capture_samplerate = handle->captureInSamplerate;
    int process_samplerate = handle->processSamplerate;
    int playback_channel = handle->playbackInChannels;
    int capture_channel = handle->captureInChannels;
    int process_buffer_size = PROCESS_BUFFER_SIZE * 2;

    int playback_min_buffersize = process_buffer_size * playback_samplerate / process_samplerate * playback_channel;
    int capture_min_buffersize = process_buffer_size * capture_samplerate / process_samplerate * capture_channel;

    char tmp_playback_buffer[playback_min_buffersize];
    char tmp_capture_buffer[capture_min_buffersize];

    char tmp_outplayback_buffer[playback_min_buffersize];
    char tmp_outcapture_buffer[capture_min_buffersize];
#ifdef ALSA_3A_DEBUG
    in_capture_debug = fopen("/data/3a_capture_in.pcm","wb");//please touch /data/3a_in.pcm first
    out_capture_debug = fopen("/data/3a_capture_out.pcm","wb");//please touch /data/3a_out.pcm first
    in_playback_debug = fopen("/data/3a_playback_in.pcm","wb");//please touch /data/3a_ref.pcm first
    out_playback_debug = fopen("/data/3a_playback_out.pcm","wb");//please touch /data/3a_rx.pcm first
#endif

    while (handle->voice_thread.running) {

        bool isGetBuffer = false;

        //wait the enough raw buffer
        if ((handle->captureBufferSize < capture_min_buffersize) || (handle->playbackBufferSize < playback_min_buffersize)) {
            sem_wait(&handle->voice_thread.sem);
        }

        char value[PROPERTY_VALUE_MAX] = "";
        property_get("media.audio.record", value, NULL);
        prop_pcm_record = atoi(value);

        // try to get the raw buffer to process
        if ((handle->captureBufferSize >= capture_min_buffersize) && (handle->playbackBufferSize >= playback_min_buffersize)) {
            pthread_mutex_lock(&handle->voice_thread.queueCapLock);
            memcpy(tmp_capture_buffer, handle->captureBuffer, capture_min_buffersize);
            memcpy(handle->captureBuffer, handle->captureBuffer+capture_min_buffersize, MAX_BUFFER_SIZE-capture_min_buffersize);
            handle->captureBufferSize -= capture_min_buffersize;
            pthread_mutex_unlock(&handle->voice_thread.queueCapLock);

            pthread_mutex_lock(&handle->voice_thread.queuePlyLock);
            memcpy(tmp_playback_buffer, handle->playBackBuffer, playback_min_buffersize);
            memcpy(handle->playBackBuffer, handle->playBackBuffer+playback_min_buffersize, MAX_BUFFER_SIZE-playback_min_buffersize);
            handle->playbackBufferSize -= playback_min_buffersize;
            pthread_mutex_unlock(&handle->voice_thread.queuePlyLock);
            isGetBuffer = true;
        }

        // process the raw buffer and queue to output list
        if (isGetBuffer) {
            // process buffer to mono
            if (playback_channel > 1) {
                processBuffertoMono(tmp_playback_buffer, playback_min_buffersize);
            }

            if (capture_channel > 1) {
                processBuffertoMono(tmp_capture_buffer, capture_min_buffersize);
            }

            // resample raw buffer to processed samplerate
            if (playback_samplerate != process_samplerate) {
                int in_sample = playback_min_buffersize / playback_channel / 2;
                int out_sample = in_sample;
                char tmp_resample_buffer[playback_min_buffersize];

                memcpy(tmp_resample_buffer, tmp_playback_buffer, playback_min_buffersize);
                memset(tmp_playback_buffer, 0x00, playback_min_buffersize);
                speex_resampler_process_interleaved_int(handle->speexPlaybackDownResample,
                                                        (spx_int16_t *)tmp_resample_buffer, &in_sample,
                                                        (spx_int16_t *)tmp_playback_buffer, &out_sample);
                ALOGV("playback down resample process, in_sample = %d, out_sample = %d", in_sample, out_sample);
            }

            if (capture_samplerate != process_samplerate) {
                int in_sample = capture_min_buffersize / capture_channel / 2;
                int out_sample = in_sample;
                char tmp_resample_buffer[playback_min_buffersize];
                memcpy(tmp_resample_buffer, tmp_capture_buffer, capture_min_buffersize);
                memset(tmp_capture_buffer, 0x00, capture_min_buffersize);
                speex_resampler_process_interleaved_int(handle->speexCapureDownResample,
                                                        (spx_int16_t *)tmp_resample_buffer, &in_sample,
                                                        (spx_int16_t *)tmp_capture_buffer, &out_sample);
                ALOGV("capture down resample process, in_sample = %d, out_sample = %d,capture_samplerate = %d", in_sample, out_sample,capture_samplerate);
            }

            // main process call
            if (handle->voiceApi) {
                //memcpy((char *)tmp_outplayback_buffer, (char *)tmp_playback_buffer, PROCESS_BUFFER_SIZE * 2);
                //memcpy((char *)tmp_outcapture_buffer, (char *)tmp_capture_buffer, PROCESS_BUFFER_SIZE * 2);
                handle->voiceApi->processPlayback((short *)tmp_playback_buffer, (short *)tmp_outplayback_buffer, PROCESS_BUFFER_SIZE);
                handle->voiceApi->processCapture((short *)tmp_capture_buffer, (short *)tmp_outplayback_buffer, (short *)tmp_outcapture_buffer, PROCESS_BUFFER_SIZE);
#ifdef ALSA_3A_DEBUG           
                fwrite(tmp_capture_buffer,sizeof(short),PROCESS_BUFFER_SIZE,in_capture_debug);
                fwrite(tmp_outcapture_buffer,sizeof(short),PROCESS_BUFFER_SIZE,out_capture_debug);
                fwrite(tmp_playback_buffer,sizeof(short),PROCESS_BUFFER_SIZE,in_playback_debug);
		fwrite(tmp_outplayback_buffer,sizeof(short),PROCESS_BUFFER_SIZE,out_playback_debug);
#endif
            }

            // upresample the processed buffer to raw buffer samplerate
            if (playback_samplerate != process_samplerate) {
                int in_sample = PROCESS_BUFFER_SIZE;
                int out_sample = playback_min_buffersize;
                memset(tmp_playback_buffer, 0x00, playback_min_buffersize);
                memcpy(tmp_playback_buffer, tmp_outplayback_buffer, process_buffer_size);
                speex_resampler_process_interleaved_int(handle->speexPlaybackUpResample,
                                                        (spx_int16_t *)tmp_playback_buffer, &in_sample,
                                                        (spx_int16_t *)tmp_outplayback_buffer, &out_sample);
                ALOGV("playback up resample process, in_sample = %d, out_sample = %d", in_sample, out_sample);

            }

            if (capture_samplerate != process_samplerate) {
                int in_sample = PROCESS_BUFFER_SIZE;
                int out_sample = capture_min_buffersize;
                memset(tmp_capture_buffer, 0x00, capture_min_buffersize);
                memcpy(tmp_capture_buffer, tmp_outcapture_buffer, process_buffer_size);
                speex_resampler_process_interleaved_int(handle->speexCapureUpResample,
                                                        (spx_int16_t *)tmp_capture_buffer, &in_sample,
                                                        (spx_int16_t *)tmp_outcapture_buffer, &out_sample);
                ALOGV("capture up resample process, in_sample = %d, out_sample = %d", in_sample, out_sample);
            }

            // up adjust channel to raw buffer channels
            if (playback_channel > 1) {
                processBuffertoStereo(tmp_outplayback_buffer, playback_min_buffersize/2);
            }

            if (capture_channel > 1) {
                processBuffertoStereo(tmp_outcapture_buffer, capture_min_buffersize/2);
            }

            // queue processed buffer to output list
            pthread_mutex_lock(&handle->voice_thread.getCapOutLock);
            memcpy((char *)handle->outCaptureBuffer + handle->outCaptureBufferSize, tmp_outcapture_buffer, capture_min_buffersize);
            handle->outCaptureBufferSize += capture_min_buffersize;
            pthread_mutex_unlock(&handle->voice_thread.getCapOutLock);

            pthread_mutex_lock(&handle->voice_thread.getPlyOutLock);
            memcpy((char *)handle->outPlayBuffer + handle->outPlaybackBufferSize, tmp_outplayback_buffer, playback_min_buffersize);
            handle->outPlaybackBufferSize += playback_min_buffersize;
            pthread_mutex_unlock(&handle->voice_thread.getPlyOutLock);
        }
    }

#ifdef ALSA_3A_DEBUG
    fclose(in_capture_debug);
    fclose(out_capture_debug);
    fclose(in_playback_debug);
    fclose(out_playback_debug);
#endif

}

static void*  thread_start(void* argv)
{
    rk_voice_handle* handle = (rk_voice_handle*)argv;

    thread_loop(handle);

    return NULL;
}

