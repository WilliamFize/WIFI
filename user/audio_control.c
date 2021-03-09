#include "types.h"

MIC_T	mic;

/*---------------------------------------------------------------------------------------------------------*/
/*MIC delay open conrtol                                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define MIC_VOL_MAX				33
#define MIC_VOL_FADE_PERIOD		3
void MicOpenFadePolling(void)
{
	static u16 mic_fade_tmr;

	if(mic.status == MIC_STATUS_OPEN)
	{
		if(mic_fade_tmr < MIC_VOL_FADE_PERIOD)
		{
			mic_fade_tmr++;
		}
		else
		{
			mic_fade_tmr = 0;
			if(mic.vol < MIC_VOL_MAX)
			{
				mic.vol++;
				Wm8974SetInpgaHexVolume(mic.vol);
			}
		}
	}
	else
	{
		mic_fade_tmr = 0;
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*MIC OPEN Or CLOSE DEFINE                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
void HardwordOpenMic(u8 sender_ch, u8 led_change)
{
	if(mic.status != MIC_STATUS_OPEN)
	{
		mic.status = MIC_STATUS_OPEN;
		mic.send_ch= sender_ch;
		VoiceModeNoSignalResetTimer();
		WifiCoreCommandSend(MCU_TO_WIFI_CORE_SENDER_SW, &mic.send_ch, 1);
	}
	if(led_change)
		LedStaticControl(mic.status);
}

void HardwordCloseMic(u8 send_to_host, u8 led_change)
{
	switch(mic.status)
	{
		case MIC_STATUS_OPEN:
			mic.status = MIC_STATUS_CLOSE;
			if(send_to_host)
				HostCommandSend(UNIT_TO_HOST_APPLY_CLOSEMIC, 0x00, 0x00, NULL, 0x00);
			WifiCoreCommandSend(MCU_TO_WIFI_CORE_SENDER_SW, &mic.status, 1);
			//mic.vol = 0;
			//Wm8974SetInpgaHexVolume(mic.vol);
			break;
		case MIC_STATUS_APPLY:
		case MIC_STATUS_WAIT:
			mic.status = MIC_STATUS_CLOSE;
			if(send_to_host)
				HostCommandSend(UNIT_TO_HOST_MIC_GET_OUT_WAIT, 0x00, 0x00, NULL, 0x00);
			break;
		default:
			break;
	}
	
	if(led_change)
	{
		LedStaticControl(mic.status);
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/*MIC OPEN DEFINE END                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/

void SetMicSen2WM8974(u8 sen)
{	
	//(1) min_db = -6 + 12 = 6
	//(2) min_value = (min_db + 12) / 0.75 = 24
	//(3) data = min_value + sen * 2 = 24 + sen * 2
	if(sen < 9) {
		Wm8974SetInpgaHexVolume((sen << 1) + 24);
	}
}



