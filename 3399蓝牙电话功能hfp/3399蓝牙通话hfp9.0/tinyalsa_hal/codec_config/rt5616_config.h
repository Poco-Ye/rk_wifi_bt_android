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
/**
 * @file rt5616_config.h
 * @brief 
 * @author  RKAudio
 * @version 1.0.8
 * @date 2015-08-24
 */

#ifndef _RT5616_CONFIG_H_
#define _RT5616_CONFIG_H_

#include "config.h"

const struct config_control rt5616_speaker_normal_controls[] = {
    {
        .ctl_name = "SPK GPIO Control",
        .str_val = "Low",
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Volume",
        .int_val = {off, off},
    },
    {
        .ctl_name = "HP Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Channel Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX DAC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXR INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX DAC1 Switch",
        .int_val = {on},
    },/*
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {on},
    },
      {
        .ctl_name = "OUT Channel Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "OUT Playback Volume",
        .int_val = {31, 31},
    }, 
    */
};

const struct config_control rt5616_speaker_incall_controls[] = {

};

const struct config_control rt5616_speaker_ringtone_controls[] = {    
 
};

const struct config_control rt5616_speaker_voip_controls[] = {
 
};

const struct config_control rt5616_earpiece_normal_controls[] = {

};

const struct config_control rt5616_earpiece_incall_controls[] = {

};

const struct config_control rt5616_earpiece_ringtone_controls[] = {

};

const struct config_control rt5616_earpiece_voip_controls[] = {

};

const struct config_control rt5616_headphone_normal_controls[] = {
    {
        .ctl_name = "SPK GPIO Control",
        .str_val = "Low",
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Volume",
        .int_val = {off, off},
    },
    {
        .ctl_name = "HP Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Channel Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX DAC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXR INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    /*{
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    }, */
    {
        .ctl_name = "HPO MIX DAC1 Switch",
        .int_val = {on},
    },/*
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    }, */
};

const struct config_control rt5616_headphone_incall_controls[] = {
 
};

const struct config_control rt5616_headphone_ringtone_controls[] = {

};

const struct config_control rt5616_speaker_headphone_normal_controls[] = {
 
};

const struct config_control rt5616_speaker_headphone_ringtone_controls[] = {

};

const struct config_control rt5616_headphone_voip_controls[] = {

};

const struct config_control rt5616_headset_normal_controls[] = {
    {
        .ctl_name = "SPK GPIO Control",
        .str_val = "Low",
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Volume",
        .int_val = {off, off},
    },
    {
        .ctl_name = "HP Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Channel Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX DAC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXR INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    /*{
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    }, */
    {
        .ctl_name = "HPO MIX DAC1 Switch",
        .int_val = {on},
    },/*
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    }, */
};

const struct config_control rt5616_headset_incall_controls[] = {

};

const struct config_control rt5616_headset_ringtone_controls[] = {
 
};

const struct config_control rt5616_headset_voip_controls[] = {
 
};

const struct config_control rt5616_bluetooth_normal_controls[] = {

};

const struct config_control rt5616_bluetooth_incall_controls[] = {
 
};

const struct config_control rt5616_bluetooth_voip_controls[] = {
 
};

const struct config_control rt5616_main_mic_capture_controls[] = {
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXR BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Switch",
        .int_val = {on,on},
    },
   {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "IN2 Mode Control",
        .int_val = {0},
    },
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Volume",
        .int_val = {32,32},
    },
    {
        .ctl_name = "ADC Boost Gain",
        .int_val = {3,3},
    },
    {
        .ctl_name = "RECMIXR BST2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {on},
    },
};

const struct config_control rt5616_hands_free_mic_capture_controls[] = {
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXR BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Switch",
        .int_val = {on,on},
    },
   {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "IN1 Mode Control",
        .int_val = {0},
    },
    {
        .ctl_name = "IN1 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Volume",
        .int_val = {40,40},
    },
    {
        .ctl_name = "ADC Boost Gain",
        .int_val = {1,1},
    },
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST1 Switch",
        .int_val = {on},
    },
 
};

const struct config_control rt5616_bluetooth_sco_mic_capture_controls[] = {
 
};

const struct config_control rt5616_playback_off_controls[] = {
    {
        .ctl_name = "SPK GPIO Control",
        .str_val = "Low",
    },
/*
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "OUT Playback Volume",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "HP Playback Switch",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "OUT Channel Switch",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "HPO MIX DAC1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXR BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXR BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXR INR1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXL BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXL BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXL INL1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {0},
    },   
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC L1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC R1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "DAC MIXR INF1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {0, 0},
    }, 
*/ 
};

const struct config_control rt5616_capture_off_controls[] = {
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXR BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL BST1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Switch",
        .int_val = {0,0},
    },
   {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {0, 0},
    },
    {
        .ctl_name = "IN1 Mode Control",
        .int_val = {0},
    },
    {
        .ctl_name = "IN2 Mode Control",
        .int_val = {0},
    },
    {
        .ctl_name = "IN1 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Volume",
        .int_val = {0,0},
    },
    {
        .ctl_name = "ADC Boost Gain",
        .int_val = {0,0},
    },
    {
        .ctl_name = "IN Capture Volume",
        .int_val = {0,0},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {0},
    },
};

const struct config_control rt5616_incall_off_controls[] = {
 
};

const struct config_control rt5616_voip_off_controls[] = {

};

const struct config_route_table rt5616_config_table = {
    //speaker
    .speaker_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_speaker_normal_controls,
        .controls_count = sizeof(rt5616_speaker_normal_controls) / sizeof(struct config_control),
    },
    .speaker_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_speaker_incall_controls,
        .controls_count = sizeof(rt5616_speaker_incall_controls) / sizeof(struct config_control),
    },
    .speaker_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_speaker_ringtone_controls,
        .controls_count = sizeof(rt5616_speaker_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_speaker_voip_controls,
        .controls_count = sizeof(rt5616_speaker_voip_controls) / sizeof(struct config_control),
    },

    //earpiece
    .earpiece_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_earpiece_normal_controls,
        .controls_count = sizeof(rt5616_earpiece_normal_controls) / sizeof(struct config_control),
    },
    .earpiece_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_earpiece_incall_controls,
        .controls_count = sizeof(rt5616_earpiece_incall_controls) / sizeof(struct config_control),
    },
    .earpiece_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_earpiece_ringtone_controls,
        .controls_count = sizeof(rt5616_earpiece_ringtone_controls) / sizeof(struct config_control),
    },
    .earpiece_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_earpiece_voip_controls,
        .controls_count = sizeof(rt5616_earpiece_voip_controls) / sizeof(struct config_control),
    },

    //headphone
    .headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headphone_normal_controls,
        .controls_count = sizeof(rt5616_headphone_normal_controls) / sizeof(struct config_control),
    },
    .headphone_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headphone_incall_controls,
        .controls_count = sizeof(rt5616_headphone_incall_controls) / sizeof(struct config_control),
    },
    .headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headphone_ringtone_controls,
        .controls_count = sizeof(rt5616_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_speaker_headphone_normal_controls,
        .controls_count = sizeof(rt5616_speaker_headphone_normal_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_speaker_headphone_ringtone_controls,
        .controls_count = sizeof(rt5616_speaker_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .headphone_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headphone_voip_controls,
        .controls_count = sizeof(rt5616_headphone_voip_controls) / sizeof(struct config_control),
    },

    //headset
    .headset_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headset_normal_controls,
        .controls_count = sizeof(rt5616_headset_normal_controls) / sizeof(struct config_control),
    },
    .headset_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headset_incall_controls,
        .controls_count = sizeof(rt5616_headset_incall_controls) / sizeof(struct config_control),
    },
    .headset_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headset_ringtone_controls,
        .controls_count = sizeof(rt5616_headset_ringtone_controls) / sizeof(struct config_control),
    },
    .headset_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_headset_voip_controls,
        .controls_count = sizeof(rt5616_headset_voip_controls) / sizeof(struct config_control),
    },

    //bluetooth
    .bluetooth_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_bluetooth_normal_controls,
        .controls_count = sizeof(rt5616_bluetooth_normal_controls) / sizeof(struct config_control),
    },
    .bluetooth_incall = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt5616_bluetooth_incall_controls,
        .controls_count = sizeof(rt5616_bluetooth_incall_controls) / sizeof(struct config_control),
    },
    .bluetooth_voip = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt5616_bluetooth_voip_controls,
        .controls_count = sizeof(rt5616_bluetooth_voip_controls) / sizeof(struct config_control),
    },

    //capture
    .main_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_main_mic_capture_controls,
        .controls_count = sizeof(rt5616_main_mic_capture_controls) / sizeof(struct config_control),
    },
    .hands_free_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5616_hands_free_mic_capture_controls,
        .controls_count = sizeof(rt5616_hands_free_mic_capture_controls) / sizeof(struct config_control),
    },
    .bluetooth_sco_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt5616_bluetooth_sco_mic_capture_controls,
        .controls_count = sizeof(rt5616_bluetooth_sco_mic_capture_controls) / sizeof(struct config_control),
    },

    //off
    .playback_off = {
        .controls = rt5616_playback_off_controls,
        .controls_count = sizeof(rt5616_playback_off_controls) / sizeof(struct config_control),
    },
    .capture_off = {
        .controls = rt5616_capture_off_controls,
        .controls_count = sizeof(rt5616_capture_off_controls) / sizeof(struct config_control),
    },
    .incall_off = {
        .controls = rt5616_incall_off_controls,
        .controls_count = sizeof(rt5616_incall_off_controls) / sizeof(struct config_control),
    },
    .voip_off = {
        .controls = rt5616_voip_off_controls,
        .controls_count = sizeof(rt5616_voip_off_controls) / sizeof(struct config_control),
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


#endif //_RT5616_CONFIG_H_
