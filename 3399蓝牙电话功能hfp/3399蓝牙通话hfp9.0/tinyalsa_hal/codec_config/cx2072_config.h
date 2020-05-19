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
#ifndef _CX2072_CONFIG_H_
#define _CX2072_CONFIG_H_

#include "config.h"

const struct config_control cx2072_speaker_normal_controls[] = {
    {
        .ctl_name = "PortG Mux",
        .int_val = {0},
    },
};

const struct config_control cx2072_speaker_incall_controls[] = {
};

const struct config_control cx2072_speaker_ringtone_controls[] = {
};

const struct config_control cx2072_speaker_voip_controls[] = {
};

const struct config_control cx2072_earpiece_normal_controls[] = {
};

const struct config_control cx2072_earpiece_incall_controls[] = {
};

const struct config_control cx2072_earpiece_ringtone_controls[] = {
};

const struct config_control cx2072_earpiece_voip_controls[] = {
};

const struct config_control cx2072_headphone_normal_controls[] = {
    {
        .ctl_name = "PortG Mux",
        .int_val = {1},
    },
};

const struct config_control cx2072_headphone_incall_controls[] = {
};

const struct config_control cx2072_headphone_ringtone_controls[] = {
};

const struct config_control cx2072_speaker_headphone_normal_controls[] = {
};

const struct config_control cx2072_speaker_headphone_ringtone_controls[] = {
};

const struct config_control cx2072_headphone_voip_controls[] = {
};

const struct config_control cx2072_headset_normal_controls[] = {
    {
        .ctl_name = "PortG Mux",
        .int_val = {1},
    },
};

const struct config_control cx2072_headset_incall_controls[] = {
};

const struct config_control cx2072_headset_ringtone_controls[] = {
};

const struct config_control cx2072_headset_voip_controls[] = {
};

const struct config_control cx2072_bluetooth_normal_controls[] = {
};

const struct config_control cx2072_bluetooth_incall_controls[] = {
};

const struct config_control cx2072_bluetooth_voip_controls[] = {
};

const struct config_control cx2072_main_mic_capture_controls[] = {
    {
        .ctl_name = "ADC1 Mux",
        .int_val = {2},
    },
    {
        .ctl_name = "PortC Boost",
        .int_val = {2, 2},
    },
};

const struct config_control cx2072_hands_free_mic_capture_controls[] = {
    {
        .ctl_name = "ADC1 Mux",
        .int_val = {1},
    },
    {
        .ctl_name = "PortD Boost",
        .int_val = {2, 2},
    },
};

const struct config_control cx2072_bluetooth_sco_mic_capture_controls[] = {
    {
        .ctl_name = "PortG Mux",
        .int_val = {1},
    },
};

const struct config_control cx2072_playback_off_controls[] = {
};

const struct config_control cx2072_capture_off_controls[] = {
};

const struct config_control cx2072_incall_off_controls[] = {
};

const struct config_control cx2072_voip_off_controls[] = {
};

const struct config_route_table cx2072_config_table = {
    //speaker
    .speaker_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_speaker_normal_controls,
        .controls_count = sizeof(cx2072_speaker_normal_controls) / sizeof(struct config_control),
    },
    .speaker_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_speaker_incall_controls,
        .controls_count = sizeof(cx2072_speaker_incall_controls) / sizeof(struct config_control),
    },
    .speaker_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_speaker_ringtone_controls,
        .controls_count = sizeof(cx2072_speaker_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_speaker_voip_controls,
        .controls_count = sizeof(cx2072_speaker_voip_controls) / sizeof(struct config_control),
    },

    //earpiece
    .earpiece_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_earpiece_normal_controls,
        .controls_count = sizeof(cx2072_earpiece_normal_controls) / sizeof(struct config_control),
    },
    .earpiece_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_earpiece_incall_controls,
        .controls_count = sizeof(cx2072_earpiece_incall_controls) / sizeof(struct config_control),
    },
    .earpiece_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_earpiece_ringtone_controls,
        .controls_count = sizeof(cx2072_earpiece_ringtone_controls) / sizeof(struct config_control),
    },
    .earpiece_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_earpiece_voip_controls,
        .controls_count = sizeof(cx2072_earpiece_voip_controls) / sizeof(struct config_control),
    },

    //headphone
    .headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headphone_normal_controls,
        .controls_count = sizeof(cx2072_headphone_normal_controls) / sizeof(struct config_control),
    },
    .headphone_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headphone_incall_controls,
        .controls_count = sizeof(cx2072_headphone_incall_controls) / sizeof(struct config_control),
    },
    .headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headphone_ringtone_controls,
        .controls_count = sizeof(cx2072_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_speaker_headphone_normal_controls,
        .controls_count = sizeof(cx2072_speaker_headphone_normal_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_speaker_headphone_ringtone_controls,
        .controls_count = sizeof(cx2072_speaker_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .headphone_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headphone_voip_controls,
        .controls_count = sizeof(cx2072_headphone_voip_controls) / sizeof(struct config_control),
    },

    //headset
    .headset_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headset_normal_controls,
        .controls_count = sizeof(cx2072_headset_normal_controls) / sizeof(struct config_control),
    },
    .headset_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headset_incall_controls,
        .controls_count = sizeof(cx2072_headset_incall_controls) / sizeof(struct config_control),
    },
    .headset_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headset_ringtone_controls,
        .controls_count = sizeof(cx2072_headset_ringtone_controls) / sizeof(struct config_control),
    },
    .headset_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_headset_voip_controls,
        .controls_count = sizeof(cx2072_headset_voip_controls) / sizeof(struct config_control),
    },

    //bluetooth
    .bluetooth_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_bluetooth_normal_controls,
        .controls_count = sizeof(cx2072_bluetooth_normal_controls) / sizeof(struct config_control),
    },
    .bluetooth_incall = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = cx2072_bluetooth_incall_controls,
        .controls_count = sizeof(cx2072_bluetooth_incall_controls) / sizeof(struct config_control),
    },
    .bluetooth_voip = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = cx2072_bluetooth_voip_controls,
        .controls_count = sizeof(cx2072_bluetooth_voip_controls) / sizeof(struct config_control),
    },

    //capture
    .main_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_main_mic_capture_controls,
        .controls_count = sizeof(cx2072_main_mic_capture_controls) / sizeof(struct config_control),
    },
    .hands_free_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = cx2072_hands_free_mic_capture_controls,
        .controls_count = sizeof(cx2072_hands_free_mic_capture_controls) / sizeof(struct config_control),
    },
    .bluetooth_sco_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = cx2072_bluetooth_sco_mic_capture_controls,
        .controls_count = sizeof(cx2072_bluetooth_sco_mic_capture_controls) / sizeof(struct config_control),
    },

    //off
    .playback_off = {
        .controls = cx2072_playback_off_controls,
        .controls_count = sizeof(cx2072_playback_off_controls) / sizeof(struct config_control),
    },
    .capture_off = {
        .controls = cx2072_capture_off_controls,
        .controls_count = sizeof(cx2072_capture_off_controls) / sizeof(struct config_control),
    },
    .incall_off = {
        .controls = cx2072_incall_off_controls,
        .controls_count = sizeof(cx2072_incall_off_controls) / sizeof(struct config_control),
    },
    .voip_off = {
        .controls = cx2072_voip_off_controls,
        .controls_count = sizeof(cx2072_voip_off_controls) / sizeof(struct config_control),
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


#endif //_CX2072_CONFIG_H_
