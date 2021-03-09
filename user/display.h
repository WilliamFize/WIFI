#ifndef __DISPLAY_H_
#define __DISPLAY_H_

/*---------------------------------------------------------------------------------------------------------*/
/* POPUP INFO DEFINE                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
typedef enum
{
	POPUP_NULL,
	POPUP_MIC_STATUS,
	POPUP_SYS_INFO,
	POPUP_MESSGAE,
}POPUP_STATUS_E;

typedef struct
{
	POPUP_STATUS_E	status;
	u8				enable;
	u16				cnt;
}POPUP_T;
extern POPUP_T popup;
/*---------------------------------------------------------------------------------------------------------*/
/* POPUP INFO END                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* IMAGE DEFINE                                                                                       	   */
/*---------------------------------------------------------------------------------------------------------*/
extern uc8 image_startup[][1024];
#define IMAGE_STARTUP_TOTAL					9
#define IMAGE_STARTUP_WEIGH					128
#define IMAGE_STARTUP_HIGH					64
#define IMAGE_STARTUP_COL					OLED_8_16_4_COL0
#define	IMAGE_STARTUP_PAGE					OLED_8_16_4_PAGE0

extern uc8 image_bat_value[][36];
#define IMAGE_BAT_VALUE_TOTAL				5
#define IMAGE_BAT_VALUE_WEIGH				18
#define IMAGE_BAT_VALUE_HIGH				16
#define IMAGE_BAT_VALUE_COL					110
#define	IMAGE_BAT_VALUE_PAGE				OLED_8_16_4_PAGE0

extern uc8 image_bat_charge[20];
#define IMAGE_BAT_CHARGE_TOTAL				5
#define IMAGE_BAT_CHARGE_WEIGH				10
#define IMAGE_BAT_CHARGE_HIGH				16
#define IMAGE_BAT_CHARGE_COL				97
#define	IMAGE_BAT_CHARGE_PAGE				OLED_8_16_4_PAGE0

extern uc8 image_rssi_value[][36];
#define IMAGE_RSSI_VALUE_TOTAL				5
#define IMAGE_RSSI_VALUE_WEIGH				18
#define IMAGE_RSSI_VALUE_HIGH				16
#define IMAGE_RSSI_VALUE_COL				0
#define	IMAGE_RSSI_VALUE_PAGE				OLED_8_16_4_PAGE0


#define LANGUAGE_CHOOSE(str, pic, w, h, col, page) 	{(info.lang) ? (OLEDDMAShowStr(str, col, page)) : \
															   (OLEDDMAShowPic(pic, w, h, col, page));}


//MIC STATUS DISPLAY
extern uc8 image_mic_open[256];
#define IMAGE_MIC_OPEN_DISPLAY()			{DisplaySetPopup(POPUP_MIC_STATUS); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("   MIC IS ON    ", image_mic_open, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}

extern uc8 image_mic_close[256];
#define IMAGE_MIC_CLOSE_DISPLAY()			{DisplaySetPopup(POPUP_MIC_STATUS); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("   MIC IS OFF   ", image_mic_close, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}

extern uc8 image_mic_applying[256];
#define IMAGE_MIC_APPLYING_DISPLAY()		{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("MIC IS APPLYING ", image_mic_applying, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}


extern uc8 image_mic_waiting[256];
#define IMAGE_MIC_WAITING_DISPLAY()			{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE(" MIC IS WAITING ", image_mic_waiting, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}

extern uc8 image_mic_full[256];
#define IMAGE_MIC_FULL_DISPLAY()			{DisplaySetPopup(POPUP_MIC_STATUS); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("   MIC IS FULL  ", image_mic_full, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}

//MIC COUNTER DISPLAY
extern uc8 image_spk_time[256];
#define IMAGE_SPK_TIME_DISPLAY()			{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Spk Time  :  :  ", image_spk_time, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}

extern uc8 image_rem_time[256];
#define IMAGE_REM_TIME_DISPLAY()			{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Rem Time  :  :  ", image_rem_time, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}

#define IMAGE_MIC_TIME_DISPLAY()			{OLEDDMAShowNumFill(info.time_statement_count / 3600,      2, OLED_8_16_4_COL8,  OLED_8_16_4_PAGE2); \
											 OLEDDMAShowNumFill(info.time_statement_count % 3600 / 60, 2, OLED_8_16_4_COL11, OLED_8_16_4_PAGE2); \
											 OLEDDMAShowNumFill(info.time_statement_count % 60,        2, OLED_8_16_4_COL14, OLED_8_16_4_PAGE2);}



//SIGN UI DISPLAY
extern uc8 image_total_sign[192];
extern uc8 image_have_signed[192];
#define IMAGE_SIGN_DISPLAY()				{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Total  sign:", image_total_sign, 96, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 LANGUAGE_CHOOSE("Have signed:", image_have_signed, 96, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}	

#define IMAGE_SIGN_NUM_DISPLAY()			{OLEDDMAShowNumFill(sign.total, 4, OLED_8_16_4_COL12, OLED_8_16_4_PAGE2); \
											 OLEDDMAShowNumFill(sign.already_total, 4, OLED_8_16_4_COL12, OLED_8_16_4_PAGE3);}

extern uc8 image_sign_banned[256];
#define IMAGE_SIGN_BANNED_DISPLAY()			{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Signin be banned", image_sign_banned, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}


//VOTE UI DISPLAY
extern uc8 image_voting[256];
#define IMAGE_VOTING_DISPLAY()				{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("    Voting...   ", image_voting, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}


//FIRE WARNNING DISPLAY
extern uc8 image_fire_warning[256];
#define IMAGE_FIRE_WARNNING_DISPLAY()		{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 48, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
                                             LANGUAGE_CHOOSE("  Fire Warning! ", image_fire_warning, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);}


//ID REPEAT DISPLAY
extern uc8 image_id_repeat[256];
#define IMAGE_ID_REPEAT_DISPLAY()			{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 48, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("   ID Repeat!   ", image_id_repeat, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);}


//BAT TOO LOW DISPLAY
extern uc8 image_bat_too_low[256];
#define IMAGE_BAT_TOO_LOW_DISPLAY()			{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 48, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Battery Too Low!", image_bat_too_low, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);}

//RSSI TOO LOW DISPLAY
extern uc8 image_rssi_too_low[256];
#define IMAGE_RSSI_TOO_LOW_DISPLAY()		{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 48, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("  RSSI Too Low! ", image_rssi_too_low, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);}


//SET ID DISPLAY
extern uc8 image_local_id[208];
extern uc8 image_current_id[208];
#define IMAGE_SET_ID_DISPLAY()				{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Local   ID: W", image_local_id, 104, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2); \
											 LANGUAGE_CHOOSE("Current ID: W", image_current_id, 104, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);}	

#define IMAGE_SET_LOCAL_ID_DISPLAY()		OLEDDMAShowNumFill(setid.local   - 0x3000, 3, OLED_8_16_4_COL13, OLED_8_16_4_PAGE2);
#define IMAGE_SET_CURRENT_ID_DISPLAY()		OLEDDMAShowNumFill(setid.current - 0x3000, 3, OLED_8_16_4_COL13, OLED_8_16_4_PAGE3);


//VER DISPLAY
extern uc8 image_ver[80];
#define IMAGE_VER_DISPLAY()					LANGUAGE_CHOOSE("VER :", image_ver, 40, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);


//HOME DISPLAY
extern uc8 image_home[256];
#define IMAGE_HOME_DISPLAY()				{DisplaySetPopup(POPUP_NULL); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
												(info.lang) ? (OLEDDMAShowStr("    Wireless    ",  OLED_8_16_4_COL0, OLED_8_16_4_PAGE2), \
													           OLEDDMAShowStr("   Conference   ",  OLED_8_16_4_COL0, OLED_8_16_4_PAGE3)) : \
													          (OLEDDMAShowPic(image_home, 128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE2), \
													           OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3));}


//MESSAGE DISPLAY
extern uc8 image_go_to_door[512];
#define IMAGE_GO_TO_DOOR_DISPLAY()			{DisplaySetPopup(POPUP_MESSGAE); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Plz go to the door of boardroom!", image_go_to_door, 128, 32, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);}	

extern uc8 image_go_to_console[512];
#define IMAGE_GO_TO_CONSOLE_DISPLAY()		{DisplaySetPopup(POPUP_MESSGAE); \
											 OLEDDMAFill(128, 16, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1); \
											 LANGUAGE_CHOOSE("Please go to the console!       ", image_go_to_console, 128, 32, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);}	


//SYSTEM INFO DISPLAY
extern uc8 image_ap_lose[256];
#define IMAGE_AP_LOSE_DISPLAY()				LANGUAGE_CHOOSE(" Connecting AP! ", image_ap_lose, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE1);


extern uc8 image_host_lose[256];
#define IMAGE_HOST_LOSE_DISPLAY()			LANGUAGE_CHOOSE("Connecting HOST!", image_host_lose, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE1);


extern uc8 image_core_uart_error[256];
#define IMAGE_CORE_UART_ERROR_DISPLAY()		LANGUAGE_CHOOSE("Core UART Error!", image_core_uart_error, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);


extern uc8 image_ssid_set_ok[256];
#define IMAGE_SSID_SET_OK_DISPLAY()			LANGUAGE_CHOOSE("  SSID Set OK!  ", image_ssid_set_ok, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGEM);


extern uc8 image_please_crack[256];
#define IMAGE_PLEASE_CRACK_DISPLAY()		LANGUAGE_CHOOSE(" Please Crack!  ", image_please_crack, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGEM);

extern uc8 image_crack_sucess[256];
#define IMAGE_CRACK_SUCESS_DISPLAY()		LANGUAGE_CHOOSE(" Crack Sucess!  ", image_crack_sucess, 128, 16, \
												OLED_8_16_4_COL0, OLED_8_16_4_PAGEM);

/*---------------------------------------------------------------------------------------------------------*/
/* IMAGE DEFINE END                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------*/
/* DISPLAY DEFINE                                                                             			   */
/*---------------------------------------------------------------------------------------------------------*/
void DisplaySetPopup(POPUP_STATUS_E status);
void DisplayStatusInfo(void);
void DisplaySystemInfo(void);
void DisplayRestoreMeetingMode(void);
void DisplayRestoreSignMode(void);
void DisplayRestoreVoteMode(void);
void DisplayRestoreSetIDMode(void);
void DisplayRestoreIDRepeatMode(void);
void DisplayMicStartTimeStatement(void);
void DisplayStartupFlash(void);
void DisplayAPLose(void);
void DisplayHostLose(void);
void DisplayUartError(void);
/*---------------------------------------------------------------------------------------------------------*/
/* DISPLAY DEFINE END                                                                            		   */
/*---------------------------------------------------------------------------------------------------------*/


#endif



