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
 * @file rt3224_config.h
 * @brief 
 * @author  RkAudio
 * @version 1.0.8
 * @date 2015-08-24
 */

#ifndef _RT3224_CONFIG_H_
#define _RT3224_CONFIG_H_

#include "config.h"

const struct config_control rt3224_speaker_normal_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",               
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Speaker Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
};

const struct config_control rt3224_speaker_incall_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {1},
    },  

    //OPEN ROUTE 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC L1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {on},
    },

    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },

    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127
    {
        .ctl_name = "ADC Capture Volume",                  
        .int_val = {55, 55},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
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
        .ctl_name = "IF2 ADC R Mux",
        .str_val = "Mono ADC MIXR",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDP_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_ADC",
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {on},
    },

    //"Single ended"=0, "Differential"=1
    {
        .ctl_name = "IN1 Mode Control",
        .str_val = "Differential",
    },
    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN1 Boost",
        .int_val = {4},
    },
    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127  
    {
        .ctl_name = "Mono ADC Capture Volume",
        .int_val = {47, 47},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //OPEN KEY TONE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {on},
    },

    //speaker normal
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //headphone && headset incall

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
};

const struct config_control rt3224_speaker_ringtone_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Speaker Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
};

const struct config_control rt3224_speaker_voip_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",               
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Speaker Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
};

const struct config_control rt3224_earpiece_normal_controls[] = {

};

const struct config_control rt3224_earpiece_incall_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {1},
    },  

    //OPEN ROUTE 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC L1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {on},
    },

    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },

    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127
    {
        .ctl_name = "ADC Capture Volume",                  
        .int_val = {55, 55},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
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
        .ctl_name = "IF2 ADC R Mux",
        .str_val = "Mono ADC MIXR",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDP_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_ADC",
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {on},
    },

    //"Single ended"=0, "Differential"=1
    {
        .ctl_name = "IN1 Mode Control",
        .str_val = "Differential",
    },
    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN1 Boost",
        .int_val = {4},
    },
    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127  
    {
        .ctl_name = "Mono ADC Capture Volume",
        .int_val = {47, 47},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //OPEN KEY TONE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {on},
    },

    //speaker normal
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //headphone && headset incall

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
};

const struct config_control rt3224_earpiece_ringtone_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Speaker Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
};

const struct config_control rt3224_earpiece_voip_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",               
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },  

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Speaker Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
};

const struct config_control rt3224_headphone_normal_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },  

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //speaker normal
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_headphone_incall_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {1},
    },  

    //OPEN ROUTE 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC L1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },

    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127
    {
        .ctl_name = "ADC Capture Volume",                  
        .int_val = {55, 55},
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
        .ctl_name = "IF2 ADC R Mux",
        .str_val = "Mono ADC MIXR",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDP_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_ADC",
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {on},
    },

    //"Single ended"=0, "Differential"=1
    {
        .ctl_name = "IN1 Mode Control",
        .str_val = "Differential",
    },
    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN1 Boost",
        .int_val = {4},
    },
    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127  
    {
        .ctl_name = "Mono ADC Capture Volume",
        .int_val = {47, 47},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //OPEN KEY TONE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {on},
    },

    //speaker normal
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {on, on},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_headphone_ringtone_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },        
        
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },  

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //speaker normal
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_speaker_headphone_normal_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Speaker Playback Volume",
        .int_val = {31, 31},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_speaker_headphone_ringtone_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },        
        
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Speaker Playback Volume",
        .int_val = {31, 31},
    },
    //min=0,max=10
    {
        .ctl_name = "Class D SPK Ratio Control",
        .int_val = {10},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {on, on},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_headphone_voip_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },

    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },  

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //speaker normal
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_headset_normal_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },        
        
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },  

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //speaker normal
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_headset_incall_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },        
        
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {1},
    },  

    //OPEN ROUTE 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC L1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },

    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127
    {
        .ctl_name = "ADC Capture Volume",                  
        .int_val = {55, 55},
    },

    {
        .ctl_name = "RECMIXR BST3 Switch",
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
        .ctl_name = "IF2 ADC R Mux",
        .str_val = "Mono ADC MIXR",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDP_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_ADC",
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {on},
    },

    //"Single ended"=0, "Differential"=1
    {
        .ctl_name = "IN3 Mode Control",
        .str_val = "Single ended",
    },
    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN3 Boost",
        .int_val = {4},
    },
    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127  
    {
        .ctl_name = "Mono ADC Capture Volume",
        .int_val = {47, 47},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //OPEN KEY TONE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {on},
    },

    //speaker normal
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {on, on},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_headset_ringtone_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },        
        
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },  

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //speaker normal
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_headset_voip_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },        
        
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },  

    //OPEN ROUTE
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
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
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },

    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=31
    {
        .ctl_name = "Headphone Playback Volume",
        .int_val = {31, 31},
    },
    //dBscale-min=-65.625dB,step=0.375dB,min=0,max=175
    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },

    //speaker normal
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {on},
    },
*/
};

const struct config_control rt3224_bluetooth_normal_controls[] = {

};

const struct config_control rt3224_bluetooth_incall_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },
        
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {1},
    },  

    //INF1_DAC -> DAC MIXL
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {on},
    },

    {
        .ctl_name = "Mono ADC Capture Volume",        
        .int_val = {127, 127},
    },
    {
        .ctl_name = "Mono DAC Playback Volume",       
        .int_val = {175, 175},
    },
    //dBscale-min=-46.50dB,step=1.50dB,min=0,max=39
    {
        .ctl_name = "OUT Playback Volume",
        .int_val = {39, 39},
    },

    //IN2 -> ADC_L -> Stereo_ADC_Mixer_L -> IF1_ADC_L  
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC L1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {on},
    },

    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Volume",
        .int_val = {45, 45},
    },   

    //speaker normal
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",
        .int_val = {off},
    },

    //speaker incall 
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //headphone && headset incall

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
};

const struct config_control rt3224_bluetooth_voip_controls[] = {
    //close speaker
    {
        .ctl_name = "SPK MIXL DAC L2 Switch",             
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR DAC R2 Switch",             
        .int_val = {off},
    },

    // IF2 DAC L ->DAC L2 Volume ->DIG MIXL ->Stereo ADC L2 Mux ->Stereo ADC MIXL ->IF1_ADC_L 
    {
        .ctl_name = "DAC L2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "DIG MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC L2 Mux",  
        .str_val = "DMIC1",
    },
    {
        .ctl_name = "Stereo ADC L2 Mux",  
        .str_val = "DIG MIX",
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC R2 Mux",
        .str_val = "IF2",
    },
    {
        .ctl_name = "Mono dacr Mux",
        .str_val = "TxDC_R",
    },
    {
        .ctl_name = "DACR Select",
        .str_val = "IF2_DAC",
    },
    {
        .ctl_name = "DIG MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC R2 Mux",  
        .str_val = "DMIC1",
    },
    {
        .ctl_name = "Stereo ADC R2 Mux",  
        .str_val = "DIG MIX",
    },
    {
        .ctl_name = "Stereo ADC MIXR ADC2 Switch",
        .int_val = {on},
    },
    // MX-2C[15]   MX-2C[11] 
    {
        .ctl_name = "DIG MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DIG MIXR DAC R1 Switch",
        .int_val = {off},
    },
    // MX-29[15]   MX-29[7]  
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",  
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",  
        .int_val = {off},
    },
    // DIG MIXL ->Stereo ADC L1 Mux ->Stereo ADC MIXL 
    {
        .ctl_name = "Stereo ADC L1 Mux",  
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo ADC L1 Mux",  
        .str_val = "DIG MIX",
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo ADC R1 Mux",  
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo ADC R1 Mux",  
        .str_val = "DIG MIX",
    },
    {
        .ctl_name = "Stereo ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },    
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL DAC L1 Switch",  
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
/*
    {
        .ctl_name = "HP mute Switch",
        .int_val = {off},
    },
*/
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Enable",
    },      

    {
        .ctl_name = "Mono DAC Playback Volume",
        .int_val = {175, 175},
    },
    {
        .ctl_name = "ADC Capture Volume", 
        .int_val = {47, 47},
    },
};

const struct config_control rt3224_main_mic_capture_controls[] = {
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },

    //OPEN ROUTE
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
        .ctl_name = "IF2 ADC R Mux",
        .str_val = "Mono ADC MIXR",
    },
    {
        .ctl_name = "ADC IF2 Data Switch",
        .str_val = "right copy to left",
    },

    //"Single ended"=0, "Differential"=1
    {
        .ctl_name = "IN1 Mode Control",
        .str_val = "Differential",
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

const struct config_control rt3224_hands_free_mic_capture_controls[] = {
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {off},
    },

    //OPEN ROUTE
    {
        .ctl_name = "RECMIXR BST3 Switch",
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
        .ctl_name = "IF2 ADC R Mux",
        .str_val = "Mono ADC MIXR",
    },
    {
        .ctl_name = "ADC IF2 Data Switch",
        .str_val = "right copy to left",
    },

    //"Single ended"=0, "Differential"=1
    {
        .ctl_name = "IN3 Mode Control",
        .str_val = "Single ended",
    },
    //min=0,max=8, bypass=0=0db, 30db=3, 52db=8
    {
        .ctl_name = "IN3 Boost",
        .int_val = {5},
    },
    //dBscale-min=-17.625dB,step=0.375dB,min=0,max=127  
    {
        .ctl_name = "Mono ADC Capture Volume",
        .int_val = {60, 60},
    },
};

const struct config_control rt3224_bluetooth_sco_mic_capture_controls[] = {
    // IF1_DAC_L -> DACL1 -> Mono_DAC_Mixer_L -> Mono ADC L1 Mux  ->Mono ADC MIXL->IF2 ADC L Mux->  IF2_ADC_L  
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono ADC L1 Mux",  
        .str_val = "Mono DAC MIXL",
    },
    {
        .ctl_name = "Mono ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "IF2 ADC L Mux",
        .str_val = "Mono ADC MIXL",
    },
    {
        .ctl_name = "ADC IF2 Data Switch",
        .str_val = "Normal",
    },
    {
        .ctl_name = "DAC MIXR INF1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Mono ADC R1 Mux",  
        .str_val = "Mono DAC MIXR",
    },
    {
        .ctl_name = "Mono ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "IF2 ADC R Mux",
        .str_val = "Mono ADC MIXR",
    },
    //  MX-2B[12]       MX-2B[10]      MX-2B[4]       MX-2B[2]  
    {
        .ctl_name = "Mono DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono ADC Capture Volume",
        .int_val = {47, 47},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
};

const struct config_control rt3224_playback_off_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },
/*
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },

    //speaker incall
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
*/
};

const struct config_control rt3224_capture_off_controls[] = {
    {
        .ctl_name = "RECMIXR BST1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
};

const struct config_control rt3224_incall_off_controls[] = {
    //disable ASRC
    {
        .ctl_name = "ASRC Switch",
        .str_val = "Disable",
    },
    {
        .ctl_name = "Speaker Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "OUT Playback Switch",
        .int_val = {off, off},
    },
    {
        .ctl_name = "Modem Input Switch",
        .int_val = {0},
    },

    //speaker incall 
    {
        .ctl_name = "RECMIXL BST2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo ADC MIXL ADC1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Mono DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXL OUT MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "SPK MIXR OUT MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {off},
    },

    //headphone && headset normal
    {
        .ctl_name = "OUT MIXR DAC R2 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {off},
    },

    //bt incall
    {
        .ctl_name = "DAC MIXL INF1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {off},
    },

    //close other mixer 
    {
        .ctl_name = "OUT MIXL REC MIXL Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "OUT MIXR REC MIXR Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
};

const struct config_control rt3224_voip_off_controls[] = {

};

const struct config_route_table rt3224_config_table = {
    //speaker
    .speaker_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_speaker_normal_controls,
        .controls_count = sizeof(rt3224_speaker_normal_controls) / sizeof(struct config_control),
    },
    .speaker_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_speaker_incall_controls,
        .controls_count = sizeof(rt3224_speaker_incall_controls) / sizeof(struct config_control),
    },
    .speaker_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_speaker_ringtone_controls,
        .controls_count = sizeof(rt3224_speaker_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_speaker_voip_controls,
        .controls_count = sizeof(rt3224_speaker_voip_controls) / sizeof(struct config_control),
    },

    //earpiece
    .earpiece_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_earpiece_normal_controls,
        .controls_count = sizeof(rt3224_earpiece_normal_controls) / sizeof(struct config_control),
    },
    .earpiece_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_earpiece_incall_controls,
        .controls_count = sizeof(rt3224_earpiece_incall_controls) / sizeof(struct config_control),
    },
    .earpiece_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_earpiece_ringtone_controls,
        .controls_count = sizeof(rt3224_earpiece_ringtone_controls) / sizeof(struct config_control),
    },
    .earpiece_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_earpiece_voip_controls,
        .controls_count = sizeof(rt3224_earpiece_voip_controls) / sizeof(struct config_control),
    },

    //headphone
    .headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headphone_normal_controls,
        .controls_count = sizeof(rt3224_headphone_normal_controls) / sizeof(struct config_control),
    },
    .headphone_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headphone_incall_controls,
        .controls_count = sizeof(rt3224_headphone_incall_controls) / sizeof(struct config_control),
    },
    .headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headphone_ringtone_controls,
        .controls_count = sizeof(rt3224_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_speaker_headphone_normal_controls,
        .controls_count = sizeof(rt3224_speaker_headphone_normal_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_speaker_headphone_ringtone_controls,
        .controls_count = sizeof(rt3224_speaker_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .headphone_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headphone_voip_controls,
        .controls_count = sizeof(rt3224_headphone_voip_controls) / sizeof(struct config_control),
    },

    //headset
    .headset_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headset_normal_controls,
        .controls_count = sizeof(rt3224_headset_normal_controls) / sizeof(struct config_control),
    },
    .headset_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headset_incall_controls,
        .controls_count = sizeof(rt3224_headset_incall_controls) / sizeof(struct config_control),
    },
    .headset_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headset_ringtone_controls,
        .controls_count = sizeof(rt3224_headset_ringtone_controls) / sizeof(struct config_control),
    },
    .headset_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_headset_voip_controls,
        .controls_count = sizeof(rt3224_headset_voip_controls) / sizeof(struct config_control),
    },

    //bluetooth
    .bluetooth_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_bluetooth_normal_controls,
        .controls_count = sizeof(rt3224_bluetooth_normal_controls) / sizeof(struct config_control),
    },
    .bluetooth_incall = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt3224_bluetooth_incall_controls,
        .controls_count = sizeof(rt3224_bluetooth_incall_controls) / sizeof(struct config_control),
    },
    .bluetooth_voip = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt3224_bluetooth_voip_controls,
        .controls_count = sizeof(rt3224_bluetooth_voip_controls) / sizeof(struct config_control),
    },

    //capture
    .main_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_main_mic_capture_controls,
        .controls_count = sizeof(rt3224_main_mic_capture_controls) / sizeof(struct config_control),
    },
    .hands_free_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt3224_hands_free_mic_capture_controls,
        .controls_count = sizeof(rt3224_hands_free_mic_capture_controls) / sizeof(struct config_control),
    },
    .bluetooth_sco_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt3224_bluetooth_sco_mic_capture_controls,
        .controls_count = sizeof(rt3224_bluetooth_sco_mic_capture_controls) / sizeof(struct config_control),
    },

    //off
    .playback_off = {
        .controls = rt3224_playback_off_controls,
        .controls_count = sizeof(rt3224_playback_off_controls) / sizeof(struct config_control),
    },
    .capture_off = {
        .controls = rt3224_capture_off_controls,
        .controls_count = sizeof(rt3224_capture_off_controls) / sizeof(struct config_control),
    },
    .incall_off = {
        .controls = rt3224_incall_off_controls,
        .controls_count = sizeof(rt3224_incall_off_controls) / sizeof(struct config_control),
    },
    .voip_off = {
        .controls = rt3224_voip_off_controls,
        .controls_count = sizeof(rt3224_voip_off_controls) / sizeof(struct config_control),
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


#endif //_RT3224_CONFIG_H_
