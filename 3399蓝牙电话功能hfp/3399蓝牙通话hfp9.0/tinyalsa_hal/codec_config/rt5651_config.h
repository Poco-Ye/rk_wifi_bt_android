/*
 * Copyright (C) 2015 Rockchip Electronics Co., Ltd.
*/
/**
 * @file rt5651_config.h
 * @brief
 * @author  RkAudio
 * @version 1.0.8
 * @date 2015-08-24
 */

#ifndef _RT5651_CONFIG_H_
#define _RT5651_CONFIG_H_

#include "config.h"

const struct config_control rt5651_speaker_normal_controls[] = {
    /*
    	{
            .ctl_name = "DAC MIXL INF1 Switch",
            .int_val = {on},
        },
    	{
            .ctl_name = "DAC MIXR INF1 Switch",
            .int_val = {on},
        },
    	{
            .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
            .int_val = {on},
        },
    	{
            .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
            .int_val = {on},
        },
    	{
            .ctl_name = "OUT MIXL DAC L1 Switch",
            .int_val = {on},
        },
    	{
            .ctl_name = "OUT MIXR DAC R1 Switch",
            .int_val = {on},
        },
        	{
            .ctl_name = "OUTVOL L Switch",
            .int_val = {on},
        },
        	{
            .ctl_name = "OUTVOL R Switch",
            .int_val = {on},
        },
    	{
            .ctl_name = "LOUT MIX OUTVOL L Switch",
            .int_val = {on},
        },
    	{
            .ctl_name = "LOUT MIX OUTVOL R Switch",
            .int_val = {on},
        },
        {
            .ctl_name = "LOUT L Playback Switch",
            .int_val = {on},
        },
          {
            .ctl_name = "LOUT R Playback Switch",
            .int_val = {on},
        },
    */
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
	
	// tapc : open speaker headset
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },

    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {on},
    },

	// open external input
    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },	
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_speaker_incall_controls[] = {


};

const struct config_control rt5651_speaker_ringtone_controls[] = {
       {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
	
	// tapc : open speaker headset
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },

    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {on},
    },


    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },	
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_speaker_voip_controls[] = {
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
	
	// tapc : open speaker headset
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },

    {
        .ctl_name = "LOUT MIX DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT MIX OUTVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {on},
    },


    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },	
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_earpiece_normal_controls[] = {
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo DAC MIXL DAC L2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R2 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },

};

const struct config_control rt5651_earpiece_incall_controls[] = {

};

const struct config_control rt5651_earpiece_ringtone_controls[] = {

};

const struct config_control rt5651_earpiece_voip_controls[] = {

};

const struct config_control rt5651_headphone_normal_controls[] = {
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
	
	// tapc : open headset , close speaker
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
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },	
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },		
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_headphone_incall_controls[] = {

};

const struct config_control rt5651_headphone_ringtone_controls[] = {
	{
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
	
	// tapc : open headset , close speaker
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
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },	
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },		
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_speaker_headphone_normal_controls[] = {

};

const struct config_control rt5651_speaker_headphone_ringtone_controls[] = {

};

const struct config_control rt5651_headphone_voip_controls[] = {
	{
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
	
	// tapc : open headset , close speaker
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
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },	
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },		
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_headset_normal_controls[] = {
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
	
	// tapc : open headset , close speaker
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
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },	
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_headset_incall_controls[] = {

};

const struct config_control rt5651_headset_ringtone_controls[] = {
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
	
	// tapc : open headset , close speaker
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
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {off},
    },

    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },	
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_headset_voip_controls[] = {
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
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
        .ctl_name = "Stereo DAC MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo DAC MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXL DAC L1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "OUT MIXR DAC R1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL L Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPOVOL R Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO MIX HPVOL Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO L Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HPO R Playback Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "HP Playback Volume",
        .int_val = {31, 31},
    },
    {
        .ctl_name = "DAC1 Playback Volume",
        .int_val = {175, 175},
    },
	
	// tapc : open headset , close speaker
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
        .ctl_name = "LOUT L Playback Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "LOUT R Playback Switch",
        .int_val = {off},
    },
	
    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },	
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_bluetooth_normal_controls[] = {

};

const struct config_control rt5651_bluetooth_incall_controls[] = {

};

const struct config_control rt5651_bluetooth_voip_controls[] = {

};

const struct config_control rt5651_hands_free_mic_capture_controls[] = {
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC L1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo1 ADC R1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "ADC Capture Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "IN1 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Volume",
        .int_val = {47, 47},
    },
    {
        .ctl_name = "IN3 Boost",
        .int_val = {0},
    },		
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },		
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_main_mic_capture_controls[] = {
    /* {
         .ctl_name = "Stereo1 ADC L2 Mux",
         .str_val = "DMIC",
     },
    {
         .ctl_name = "Stereo1 ADC R2 Mux",
         .str_val = "DMIC",
     },
    {
         .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
         .int_val = {on},
     },
    {
         .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
         .int_val = {on},
     },*/
    {
        .ctl_name = "RECMIXL INL1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXR INR1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "RECMIXL BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "RECMIXR BST3 Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "Stereo1 ADC L1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "Stereo1 ADC R1 Mux",
        .str_val = "ADC",
    },
    {
        .ctl_name = "ADC Capture Switch",
        .int_val = {on, on},
    },
    {
        .ctl_name = "IN2 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "ADC Capture Volume",
        .int_val = {47, 47},
    },
    {
        .ctl_name = "IN3 Boost",
        .int_val = {0},
    },
    {
        .ctl_name = "DAC MIXL Stereo ADC Switch",
        .int_val = {off},
    },
    {
        .ctl_name = "DAC MIXR Stereo ADC Switch",
        .int_val = {off},
    },		
    {
        .ctl_name = "Stereo1 ADC MIXL ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC1 Switch",
        .int_val = {on},
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },
};

const struct config_control rt5651_bluetooth_sco_mic_capture_controls[] = {

};

const struct config_control rt5651_playback_off_controls[] = {

};

const struct config_control rt5651_capture_off_controls[] = {

};

const struct config_control rt5651_incall_off_controls[] = {

};

const struct config_control rt5651_voip_off_controls[] = {

};
// tapc : hdmiin on
const struct config_control rt5651_hdmiin_normal_controls[] = {

    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },
	
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {1},
    },


};
// tapc : hdmiin off
const struct config_control rt5651_hdmiin_off_controls[] = {
	// close hdmiin must need this 
    {
        .ctl_name = "RT5651 ASRC Switch",
        .str_val = "Enable",
    },
    {
        .ctl_name = "DD MIXL DAC L2 Switch",
        .int_val = {1},
    },
    {
        .ctl_name = "DD MIXR DAC R2 Switch",
        .int_val = {1},
    },
	// close hdmiin sound
    {
        .ctl_name = "Stereo1 ADC MIXL ADC2 Switch",
        .int_val = {0},
    },
    {
        .ctl_name = "Stereo1 ADC MIXR ADC2 Switch",
        .int_val = {0},
    },
};

const struct config_route_table rt5651_config_table = {
    //speaker
    .speaker_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_speaker_normal_controls,
        .controls_count = sizeof(rt5651_speaker_normal_controls) / sizeof(struct config_control),
    },
    .speaker_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_speaker_incall_controls,
        .controls_count = sizeof(rt5651_speaker_incall_controls) / sizeof(struct config_control),
    },
    .speaker_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_speaker_ringtone_controls,
        .controls_count = sizeof(rt5651_speaker_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_speaker_voip_controls,
        .controls_count = sizeof(rt5651_speaker_voip_controls) / sizeof(struct config_control),
    },

    //earpiece
    .earpiece_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_earpiece_normal_controls,
        .controls_count = sizeof(rt5651_earpiece_normal_controls) / sizeof(struct config_control),
    },
    .earpiece_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_earpiece_incall_controls,
        .controls_count = sizeof(rt5651_earpiece_incall_controls) / sizeof(struct config_control),
    },
    .earpiece_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_earpiece_ringtone_controls,
        .controls_count = sizeof(rt5651_earpiece_ringtone_controls) / sizeof(struct config_control),
    },
    .earpiece_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_earpiece_voip_controls,
        .controls_count = sizeof(rt5651_earpiece_voip_controls) / sizeof(struct config_control),
    },

    //headphone
    .headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headphone_normal_controls,
        .controls_count = sizeof(rt5651_headphone_normal_controls) / sizeof(struct config_control),
    },
    .headphone_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headphone_incall_controls,
        .controls_count = sizeof(rt5651_headphone_incall_controls) / sizeof(struct config_control),
    },
    .headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headphone_ringtone_controls,
        .controls_count = sizeof(rt5651_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_speaker_headphone_normal_controls,
        .controls_count = sizeof(rt5651_speaker_headphone_normal_controls) / sizeof(struct config_control),
    },
    .speaker_headphone_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_speaker_headphone_ringtone_controls,
        .controls_count = sizeof(rt5651_speaker_headphone_ringtone_controls) / sizeof(struct config_control),
    },
    .headphone_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headphone_voip_controls,
        .controls_count = sizeof(rt5651_headphone_voip_controls) / sizeof(struct config_control),
    },

    //headset
    .headset_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headset_normal_controls,
        .controls_count = sizeof(rt5651_headset_normal_controls) / sizeof(struct config_control),
    },
    .headset_incall = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headset_incall_controls,
        .controls_count = sizeof(rt5651_headset_incall_controls) / sizeof(struct config_control),
    },
    .headset_ringtone = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headset_ringtone_controls,
        .controls_count = sizeof(rt5651_headset_ringtone_controls) / sizeof(struct config_control),
    },
    .headset_voip = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_headset_voip_controls,
        .controls_count = sizeof(rt5651_headset_voip_controls) / sizeof(struct config_control),
    },

    //bluetooth
    .bluetooth_normal = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_bluetooth_normal_controls,
        .controls_count = sizeof(rt5651_bluetooth_normal_controls) / sizeof(struct config_control),
    },
    .bluetooth_incall = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt5651_bluetooth_incall_controls,
        .controls_count = sizeof(rt5651_bluetooth_incall_controls) / sizeof(struct config_control),
    },
    .bluetooth_voip = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt5651_bluetooth_voip_controls,
        .controls_count = sizeof(rt5651_bluetooth_voip_controls) / sizeof(struct config_control),
    },

    //capture
    .main_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_main_mic_capture_controls,
        .controls_count = sizeof(rt5651_main_mic_capture_controls) / sizeof(struct config_control),
    },
    .hands_free_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0,
        .controls = rt5651_hands_free_mic_capture_controls,
        .controls_count = sizeof(rt5651_hands_free_mic_capture_controls) / sizeof(struct config_control),
    },
    .bluetooth_sco_mic_capture = {
        .sound_card = 0,
        .devices = DEVICES_0_1,
        .controls = rt5651_bluetooth_sco_mic_capture_controls,
        .controls_count = sizeof(rt5651_bluetooth_sco_mic_capture_controls) / sizeof(struct config_control),
    },

    //off
    .playback_off = {
        .controls = rt5651_playback_off_controls,
        .controls_count = sizeof(rt5651_playback_off_controls) / sizeof(struct config_control),
    },
    .capture_off = {
        .controls = rt5651_capture_off_controls,
        .controls_count = sizeof(rt5651_capture_off_controls) / sizeof(struct config_control),
    },
    .incall_off = {
        .controls = rt5651_incall_off_controls,
        .controls_count = sizeof(rt5651_incall_off_controls) / sizeof(struct config_control),
    },
    .voip_off = {
        .controls = rt5651_voip_off_controls,
        .controls_count = sizeof(rt5651_voip_off_controls) / sizeof(struct config_control),
    },
    .hdmiin_normal = {
        .controls = rt5651_hdmiin_normal_controls,
        .controls_count = sizeof(rt5651_hdmiin_normal_controls) / sizeof(struct config_control),
    },

    .hdmiin_off = {
        .controls = rt5651_hdmiin_off_controls,
        .controls_count = sizeof(rt5651_hdmiin_off_controls) / sizeof(struct config_control),
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


#endif //_RT5651_CONFIG_H_
