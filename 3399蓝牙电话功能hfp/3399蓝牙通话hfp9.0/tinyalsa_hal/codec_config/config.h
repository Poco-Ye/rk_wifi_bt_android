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
 * @file config.h
 * @brief 
 * @author  RkAudio
 * @version 1.0.8
 * @date 2015-08-24
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

struct config_control
{
    const char *ctl_name; //name of control.
    const char *str_val; //value of control, which type is stream.
    const int int_val[2]; //left and right value of control, which type are int.
};

struct config_route
{
    const int sound_card;
    const int devices;
    const struct config_control *controls;
    const unsigned controls_count;
};

struct config_route_table
{
    const struct config_route speaker_normal;
    const struct config_route speaker_incall;
    const struct config_route speaker_ringtone;
    const struct config_route speaker_voip;

    const struct config_route earpiece_normal;
    const struct config_route earpiece_incall;
    const struct config_route earpiece_ringtone;
    const struct config_route earpiece_voip;

    const struct config_route headphone_normal;
    const struct config_route headphone_incall;
    const struct config_route headphone_ringtone;
    const struct config_route speaker_headphone_normal;
    const struct config_route speaker_headphone_ringtone;
    const struct config_route headphone_voip;

    const struct config_route headset_normal;
    const struct config_route headset_incall;
    const struct config_route headset_ringtone;
    const struct config_route headset_voip;

    const struct config_route bluetooth_normal;
    const struct config_route bluetooth_incall;
    const struct config_route bluetooth_voip;

    const struct config_route main_mic_capture;
    const struct config_route hands_free_mic_capture;
    const struct config_route bluetooth_sco_mic_capture;

    const struct config_route playback_off;
    const struct config_route capture_off;
    const struct config_route incall_off;
    const struct config_route voip_off;

    const struct config_route hdmi_normal;

    const struct config_route usb_normal;
    const struct config_route usb_capture;

    const struct config_route spdif_normal;

    const struct config_route hdmiin_normal;
    const struct config_route hdmiin_off;
    const struct config_route hdmiin_captrue;
    const struct config_route hdmiin_captrue_off;
};

#define on 1
#define off 0

#define DEVICES_0 0
#define DEVICES_0_1 1
#define DEVICES_0_2 2
#define DEVICES_0_1_2 3

#endif //_CONFIG_H_
