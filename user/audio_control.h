#ifndef __AUDIO_CONTROL_H_
#define __AUDIO_CONTROL_H_

/*---------------------------------------------------------------------------------------------------------*/
/* Audio Control DEFINE                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/

typedef enum
{
	MIC_STATUS_CLOSE,
	MIC_STATUS_OPEN,
	MIC_STATUS_WAIT,
	MIC_STATUS_APPLY,
}MIC_STATUS_T;

typedef enum
{
	MIC_MODE_FIFO = 1,
	MIC_MODE_NORMAL,
	MIC_MODE_VOICE,
	MIC_MODE_APPLY,
}MIC_MODE_E;

typedef enum
{
	MIC_OPEN_TOTAL_1 = 1,
	MIC_OPEN_TOTAL_2 = 2,
	MIC_OPEN_TOTAL_4 = 4,
	MIC_OPEN_TOTAL_6 = 6,
}MIC_OPEN_TOTAL_E;

typedef struct
{	
	MIC_STATUS_T 		status;
	u8					enable;
	u8					send_ch;
	u8					led;
	u8					use;
	u8					vol;
	MIC_MODE_E			mode;
	MIC_OPEN_TOTAL_E	open_total;
	u16					v_sen;
	u16					nos_tmr;
	u16					nos_cnt;
	u8					sen_preset;
	u8					sen;
	u8					filter_en;
	u8					eq_preset[5];
	u8					eq[5];
}MIC_T;

/*---------------------------------------------------------------------------------------------------------*/
/* Audio Control DEFINE END                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
void MicOpenFadePolling(void);
void HardwordOpenMic(u8 sender_ch, u8 led_change);
void HardwordCloseMic(u8 send_to_host, u8 led_change);
void SetMicSen2WM8974(u8 sen);

extern MIC_T	mic;

#endif



