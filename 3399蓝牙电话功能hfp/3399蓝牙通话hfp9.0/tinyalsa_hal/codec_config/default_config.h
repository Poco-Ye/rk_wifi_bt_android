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
 * @file default_config.h
 * @brief 
 * @author  RkAudio
 * @version 1.0.8
 * @date 2015-08-24
 */

#ifndef _DEFAULT_CONFIG_H_
#define _DEFAULT_CONFIG_H_

#include "config.h"

const struct config_control default_speaker_normal_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "SPK",
    },
};

const struct config_control default_speaker_incall_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "SPK",
    },
    {
        .ctl_name = "Voice Call Path",
        .str_val = "SPK",
    },
};

const struct config_control default_speaker_ringtone_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "RING_SPK",
    },
};

const struct config_control default_speaker_voip_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "SPK",
    },
    {
        .ctl_name = "Voip Path",
        .str_val = "SPK",
    },
};

const struct config_control default_earpiece_normal_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "RCV",
    },
};

const struct config_control default_earpiece_incall_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "SPK",
    },
    {
        .ctl_name = "Voice Call Path",
        .str_val = "RCV",
    },
};

const struct config_control default_earpiece_ringtone_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "RCV",
    },
};

const struct config_control default_earpiece_voip_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "RCV",
    },
    {
        .ctl_name = "Voip Path",
        .str_val = "RCV",
    },
};

const struct config_control default_headphone_normal_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "HP_NO_MIC",
    },
};

const struct config_control default_headphone_incall_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "HP_NO_MIC",
    },
    {
        .ctl_name = "Voice Call Path",
        .str_val = "HP_NO_MIC",
    },
};

const struct config_control default_headphone_ringtone_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "RING_HP_NO_MIC",
    },
};

const struct config_control default_speaker_headphone_normal_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "SPK_HP",
    },
};

const struct config_control default_speaker_headphone_ringtone_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "RING_SPK_HP",
    },
};

const struct config_control default_headphone_voip_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "HP_NO_MIC",
    },
    {
        .ctl_name = "Voip Path",
        .str_val = "HP_NO_MIC",
    },
};

const struct config_control default_headset_normal_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "HP",
    },
};

const struct config_control default_headset_incall_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "HP",
    },
    {
        .ctl_name = "Voice Call Path",
        .str_val = "HP",
    },
};

const struct config_control default_headset_ringtone_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "RING_HP",
    },
};

const struct config_control default_headset_voip_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "HP",
    },
    {
        .ctl_name = "Voip Path",
        .str_val = "HP",
    },
};

const struct config_control default_bluetooth_normal_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "BT",
    },
};

const struct config_control default_bluetooth_incall_controls[] = {
    {
        .ctl_name = "Voice Call Path",
        .str_val = "BT",
    },
};

const struct config_control default_bluetooth_voip_controls[] = {
    {
        .ctl_name = "Voip Path",
        .str_val = "BT",
    },
};

const struct config_control default_main_mic_capture_controls[] = {
    {
        .ctl_name = "Capture MIC Path",
        .str_val = "Main Mic",
    },
};

const struct config_control default_hands_free_mic_capture_controls[] = {
    {
        .ctl_name = "Capture MIC Path",
        .str_val = "Hands Free Mic",
    },
};

const struct config_control default_bluetooth_sco_mic_capture_controls[] = {
    {
        .ctl_name = "Capture MIC Path",
        .str_val = "BT Sco Mic",
    },
};

const struct config_control default_playback_off_controls[] = {
    {
        .ctl_name = "Playback Path",
        .str_val = "OFF",
    },
};

const struct config_control default_capture_off_controls[] = {
    {
        .ctl_name = "Capture MIC Path",
        .str_val = "MIC OFF",
    },
};

const struct config_control default_incall_off_controls[] = {
    {
        .ctl_name = "Voice Call Path",
        .str_val = "OFF",
    },
};

const struct config_control default_voip_off_controls[] = {
    {
        .ctl_name = "Voip Path",
        .str_val = "OFF",
    },
};

const struct config_route_table default_config_table = {
    //speaker
    .speaker_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_speaker_normal_controls,
        .controls_count = sizeof(default_speaker_normal_controls) / sizeof(struct config_control),
    },
    .speaker_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_speaker_incall_controls,
        .controls_count = sizeof(default_speaker_incall_controls) / sizeof(struct config_control),
    },
    .speaker_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_speaker_ringtone_controls,
        .controls_count = sizeof(default_speaker_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_speaker_voip_controls,
        .controls_count = sizeof(default_speaker_voip_controls) / sizeof(struct config_control),
    },

    //earpiece
    .earpiece_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_earpiece_normal_controls,
        .controls_count = sizeof(default_earpiece_normal_controls) / sizeof(struct config_control),
    },
    .earpiece_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_earpiece_incall_controls,
        .controls_count = sizeof(default_earpiece_incall_controls) / sizeof(struct config_control),
    },
    .earpiece_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_earpiece_ringtone_controls,
        .controls_count = sizeof(default_earpiece_ringtone_controls) / sizeof(struct config_control),
    },
    .earpiece_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_earpiece_voip_controls,
        .controls_count = sizeof(default_earpiece_voip_controls) / sizeof(struct config_control),
    },

    //headphone
    .headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headphone_normal_controls,
        .controls_count = sizeof(default_headphone_normal_controls) / sizeof(struct config_control),
    },
    .headphone_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headphone_incall_controls,
        .controls_count = sizeof(default_headphone_incall_controls) / sizeof(struct config_control),
    },
    .headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headphone_ringtone_controls,
        .controls_count = sizeof(default_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_speaker_headphone_normal_controls,
        .controls_count = sizeof(default_speaker_headphone_normal_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_speaker_headphone_ringtone_controls,
        .controls_count = sizeof(default_speaker_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .headphone_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headphone_voip_controls,
        .controls_count = sizeof(default_headphone_voip_controls) / sizeof(struct config_control),
    },

    //headset
    .headset_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headset_normal_controls,
        .controls_count = sizeof(default_headset_normal_controls) / sizeof(struct config_control),
    },
    .headset_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headset_incall_controls,
        .controls_count = sizeof(default_headset_incall_controls) / sizeof(struct config_control),
    },
    .headset_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headset_ringtone_controls,
        .controls_count = sizeof(default_headset_ringtone_controls) / sizeof(struct config_control),
    },
    .headset_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_headset_voip_controls,
        .controls_count = sizeof(default_headset_voip_controls) / sizeof(struct config_control),
    },

    //bluetooth
    .bluetooth_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_bluetooth_normal_controls,
        .controls_count = sizeof(default_bluetooth_normal_controls) / sizeof(struct config_control),
    },
    .bluetooth_incall = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = default_bluetooth_incall_controls,
        .controls_count = sizeof(default_bluetooth_incall_controls) / sizeof(struct config_control),
    },
    .bluetooth_voip = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = default_bluetooth_voip_controls,
        .controls_count = sizeof(default_bluetooth_voip_controls) / sizeof(struct config_control),
    },

    //capture
    .main_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_main_mic_capture_controls,
        .controls_count = sizeof(default_main_mic_capture_controls) / sizeof(struct config_control),
    },
    .hands_free_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = default_hands_free_mic_capture_controls,
        .controls_count = sizeof(default_hands_free_mic_capture_controls) / sizeof(struct config_control),
    },
    .bluetooth_sco_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = default_bluetooth_sco_mic_capture_controls,
        .controls_count = sizeof(default_bluetooth_sco_mic_capture_controls) / sizeof(struct config_control),
    },

    //off
    .playback_off = {
        .controls = default_playback_off_controls,
        .controls_count = sizeof(default_playback_off_controls) / sizeof(struct config_control),
    },
    .capture_off = {
        .controls = default_capture_off_controls,
        .controls_count = sizeof(default_capture_off_controls) / sizeof(struct config_control),
    },
    .incall_off = {
        .controls = default_incall_off_controls,
        .controls_count = sizeof(default_incall_off_controls) / sizeof(struct config_control),
    },
    .voip_off = {
        .controls = default_voip_off_controls,
        .controls_count = sizeof(default_voip_off_controls) / sizeof(struct config_control),
    },
#ifdef BOX_HAL
    //hdmi
    .hdmi_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls_count = 0,
    },
#else
    //hdmi
    .hdmi_normal = {
        .sound_card = 1,
        .devices = DEVICES_0,
        .controls_count = 0,
    },
#endif
    //spdif
    .spdif_normal = {
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


#endif //_DEFAULT_CONFIG_H_
