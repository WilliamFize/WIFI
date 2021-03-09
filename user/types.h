#ifndef __TYPES_H__
#define __TYPES_H__

/*---------------------------------------------------------------------------------------------------------*/
/* BASE TYPE DEFINE                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;  
typedef signed short const sc16;  
typedef signed char  const sc8;   

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;
 
typedef volatile signed long  const vsc32;  
typedef volatile signed short const vsc16;  
typedef volatile signed char  const vsc8;   

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;  
typedef unsigned short const uc16;  
typedef unsigned char  const uc8;   

//typedef volatile unsigned long  vu32;这些在stdint.h中有定义
//typedef volatile unsigned short vu16;
//typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;  
typedef volatile unsigned short const vuc16;  
typedef volatile unsigned char  const vuc8;  

#define DATA_WORD_ALIGN		__align(4)

#define DATA_BIT_CHANGE_STAT(data, stat)	((data & (1<<stat))>>stat) 
/*---------------------------------------------------------------------------------------------------------*/
/* BASE TYPE DEFINE END                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* System Clock DEFINE                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define HCLK_CLOCK           72000000
/*---------------------------------------------------------------------------------------------------------*/
/* System Clock DEFINE END                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* VOTE INFO DEFINE                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
typedef enum
{
	BUTTON_3_VOTE_ONCE_SIGN,
	BUTTON_3_VOTE_ONCE_NOT_SIGN,
	BUTTON_3_VOTE_LAST_SIGN,
	BUTTON_3_VOTE_LAST_NOT_SIGN,
	BUTTON_5_OPTION_ONCE_SIGN,
	BUTTON_5_OPTION_ONCE_NOT_SIGN,
	BUTTON_5_OPTION_LAST_SIGN,
	BUTTON_5_OPTION_LAST_NOT_SIGN,
	BUTTON_5_LEVEL_ONCE_SIGN,
	BUTTON_5_LEVEL_ONCE_NOT_SIGN,
	BUTTON_5_LEVEL_LAST_SIGN,
	BUTTON_5_LEVEL_LAST_NOT_SIGN,
	BUTTON_2_USER_OPTION_ONCE_SIGN,
	BUTTON_2_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_2_USER_OPTION_LAST_SIGN,
	BUTTON_2_USER_OPTION_LAST_NOT_SIGN,
	BUTTON_3_USER_OPTION_ONCE_SIGN,
	BUTTON_3_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_3_USER_OPTION_LAST_SIGN,
	BUTTON_3_USER_OPTION_LAST_NOT_SIGN,
	BUTTON_4_USER_OPTION_ONCE_SIGN,
	BUTTON_4_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_4_USER_OPTION_LAST_SIGN,
	BUTTON_4_USER_OPTION_LAST_NOT_SIGN,
	BUTTON_5_USER_OPTION_ONCE_SIGN,
	BUTTON_5_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_5_USER_OPTION_LAST_SIGN,
	BUTTON_5_USER_OPTION_LAST_NOT_SIGN,
}VOTE_TYPE_E;

typedef struct
{
	u8			enable;
	u8			result;// 0没按，1赞成，2弃权，3反对
	VOTE_TYPE_E	type;
}VOTE_T;
extern VOTE_T vote;
/*---------------------------------------------------------------------------------------------------------*/
/* VOTE INFO DEFINE END                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* SET ID INFO DEFINE                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
typedef struct
{
	u8	press;
	u8	sucess;
	u8	already;
	u16	current;
	u16	local;
}SET_ID_T;
extern SET_ID_T setid;
/*---------------------------------------------------------------------------------------------------------*/
/* SET ID INFO DEFINE END                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/* SIGN INFO DEFINE                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
typedef struct
{
	u8	already;
	u8	enable;
	u16	total;
	u16	already_total;
}SIGN_T;
extern SIGN_T sign;
/*---------------------------------------------------------------------------------------------------------*/
/* SIGN INFO DEFINE                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/* WIFI INFO DEFINE                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define WPA_INPUT_CHAR_LEN	17
typedef struct
{
	u8 	ssid[WPA_INPUT_CHAR_LEN];
	u8 	ssid_len;
	u8 	key[WPA_INPUT_CHAR_LEN];
	u8 	key_len;
}WPA2_PSK_T;

typedef struct
{
	u8			rssi;
	u8 			connect;
	u8			low;
	u8 			mac[6];
	WPA2_PSK_T	wpa;
}WIFI_T;
extern WIFI_T wifi;
/*---------------------------------------------------------------------------------------------------------*/
/* WIFI INFO DEFINE                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/* SYSTEM INFO DEFINE END                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
typedef enum
{
	UNIT_OPRATION_MEETING_MODE,
	UNIT_OPRATION_SIGN_MODE,
	UNIT_OPRATION_VOTE_MODE,
	UNIT_OPRATION_SETID_MODE,
	
	UNIT_OPRATION_IDREPEAT_MODE,
	UNIT_OPRATION_VOTE_RESULT_MODE,
	UNIT_OPRATION_HOST_DISCONNECT_MODE,
}UNIT_OPRATION_E;

typedef enum
{
	DOWN_STATEMENT,
	UP_STATEMENT,
	NO_STATEMENT,
}TIME_STATEMENT_E;

typedef enum
{
	WIFI_CORE_STARTUP_WAIT_UART,
	WIFI_CORE_STARTUP_WAIT_AP,
	WIFI_CORE_STARTUP_WAIT_HOST,
	WIFI_CORE_STARTUP_FINISH,
	
	WIFI_CORE_STARTUP_UART_ERROR,
	WIFI_CORE_STARTUP_AP_DISCONNECT,
	WIFI_CORE_STARTUP_HOST_DISCONNECT,
}WIFI_CORE_STARTUP_E;

typedef enum
{
	LANG_CHINESE,
	LANG_ENGLISH,
}SYS_LANG_E;

#define DEFAULT_DISPLAY_VER		"2.5&x.x    "
#define WIFI_CORE_VER_SHIFT		4

typedef struct
{
	u8					master_unit;
	u8					host_connect;
	u8					battery;
	u8					battery_low;
	u8					usb_state;
	u8					ver[12];
	u8					mcu_uid[12];
	u8					uid_key[16];
	u8					fire_warning;
	
	SYS_LANG_E			lang;
	WIFI_CORE_STARTUP_E	wifi_core_startup;
	UNIT_OPRATION_E		unit_opration;
	TIME_STATEMENT_E	time_statement;
	
	u16					host_lost_count;
	u16					overcount;
	u16					led_flash_count;
	
	u32					time_statement_count;
	u32					time_statement_max;
	u8          		MICFULLFlag ;
}INFO_T;
extern INFO_T info;

typedef enum
{
	LED_CONTROL_MIC_CLOSE,
	LED_CONTROL_MIC_OPEN,
	LED_CONTROL_MIC_WAIT,
	LED_CONTROL_MIC_APPLY,

	LED_CONTROL_ALREADY_SIGN,
	LED_CONTROL_ALREADY_SETID,
	LED_CONTROL_ALL_CLOSE
}LED_CONTROL_E;

void SystemPowerDown(void);
void LedStaticControl(LED_CONTROL_E ctrl);
void HostDisconnectDo(void);
void Wm8974SpecialParmInit(void);

/*---------------------------------------------------------------------------------------------------------*/
/* SYSTEM INFO DEFINE END                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/* SYS INCLUDE DEFINE                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>

/*---------------------------------------------------------------------------------------------------------*/
/* MOUDLE INCLUDE DEFINE                                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#include "NUC123.h"
#include "delay.h"
#include "system_timer.h"
#include "system_adc.h"
#include "wifi_core.h"
#include "wm8974.h"
#include "io_define.h"
#include "dataflash.h"
#include "i2c_simulate.h"
#include "strconv.h"
#include "audio_control.h"
#include "key.h"
#include "hid_transfer.h"
#include "aes.h"
#include "oled.h"
#include "display.h"
/*---------------------------------------------------------------------------------------------------------*/
/* INCLUDE DEFINE END                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/




#endif

