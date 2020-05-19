/*
 * Copyright (C) 2015 Fuzhou Rockchip Electronics Co. Ltd. All rights reserved.
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
** Copyright 2010, The Android Open-Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

/**
 * @file alsa_mixer.c
 * @brief
 * @author  RkAudio
 * @version 1.0.8
 * @date 2015-08-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#include <linux/ioctl.h>
#define __force
#define __bitwise
#define __user
#include "asound.h"
#define LOG_TAG "alsa_mixer"

//#define LOG_NDEBUG 0

#include "alsa_audio.h"
#include <cutils/log.h>

#define MAX_SOUND_CARDS     10
#define VOLUME_PERCENTS     90
#define SOUND_CTL_PREFIX    "/dev/snd/controlC%d"

/* convert to index of integer array */
#define int_index(size)	(((size) + sizeof(int) - 1) / sizeof(int))
/* max size of a TLV entry for dB information (including compound one) */
#define MAX_TLV_RANGE_SIZE	256

char *volume_controls_name_table[] = {
    "Earpiece Playback Volume",
    "Speaker Playback Volume",
    "Headphone Playback Volume",
    "PCM Playback Volume",
    "Mic Capture Volume",
};

/**
 * @brief elem_iface_name
 *
 * @param n
 *
 * @returns
 */
static const char *elem_iface_name(snd_ctl_elem_iface_t n)
{
    switch (n) {
    case SNDRV_CTL_ELEM_IFACE_CARD:
        return "CARD";
    case SNDRV_CTL_ELEM_IFACE_HWDEP:
        return "HWDEP";
    case SNDRV_CTL_ELEM_IFACE_MIXER:
        return "MIXER";
    case SNDRV_CTL_ELEM_IFACE_PCM:
        return "PCM";
    case SNDRV_CTL_ELEM_IFACE_RAWMIDI:
        return "MIDI";
    case SNDRV_CTL_ELEM_IFACE_TIMER:
        return "TIMER";
    case SNDRV_CTL_ELEM_IFACE_SEQUENCER:
        return "SEQ";
    default:
        return "???";
    }
}

/**
 * @brief elem_type_name
 *
 * @param n
 *
 * @returns
 */
static const char *elem_type_name(snd_ctl_elem_type_t n)
{
    switch (n) {
    case SNDRV_CTL_ELEM_TYPE_NONE:
        return "NONE";
    case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
        return "BOOL";
    case SNDRV_CTL_ELEM_TYPE_INTEGER:
        return "INT32";
    case SNDRV_CTL_ELEM_TYPE_ENUMERATED:
        return "ENUM";
    case SNDRV_CTL_ELEM_TYPE_BYTES:
        return "BYTES";
    case SNDRV_CTL_ELEM_TYPE_IEC958:
        return "IEC958";
    case SNDRV_CTL_ELEM_TYPE_INTEGER64:
        return "INT64";
    default:
        return "???";
    }
}

/**
 * @brief mixer_close_legacy
 *
 * @param mixer
 */
void mixer_close_legacy(struct mixer *mixer)
{
    unsigned n,m;

    if (mixer->fd >= 0)
        close(mixer->fd);

    if (mixer->ctl) {
        for (n = 0; n < mixer->count; n++) {
            if (mixer->ctl[n].tlv)
                free(mixer->ctl[n].tlv);
            if (mixer->ctl[n].ename) {
                unsigned max = mixer->ctl[n].info->value.enumerated.items;
                for (m = 0; m < max; m++)
                    if(mixer->ctl[n].ename[m])
                        free(mixer->ctl[n].ename[m]);
                if(mixer->ctl[n].ename[m])
                    free(mixer->ctl[n].ename);
            }
        }
        free(mixer->ctl);
    }

    if (mixer->info)
        free(mixer->info);

    free(mixer);
}

/**
 * @brief mixer_open_legacy
 *
 * @param card
 *
 * @returns
 */
struct mixer *mixer_open_legacy(unsigned card)
{
    char dname[sizeof(SOUND_CTL_PREFIX) + 20];
    struct snd_ctl_elem_list elist;
    struct snd_ctl_elem_info tmp;
    struct snd_ctl_elem_id *eid = NULL;
    struct mixer *mixer = NULL;
    unsigned n, m, i, max = sizeof(volume_controls_name_table) / sizeof(char *);
    int fd;
    sprintf(dname, SOUND_CTL_PREFIX, card);

    fd = open(dname, O_RDWR);

    if (fd < 0) {
        ALOGE("mixer_open() Can not open %s for card %d", dname, card);
        return 0;
    }

    memset(&elist, 0, sizeof(elist));
    if (ioctl(fd, SNDRV_CTL_IOCTL_ELEM_LIST, &elist) < 0)
        goto fail;

    mixer = calloc(1, sizeof(*mixer));
    if (!mixer)
        goto fail;

    mixer->ctl = calloc(elist.count, sizeof(struct mixer_ctl));
    mixer->info = calloc(elist.count, sizeof(struct snd_ctl_elem_info));
    if (!mixer->ctl || !mixer->info)
        goto fail;

    eid = calloc(elist.count, sizeof(struct snd_ctl_elem_id));
    if (!eid)
        goto fail;

    mixer->count = elist.count;
    mixer->fd = fd;
    elist.space = mixer->count;
    elist.pids = eid;
    if (ioctl(fd, SNDRV_CTL_IOCTL_ELEM_LIST, &elist) < 0)
        goto fail;

    for (n = 0; n < mixer->count; n++) {
        struct snd_ctl_elem_info *ei = mixer->info + n;
        ei->id.numid = eid[n].numid;
        if (ioctl(fd, SNDRV_CTL_IOCTL_ELEM_INFO, ei) < 0)
            goto fail;
        mixer->ctl[n].info = ei;
        mixer->ctl[n].mixer = mixer;
        if (ei->type == SNDRV_CTL_ELEM_TYPE_ENUMERATED) {
            char **enames = calloc(ei->value.enumerated.items, sizeof(char*));
            if (!enames)
                goto fail;
            mixer->ctl[n].ename = enames;
            for (m = 0; m < ei->value.enumerated.items; m++) {
                memset(&tmp, 0, sizeof(tmp));
                tmp.id.numid = ei->id.numid;
                tmp.value.enumerated.item = m;
                if (ioctl(fd, SNDRV_CTL_IOCTL_ELEM_INFO, &tmp) < 0)
                    goto fail;
                enames[m] = strdup(tmp.value.enumerated.name);
                if (!enames[m])
                    goto fail;
            }
        }

        //add for incall volume by Jear.Chen. get tlv.
        for (i = 0; i < max; i++) {
            if (!strcmp((char*) mixer->ctl[n].info->id.name, volume_controls_name_table[i]))
                break;
        }

        if (i >= max) {
            mixer->ctl[n].tlv = NULL;
            continue;
        }

        if ((mixer->ctl[n].info->access & SNDRV_CTL_ELEM_ACCESS_TLV_READWRITE) == 0) {
            ALOGV("mixer_open() type of control %s is not TLVT_DB", mixer->ctl[n].info->id.name);
            mixer->ctl[n].tlv = NULL;
            continue;
        }

        unsigned int tlv_size = 2 * sizeof(unsigned int) + 2 * sizeof(unsigned int);
        struct snd_ctl_tlv *tlv = malloc(sizeof(struct sndrv_ctl_tlv) + tlv_size);

        //tlv->numid < (info->id.numid + info->count) and
        //tlv->numid >= info->id.numid
        tlv->numid = mixer->ctl[n].info->id.numid;
        //length >= tlv.p[1] + 2 * sizeof(unsigned int);
        //tlv.p is DECLARE_TLV_DB_SCALE defined in kernel
        tlv->length = tlv_size;

        if (ioctl(fd, SNDRV_CTL_IOCTL_TLV_READ, tlv) < 0) {
            ALOGE("mixer_open() get tlv for control %s fail", mixer->ctl[n].info->id.name);
            free(tlv);
            mixer->ctl[n].tlv = tlv = NULL;
            continue;
        }

        ALOGV("mixer_open() get tlv for control %s", mixer->ctl[n].info->id.name);
        mixer->ctl[n].tlv = tlv;
        //add for incall volume end
    }

    free(eid);
    return mixer;

fail:
    if (eid)
        free(eid);
    if (mixer)
        mixer_close_legacy(mixer);
    else if (fd >= 0)
        close(fd);
    return 0;
}

/**
 * @brief mixer_ctl_print
 *
 * @param ctl
 */
void mixer_ctl_print(struct mixer_ctl *ctl)
{
    struct snd_ctl_elem_value ev;
    struct snd_ctl_elem_info *ei = ctl->info;
    unsigned m;

    memset(&ev, 0, sizeof(ev));
    ev.id.numid = ctl->info->id.numid;
    if (ioctl(ctl->mixer->fd, SNDRV_CTL_IOCTL_ELEM_READ, &ev))
        return;
    printf("%s:", ctl->info->id.name);

    switch (ei->type) {
    case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
        for (m = 0; m < ei->count; m++)
            printf(" %s", ev.value.integer.value[m] ? "ON" : "OFF");

        printf(" { OFF=0, ON=1 }");
        break;
    case SNDRV_CTL_ELEM_TYPE_INTEGER:
        for (m = 0; m < ei->count; m++)
            printf(" %ld", ev.value.integer.value[m]);

        printf(ei->value.integer.step ?
               " { %ld-%ld, %ld }\n" : " { %ld-%ld }",
               ei->value.integer.min,
               ei->value.integer.max,
               ei->value.integer.step);
        break;
    case SNDRV_CTL_ELEM_TYPE_INTEGER64:
        for (m = 0; m < ei->count; m++)
            printf(" %lld", ev.value.integer64.value[m]);

        printf(ei->value.integer64.step ?
               " { %lld-%lld, %lld }\n" : " { %lld-%lld }",
               ei->value.integer64.min,
               ei->value.integer64.max,
               ei->value.integer64.step);
        break;
    case SNDRV_CTL_ELEM_TYPE_ENUMERATED: {
        for (m = 0; m < ei->count; m++) {
            unsigned v = ev.value.enumerated.item[m];
            printf(" (%d %s)", v,
                   (v < ei->value.enumerated.items) ? ctl->ename[v] : "???");
        }

        printf(" { %s=0", ctl->ename[0]);
        for (m = 1; m < ei->value.enumerated.items; m++)
            printf(", %s=%d", ctl->ename[m],m);
        printf(" }");
        break;
    }
    default:
        printf(" ???");
    }
    printf("\n");
}

/**
 * @brief mixer_dump
 *
 * @param mixer
 */
void mixer_dump(struct mixer *mixer)
{
    unsigned n;

    printf("  id iface dev sub idx num perms     type   name\n");
    for (n = 0; n < mixer->count; n++) {
        struct snd_ctl_elem_info *ei = mixer->info + n;

        printf("%4d %5s %3d %3d %3d %3d %c%c%c%c%c%c%c%c%c %-6s ",
               ei->id.numid, elem_iface_name(ei->id.iface),
               ei->id.device, ei->id.subdevice, ei->id.index,
               ei->count,
               (ei->access & SNDRV_CTL_ELEM_ACCESS_READ) ? 'r' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_WRITE) ? 'w' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_VOLATILE) ? 'V' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_TIMESTAMP) ? 'T' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_TLV_READ) ? 'R' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_TLV_WRITE) ? 'W' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_TLV_COMMAND) ? 'C' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_INACTIVE) ? 'I' : ' ',
               (ei->access & SNDRV_CTL_ELEM_ACCESS_LOCK) ? 'L' : ' ',
               elem_type_name(ei->type));

        mixer_ctl_print(mixer->ctl + n);
    }
}

/**
 * @brief mixer_get_control
 *
 * @param mixer
 * @param name
 * @param index
 *
 * @returns
 */
struct mixer_ctl *mixer_get_control(struct mixer *mixer,
                                    const char *name, unsigned index)
{
    unsigned n;
    for (n = 0; n < mixer->count; n++) {
        if (mixer->info[n].id.index == index) {
            if (!strcmp(name, (char*) mixer->info[n].id.name)) {
                ALOGV("mixer_get_control() %s access 0x%08x",mixer->info[n].id.name,mixer->info[n].access);
                return mixer->ctl + n;
            }
        }
    }
    return 0;
}

/**
 * @brief mixer_get_nth_control
 *
 * @param mixer
 * @param n
 *
 * @returns
 */
struct mixer_ctl *mixer_get_nth_control(struct mixer *mixer, unsigned n)
{
    if (n < mixer->count)
        return mixer->ctl + n;
    return 0;
}

/**
 * @brief scale_int
 *
 * @param ei
 * @param _percent
 *
 * @returns
 */
static long scale_int(struct snd_ctl_elem_info *ei, unsigned _percent)
{
    long percent;
    long range;

    if (_percent > 100)
        percent = 100;
    else
        percent = (long) _percent;

    range = (ei->value.integer.max - ei->value.integer.min);

    return ei->value.integer.min + (range * percent) / 100LL;
}

/**
 * @brief scale_int64
 *
 * @param ei
 * @param _percent
 *
 * @returns
 */
static long long scale_int64(struct snd_ctl_elem_info *ei, unsigned _percent)
{
    long long percent;
    long long range;

    if (_percent > 100)
        percent = 100;
    else
        percent = (long) _percent;

    range = (ei->value.integer.max - ei->value.integer.min) * 100LL;

    return ei->value.integer.min + (range / percent);
}
/**
 * @brief mixer_ctl_set_val
 *
 * @param ctl
 * @param value
 *
 * @returns
 */


int mixer_ctl_set_val(struct mixer_ctl *ctl, int value)
{
    struct snd_ctl_elem_value ev;

    memset(&ev, 0, sizeof(ev));
    ev.id.numid = ctl->info->id.numid;

    switch (ctl->info->type) {
    case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
        ev.value.integer.value[0] = !!value;
        break;
    case SNDRV_CTL_ELEM_TYPE_INTEGER:
        ev.value.integer.value[0] = value;
        break;
    case SNDRV_CTL_ELEM_TYPE_INTEGER64:
        ev.value.integer64.value[0] = value;
        break;
defalut:
        errno = EINVAL;
        return -1;
    }
    return ioctl(ctl->mixer->fd, SNDRV_CTL_IOCTL_ELEM_WRITE, &ev);
}

/**
 * @brief mixer_ctl_set
 *
 * @param ctl
 * @param percent
 *
 * @returns
 */
int mixer_ctl_set(struct mixer_ctl *ctl, unsigned percent)
{
    struct snd_ctl_elem_value ev;
    unsigned n;

    memset(&ev, 0, sizeof(ev));
    ev.id.numid = ctl->info->id.numid;
    switch (ctl->info->type) {
    case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
        for (n = 0; n < ctl->info->count; n++)
            ev.value.integer.value[n] = !!percent;
        break;
    case SNDRV_CTL_ELEM_TYPE_INTEGER: {
        long value = scale_int(ctl->info, percent);
        for (n = 0; n < ctl->info->count; n++)
            ev.value.integer.value[n] = value;
        break;
    }
    case SNDRV_CTL_ELEM_TYPE_INTEGER64: {
        long long value = scale_int64(ctl->info, percent);
        for (n = 0; n < ctl->info->count; n++)
            ev.value.integer64.value[n] = value;
        break;
    }
    default:
        errno = EINVAL;
        return -1;
    }

    return ioctl(ctl->mixer->fd, SNDRV_CTL_IOCTL_ELEM_WRITE, &ev);
}

/**
 * @brief mixer_ctl_select
 *
 * @param ctl
 * @param value
 *
 * @returns
 */
int mixer_ctl_select(struct mixer_ctl *ctl, const char *value)
{
    unsigned n, max;
    struct snd_ctl_elem_value ev;

    if (ctl->info->type != SNDRV_CTL_ELEM_TYPE_ENUMERATED) {
        errno = EINVAL;
        return -1;
    }

    max = ctl->info->value.enumerated.items;
    for (n = 0; n < max; n++) {
        if (!strcmp(value, ctl->ename[n])) {
            memset(&ev, 0, sizeof(ev));
            ev.value.enumerated.item[0] = n;
            ev.id.numid = ctl->info->id.numid;
            if (ioctl(ctl->mixer->fd, SNDRV_CTL_IOCTL_ELEM_WRITE, &ev) < 0)
                return -1;
            return 0;
        }
    }

    errno = EINVAL;
    return -1;
}

/**
 * @brief mixer_ctl_set_int_double
 *
 * @param ctl
 * @param left
 * @param right
 *
 * @returns
 */
int mixer_ctl_set_int_double(struct mixer_ctl *ctl, long long left, long long right)
{
    struct snd_ctl_elem_value ev;
    unsigned n;
    long long max, min, value = left;

    memset(&ev, 0, sizeof(ev));
    ev.id.numid = ctl->info->id.numid;
    switch (ctl->info->type) {
    case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
        for (n = 0; n < ctl->info->count; n++) {
            ev.value.integer.value[n] = !!value;
            value = right;
        }
        break;
    case SNDRV_CTL_ELEM_TYPE_INTEGER: {
        max = ctl->info->value.integer.max;
        min = ctl->info->value.integer.min;

        left = left > max ? max : left;
        left = left < min ? min : left;
        right = right > max ? max : right;
        right = right < min ? min : right;

        value = left;

        for (n = 0; n < ctl->info->count; n++) {
            ev.value.integer.value[n] = (long)value;
            value = right;
        }
        break;
    }
    case SNDRV_CTL_ELEM_TYPE_INTEGER64: {
        max = ctl->info->value.integer64.max;
        min = ctl->info->value.integer64.min;

        left = left > max ? max : left;
        left = left < min ? min : left;
        right = right > max ? max : right;
        right = right < min ? min : right;

        value = left;

        for (n = 0; n < ctl->info->count; n++) {
            ev.value.integer64.value[n] = value;
            value = right;
        }
        break;
    }
    case SNDRV_CTL_ELEM_TYPE_ENUMERATED:
        max = ctl->info->value.enumerated.items;
        return mixer_ctl_select(ctl, ctl->ename[value > max ? max : value]);
    default:
        errno = EINVAL;
        return -1;
    }

    return ioctl(ctl->mixer->fd, SNDRV_CTL_IOCTL_ELEM_WRITE, &ev);
}

/**
 * @brief mixer_ctl_set_int
 *
 * @param ctl
 * @param value
 *
 * @returns
 */
int mixer_ctl_set_int(struct mixer_ctl *ctl, long long value)
{
    return mixer_ctl_set_int_double(ctl, value, value);
}

/**
 * @brief mixer_get_ctl_minmax
 *
 * @param ctl
 * @param min
 * @param max
 *
 * @returns
 */
int mixer_get_ctl_minmax(struct mixer_ctl *ctl, long long *min, long long *max)
{
    struct snd_ctl_elem_info *ei = ctl->info;

    switch (ei->type) {
    case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
    case SNDRV_CTL_ELEM_TYPE_INTEGER:
        *min = ei->value.integer.min;
        *max = ei->value.integer.max;
        break;
    case SNDRV_CTL_ELEM_TYPE_INTEGER64:
        *min = ei->value.integer64.min;
        *max = ei->value.integer64.max;
        break;
    case SNDRV_CTL_ELEM_TYPE_ENUMERATED:
        *min = 0;
        *max = ei->value.enumerated.items;
        break;
    default:
        return -EINVAL;
    }

    return 0;
}

/**
 * @brief mixer_tlv_get_dB_range
 * Get dB range from tlv[] which is obtained from control
 *
 * @param tlv
 * @param rangemin
 * @param rangemax
 * @param min
 * @param max
 *
 * @returns
 */
int mixer_tlv_get_dB_range(unsigned int *tlv, long rangemin, long rangemax,
                           long *min, long *max)
{
    int err;

    switch (tlv[0]) {
    case SND_CTL_TLVT_DB_RANGE: {
        unsigned int pos, len;
        len = int_index(tlv[1]);
        if (len > MAX_TLV_RANGE_SIZE)
            return -EINVAL;
        pos = 2;
        while (pos + 4 <= len) {
            long rmin, rmax;
            rangemin = (int)tlv[pos];
            rangemax = (int)tlv[pos + 1];
            err = mixer_tlv_get_dB_range(tlv + pos + 2,
                                         rangemin, rangemax,
                                         &rmin, &rmax);
            if (err < 0)
                return err;
            if (pos > 2) {
                if (rmin < *min)
                    *min = rmin;
                if (rmax > *max)
                    *max = rmax;
            } else {
                *min = rmin;
                *max = rmax;
            }
            pos += int_index(tlv[pos + 3]) + 4;
        }
        return 0;
    }
    case SND_CTL_TLVT_DB_SCALE: {
        long step;
        *min = (int)tlv[2];
        step = (tlv[3] & 0xffff);
        *max = *min + (long)(step * (rangemax - rangemin));
        return 0;
    }
    case SND_CTL_TLVT_DB_MINMAX:
    case SND_CTL_TLVT_DB_MINMAX_MUTE:
    case SND_CTL_TLVT_DB_LINEAR:
        *min = (int)tlv[2];
        *max = (int)tlv[3];
        return 0;
    }
    return -EINVAL;
}

/**
 * @brief mixer_get_dB_range
 * Get dB range of control
 *
 * @param ctl
 * @param rangemin
 * @param rangemax
 * @param dB_min
 * @param dB_max
 * @param dB_step
 *
 * @returns
 */
int mixer_get_dB_range(struct mixer_ctl *ctl, long rangemin, long rangemax,
                       float *dB_min, float *dB_max, float *dB_step)
{
    unsigned int *tlv;
    long min, max;

    if (ctl->tlv == NULL) {
        ALOGE("mixer_get_dB_range() tlv of control %s is NULL", ctl->info->id.name);
        return -EINVAL;
    }

    if (mixer_tlv_get_dB_range(ctl->tlv->tlv, rangemin, rangemax,
                               &min, &max) < 0) {
        ALOGE("mixer_get_dB_range() get control dB range fail");
        return -EINVAL;
    }

    *dB_min = min * 1.0 / 100;
    *dB_max = max * 1.0 / 100;
    *dB_step = (max - min) * 1.0 / (rangemax - rangemin) / 100;

    ALOGV("control %s : dB min = %f, dB max = %f, dB step = %f",
          ctl->info->id.name,
          *dB_min,
          *dB_max,
          *dB_step);

    return 0;
}
