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
 * @file amix.c
 * @brief 
 * @author  RkAudio
 * @version 1.0.8
 * @date 2015-08-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "alsa_audio.h"


/**
 * @brief get_ctl 
 *
 * @param mixer
 * @param name
 *
 * @returns 
 */
struct mixer_ctl *get_ctl(struct mixer *mixer, char *name)
{
    char *p;
    unsigned idx = 0;

    if (isdigit(name[0]))
        return mixer_get_nth_control(mixer, atoi(name) - 1);

    p = strrchr(name, '#');
    if (p) {
        *p++ = 0;
        idx = atoi(p);
    }

    return mixer_get_control(mixer, name, idx);
}

int main(int argc, char **argv)
{
    struct mixer *mixer;
    struct mixer_ctl *ctl;
    int card = 0;
    int r, i, c;
	//struct audio_route *ar;
    for (i = 0; i < argc; i++) {
        if ((strncmp(argv[i], "-c", sizeof(argv[i])) == 0) ||
            (strncmp(argv[i], "-card", sizeof(argv[i])) == 0)) {

            i++;
            if (i >= argc) {
                argc -= 1;
                argv += 1;
                break;
            }

            card = atoi(argv[i]);
            argc -= 2;
            argv += 2;
            break;
        }
    }

    printf("Card:%i\n", card);

    
	mixer = mixer_open_legacy(card);

    if (!mixer)
        return -1;

    if (argc == 1) {
        mixer_dump(mixer);
        return 0;
    }

    ctl = get_ctl(mixer, argv[1]);
    argc -= 2;
    argv += 2;

    if (!ctl) {
        printf("can't find control\n");
        return -1;
    }

    if (argc) {
        if (isdigit(argv[0][0]))
            r = mixer_ctl_set_int(ctl, atoi(argv[0]));
        else
            r = mixer_ctl_select(ctl, argv[0]);
        if (r)
            printf("oops: %s\n", strerror(errno));
    }

    mixer_ctl_print(ctl);

    mixer_close_legacy(mixer);

    return 0;
}
