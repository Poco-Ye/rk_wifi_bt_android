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
#ifndef _ES8396_CONFIG_H_
#define _ES8396_CONFIG_H_

#include "config.h"

const struct config_control es8396_speaker_normal_controls[] = {
/*
    {
        .ctl_name = "HPR Mix DACR2HPMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPL Mix DACL2HPMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC_1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Amp Switch",
        .int_val = {on},
    },
*/
};

// for BT client call
const struct config_control es8396_speaker_incall_controls[] = {
    /*down link*/
    {
        .ctl_name = "DACSRC Mux",
        .int_val = {1},
    },
    {
        .ctl_name = "DAC_1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPR Mix DACR2HPMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPL Mix DACL2HPMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Amp Switch",
        .int_val = {on},
    },
    /*up link*/
    {
        .ctl_name = "LLNMIX2LPGA Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RLNMIX2RPGA Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LLNIN Mix PMICDSE2LLNMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RLNIN Mix NMICDSE2RLNMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "AMIC Mux Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "MASTERSDPO Mux",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC_1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Internal Mic Switch",
        .int_val = {on},
    },
};

const struct config_control es8396_headphone_normal_controls[] = {
    {
        .ctl_name = "HPR Mix DACR2HPMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPL Mix DACL2HPMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC_1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Amp Switch",
        .int_val = {on},
    },
};

const struct config_control es8396_main_mic_capture_controls[] = {
    {
        .ctl_name = "LLNMIX2LPGA Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RLNMIX2RPGA Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LLNIN Mix PMICDSE2LLNMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RLNIN Mix NMICDSE2RLNMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "AMIC Mux Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "VOICESDPO Mux",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC_1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Internal Mic Switch",
        .int_val = {on},
    },
};

const struct config_control es8396_hands_free_mic_capture_controls[] = {
    {
        .ctl_name = "LLNMIX2LPGA Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RLNMIX2RPGA Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LLNIN Mix PMICDSE2LLNMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RLNIN Mix NMICDSE2RLNMIX Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "AMIC Mux Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "VOICESDPO Mux",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC_1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Internal Mic Switch",
        .int_val = {on},
    },
};

const struct config_control es8396_playback_off_controls[] = {
#if 0
    {
        .ctl_name = "HPR Mix DACR2HPMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPL Mix DACL2HPMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC_1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HP Amp Switch",
        .int_val = {off},
    },
#endif
};

const struct config_control es8396_capture_off_controls[] = {
    {
        .ctl_name = "LLNMIX2LPGA Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RLNMIX2RPGA Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LLNIN Mix PMICDSE2LLNMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RLNIN Mix NMICDSE2RLNMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "AMIC Mux Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "VOICESDPO Mux",
        .int_val = {3},
    },
    {
        .ctl_name = "ADC_1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Internal Mic Switch",
        .int_val = {off},
    },
};

const struct config_control es8396_incall_off_controls[] = {
    /*TODO*/
    /*downlink*/
    {
        .ctl_name = "HPR Mix DACR2HPMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPL Mix DACL2HPMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC_1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HP Amp Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DACSRC Mux",
        .int_val = {0},
    },
    /*uplink*/
    {
        .ctl_name = "LLNMIX2LPGA Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RLNMIX2RPGA Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LLNIN Mix PMICDSE2LLNMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RLNIN Mix NMICDSE2RLNMIX Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "AMIC Mux Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "MASTERSDPO Mux",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC_1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Internal Mic Switch",
        .int_val = {off},
    },
#if 1
    {
        .ctl_name = "RDMIX2 Mux",
        .int_val = {0},
    },
    {
        .ctl_name = "LDMIX2 Mux",
        .int_val = {0},
    },
    {
        .ctl_name = "RDMIX1 Mux",
        .int_val = {3},
    },
    {
        .ctl_name = "LDMIX1 Mux",
        .int_val = {0},
    },
#endif
};

const struct config_route_table es8396_config_table = {
    //speaker
    .speaker_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = es8396_speaker_normal_controls,
        .controls_count = sizeof(es8396_speaker_normal_controls) / sizeof(struct config_control),
    },
    .speaker_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = es8396_speaker_incall_controls,
        .controls_count = sizeof(es8396_speaker_incall_controls) / sizeof(struct config_control),
    },

    //headphone
    .headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = es8396_headphone_normal_controls,
        .controls_count = sizeof(es8396_headphone_normal_controls) / sizeof(struct config_control),
    },

    //capture
    .main_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = es8396_main_mic_capture_controls,
        .controls_count = sizeof(es8396_main_mic_capture_controls) / sizeof(struct config_control),
    },
    .hands_free_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = es8396_hands_free_mic_capture_controls,
        .controls_count = sizeof(es8396_hands_free_mic_capture_controls) / sizeof(struct config_control),
    },

    //off
    .playback_off = {
        .controls = es8396_playback_off_controls,
        .controls_count = sizeof(es8396_playback_off_controls) / sizeof(struct config_control),
    },
    .capture_off = {
        .controls = es8396_capture_off_controls,
        .controls_count = sizeof(es8396_capture_off_controls) / sizeof(struct config_control),
    },
    .incall_off = {
        .controls = es8396_incall_off_controls,
        .controls_count = sizeof(es8396_incall_off_controls) / sizeof(struct config_control),
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

#endif //_ES8396_CONFIG_H_
