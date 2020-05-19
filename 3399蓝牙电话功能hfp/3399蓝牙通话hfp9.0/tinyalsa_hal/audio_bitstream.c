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
#include "audio_bitstream.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <cutils/log.h>

/* b, p, c, u, v, 0, 0, 0*/
#define B_BIT_SHIFT    7
#define P_BIT_SHIFT    6
#define C_BIT_SHIFT    5
#define U_BIT_SHIFT    4
#define V_BIT_SHIFT    3
#define C_BIT_SET      (0x1<<C_BIT_SHIFT)
#define C_BIT_UNSET    (~(0x1<<C_BIT_SHIFT))


#define CHASTA_BIT0    0
#define CHASTA_BIT1    1
/* bit 24~27  sampling frequency */
#define CHASTA_BIT24   24
#define CHASTA_BIT25   25
#define CHASTA_BIT26   26
#define CHASTA_BIT27   27
/* bit 32~35 sample word lentgh */
#define CHASTA_BIT32   32
#define CHASTA_BIT33   33
#define CHASTA_BIT34   34
#define CHASTA_BIT35   35
/* bit 36~39 original samplling frequency */
#define CHASTA_BIT36   36
#define CHASTA_BIT37   37
#define CHASTA_BIT38   38
#define CHASTA_BIT39   39


static int scount = 0;

bool isValidSamplerate(int samplerate)
{
    if ((samplerate == 44100) || (samplerate== 48000) || (samplerate == 32000) ||
            (samplerate == 176400) || (samplerate == 192000)) {
        return true;
    }
    return false;
}


/**
 * @brief initchnsta
 */
void initchnsta(char* buffer)
{
    scount = 0;
    if(buffer != NULL){
        memset(buffer, 0x0, CHASTA_SUB_NUM);
        buffer[CHASTA_BIT1*2] = 1;
        buffer[CHASTA_BIT1*2+1] = 1;
        /* word length default 24 bit*/
        buffer[CHASTA_BIT32*2] = 1;
        buffer[CHASTA_BIT32*2+1] = 1;
        buffer[CHASTA_BIT33*2] = 1;
        buffer[CHASTA_BIT33*2+1] = 1;
        buffer[CHASTA_BIT35*2] = 1;
        buffer[CHASTA_BIT35*2+1] = 1;
        /* sampling frequency default 48k */
        buffer[CHASTA_BIT25*2] = 1;
        buffer[CHASTA_BIT25*2+1] = 1;
        /* original sampling frequency default 48k */
        buffer[CHASTA_BIT36*2] = 1;
        buffer[CHASTA_BIT36*2+1] = 1;
        buffer[CHASTA_BIT38*2] = 1;
        buffer[CHASTA_BIT38*2+1] = 1;
        buffer[CHASTA_BIT39*2] = 1;
        buffer[CHASTA_BIT39*2+1] = 1;

        /* b, p, c, u, v, 0, 0, 0*/
        int i = 0;
        for (i=0; i<CHASTA_SUB_NUM; i++)
            buffer[i] = (buffer[i]<<C_BIT_SHIFT) | (0x1<<V_BIT_SHIFT);

        /* B bit */
        buffer[CHASTA_BIT0*2] |= (0X1<<B_BIT_SHIFT);
        buffer[CHASTA_BIT0*2+1] |= (0X1<<B_BIT_SHIFT);
    }
}

void set176400chnsta(char* buffer)
{
    if(buffer == NULL)
        return;    

    /* sampling frequency default 176.4K */
    buffer[CHASTA_BIT24*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT24*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT25*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT25*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT26*2] |= C_BIT_SET;
    buffer[CHASTA_BIT26*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT27*2] |= C_BIT_SET;
    buffer[CHASTA_BIT27*2+1] |= C_BIT_SET;
    /* original sampling frequency */
    buffer[CHASTA_BIT36*2] |= C_BIT_SET;
    buffer[CHASTA_BIT36*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT37*2] |= C_BIT_SET;
    buffer[CHASTA_BIT37*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT38*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT38*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT39*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT39*2+1] &= C_BIT_UNSET;
}

void set32000chnsta(char* buffer)
{
    if(buffer == NULL)
        return;

    /* sampling frequency default 32K */
    buffer[CHASTA_BIT24*2] |= C_BIT_SET;
    buffer[CHASTA_BIT24*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT25*2] |= C_BIT_SET;
    buffer[CHASTA_BIT25*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT26*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT26*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT27*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT27*2+1] &= C_BIT_UNSET;
    /* original sampling frequency */
    buffer[CHASTA_BIT36*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT36*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT37*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT37*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT38*2] |= C_BIT_SET;
    buffer[CHASTA_BIT38*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT39*2] |= C_BIT_SET;
    buffer[CHASTA_BIT39*2+1] |= C_BIT_SET;
}


void set44100chnsta(char* buffer)
{
    if(buffer == NULL)
        return;

    /* sampling frequency default 44.1K */
    buffer[CHASTA_BIT24*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT24*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT25*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT25*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT26*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT26*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT27*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT27*2+1] &= C_BIT_UNSET;
    /* original sampling frequency */
    buffer[CHASTA_BIT36*2] |= C_BIT_SET;
    buffer[CHASTA_BIT36*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT37*2] |= C_BIT_SET;
    buffer[CHASTA_BIT37*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT38*2] |= C_BIT_SET;
    buffer[CHASTA_BIT38*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT39*2] |= C_BIT_SET;
    buffer[CHASTA_BIT39*2+1] |= C_BIT_SET;
}

/**
 * @brief setnlpcmchnsta
 */
void setnlpcmchnsta(char* buffer)
{
    if((buffer == NULL))
        return;

    /* sampling frequency default 48k */
    buffer[CHASTA_BIT24*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT24*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT25*2] |= C_BIT_SET;
    buffer[CHASTA_BIT25*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT26*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT26*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT27*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT27*2+1] &= C_BIT_UNSET;
    /* original sampling frequency */
    buffer[CHASTA_BIT36*2] |= C_BIT_SET;
    buffer[CHASTA_BIT36*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT37*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT37*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT38*2] |= C_BIT_SET;
    buffer[CHASTA_BIT38*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT39*2] |= C_BIT_SET;
    buffer[CHASTA_BIT39*2+1] |= C_BIT_SET;
}

void setddpchnsta(char* buffer)
{
    if((buffer == NULL))
        return;
    
    /* sampling frequency default 192k */
    buffer[CHASTA_BIT24*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT24*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT25*2] |= C_BIT_SET;
    buffer[CHASTA_BIT25*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT26*2] |= C_BIT_SET;
    buffer[CHASTA_BIT26*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT27*2] |= C_BIT_SET;
    buffer[CHASTA_BIT27*2+1] |= C_BIT_SET;
    /* original sampling frequency */
    buffer[CHASTA_BIT36*2] |= C_BIT_SET;
    buffer[CHASTA_BIT36*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT37*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT37*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT38*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT38*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT39*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT39*2+1] &= C_BIT_UNSET;
}


/**
 * @brief sethbrchnsta
 */
void sethbrchnsta(char* buffer)
{
    if((buffer == NULL))
        return;

    buffer[CHASTA_BIT24*2] |= C_BIT_SET;
    buffer[CHASTA_BIT24*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT25*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT25*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT26*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT26*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT27*2] |= C_BIT_SET;
    buffer[CHASTA_BIT27*2+1] |= C_BIT_SET;
    /* original sampling frequency */
    buffer[CHASTA_BIT36*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT36*2+1] &= C_BIT_UNSET;
    buffer[CHASTA_BIT37*2] |= C_BIT_SET;
    buffer[CHASTA_BIT37*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT38*2] |= C_BIT_SET;
    buffer[CHASTA_BIT38*2+1] |= C_BIT_SET;
    buffer[CHASTA_BIT39*2] &= C_BIT_UNSET;
    buffer[CHASTA_BIT39*2+1] &= C_BIT_UNSET;
}

void setChanSta(char* buffer,int samplerate, int channel)
{
    if(buffer == NULL)
        return;

    if (channel == 8) {
        sethbrchnsta(buffer);
    } else {
        switch (samplerate) {
        case 192000:
            setddpchnsta(buffer);
            break;
        case 176400:
            set176400chnsta(buffer);
            break;
        case 44100:
            set44100chnsta(buffer);
            break;
        case 32000:
            set32000chnsta(buffer);
            break;
        case 48000:
        default:
            setnlpcmchnsta(buffer);
            break;
        }
    }
}

void fill_hdmi_bitstream_buf(void * in, void* out,void* chan, int length)
{
    int temp, p, j = 0;
    char *ptr = (char *)in;
    char *ptr_end = (char *)in+length;
    char *newptr = (char *)out;
    char* channel = (char *)chan;
    if((ptr == NULL) || (newptr == NULL) || (channel == NULL) || (length <= 0))
        return ;

    while (ptr < ptr_end) {
        newptr[0] = (ptr[0]&0x1f)<<3;
        newptr[1] = ((ptr[0]&0xe0)>>5)|((ptr[1]&0x1f)<<3);
        newptr[2] = (ptr[1]&0xe0)>>5;
        newptr[2] |= channel[scount];
        temp = (newptr[2]<<24) | (newptr[1]<<16) | (newptr[0]<<8);
        j=0;
        p=0;
        while (j<31) {
            p ^= temp&0x1;
            p &= 0x1;
            temp >>= 1;
            j++;
        }
        newptr[2] |= (p&0x01)<<6;
        newptr[3] = 0x00;
        scount++;
        scount %= 384;
        ptr +=2;
        newptr +=4;
    }
}


/**
 * @brief dumpchnsta
 */
void dumpchnsta(char* buffer)
{
    if(buffer == NULL)
        return;

    for (int i=0; i<CHASTA_SUB_NUM; i+=16) {
        ALOGD("%02d: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x "
              "0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
              i/16, buffer[i], buffer[i+1], buffer[i+2], buffer[i+3],
              buffer[i+4], buffer[i+5], buffer[i+6], buffer[i+7],
              buffer[i+8], buffer[i+9], buffer[i+10], buffer[i+11],
              buffer[i+12], buffer[i+13], buffer[i+14], buffer[i+15]);
    }
}



