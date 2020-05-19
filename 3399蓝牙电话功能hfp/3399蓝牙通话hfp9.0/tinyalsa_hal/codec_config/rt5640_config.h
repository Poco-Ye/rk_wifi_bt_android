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
#ifndef _RT5640_CONFIG_H_
#define _RT5640_CONFIG_H_

#include "config.h"

const struct config_control rt5640_speaker_normal_controls[] = {
    {
        .ctl_name = "DAI select",
        .str_val = "1:2|2:1",
    },
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    {
        .ctl_name = "DAC2 Playback Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX DAC2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP R Playback Switch",
        .int_val = {on},
    },

};

const struct config_control rt5640_headphone_normal_controls[] = {
    {
        .ctl_name = "DAI select",
        .str_val = "1:2|2:1",
    },
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    {
        .ctl_name = "DAC2 Playback Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX DAC2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP R Playback Switch",
        .int_val = {on},
    },
};

const struct config_control rt5640_main_mic_capture_controls[] = {
    {
        .ctl_name = "DAI select",
        .str_val = "1:2|2:1",
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono ADC R1 Mux",
        .str_val = "ADCR",
    },
    {
        .ctl_name = "Mono ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "ADC IF2 Data Switch",
        .str_val = "right copy to left",
    },
    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN1 Boost",
        .int_val = {5},
    },
    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127
    {
        .ctl_name = "Mono ADC Capture Volume",
        .int_val = {60, 60},
    },
};

const struct config_control rt5640_playback_off_controls[] = {
    {
        .ctl_name = "HP L Playback Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HP R Playback Switch",
        .int_val = {off},
    },

};

const struct config_control rt5640_capture_off_controls[] = {
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
};


const struct config_route_table rt5640_config_table = {
    //speaker
    .speaker_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5640_speaker_normal_controls,
        .controls_count = sizeof(rt5640_speaker_normal_controls) / sizeof(struct config_control),
    },

    //headphone
    .headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5640_headphone_normal_controls,
        .controls_count = sizeof(rt5640_headphone_normal_controls) / sizeof(struct config_control),
    },

    //capture
    .main_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5640_main_mic_capture_controls,
        .controls_count = sizeof(rt5640_main_mic_capture_controls) / sizeof(struct config_control),
    },

    //off
    .playback_off = {
        .controls = rt5640_playback_off_controls,
        .controls_count = sizeof(rt5640_playback_off_controls) / sizeof(struct config_control),
    },
    .capture_off = {
        .controls = rt5640_capture_off_controls,
        .controls_count = sizeof(rt5640_capture_off_controls) / sizeof(struct config_control),
    },

    //hdmi
    .hdmi_normal = {
        .sound_card = 1,
        .devices = DEVICES_0,
        .controls_count = 0,
    },

    //usb audio
    .usb_normal = {
        .sound_card = 2,
        .devices = DEVICES_0,
        .controls_count = 0,
    },
    .usb_capture = {
        .sound_card = 2,
        .devices = DEVICES_0,
        .controls_count = 0,
    },
};

#endif //_RT5640_CONFIG_H_
