#ifndef __WIFI_CORE_COMMADN_H__
#define __WIFI_CORE_COMMADN_H__

/*---------------------------------------------------------------------------------------------------------*/
/* WIFI_CORE COMMAND DEFINE                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define WIFI_CORE_TO_MCU_NO_COMMAND			0x00
#define WIFI_CORE_TO_MCU_POWER_ON			0x01
#define	WIFI_CORE_TO_MCU_VER				0x02
#define WIFI_CORE_TO_MCU_RSSI				0x03
#define WIFI_CORE_TO_MCU_WIFI_DISCONNECT	0x04
#define WIFI_CORE_TO_MCU_WIFI_RECONNECT		0x05
#define WIFI_CORE_TO_MCU_SSID				0x06
#define WIFI_CORE_TO_MCU_MAC				0x07

#define MCU_TO_WIFI_CORE_SENDER_SW			0x56
#define MCU_TO_WIFI_CORE_ID					0x57
#define MCU_TO_WIFI_CORE_SET_SSID			0x58
#define MCU_TO_WIFI_CORE_SET_WPA_KEY		0x59
	
#define MCU_TO_HOST_COMMAND					0xAA
#define MCU_TO_HOST_ENTER_SYSTEM			0xAB
#define HOST_TO_MCU_COMMAND					0xAC


void WifiCoreUSARTInit(void);
void WifiCoreCommandSend(u8 cmd, u8 *data, u8 len);
u16  WifiCoreRecvPolling(void);
/*---------------------------------------------------------------------------------------------------------*/
/* WIFI_CORE COMMAND DEFINE END                                                                            */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* WIFI Host COMMAND DEFINE                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define HOST_TO_UNIT_POWER_CONTROL				0

#define UNIT_TO_HOST_ENTER_SYSTEM				1
#define HOST_TO_UNIT_REP_ENTER_SYSTEM			2

#define HOST_TO_UNIT_ENTER_MEETING_MODE			3
#define HOST_TO_UNIT_CHANGE_MIC_MANAGE			50

#define UNIT_TO_HOST_APPLY_OPENMIC				4
#define HOST_TO_UNIT_REP_APPLY_OPENMIC			5
#define UNIT_TO_HOST_APPLY_CLOSEMIC				6	
#define HOST_TO_UNIT_CONTROL_MIC				7
#define UNIT_TO_HOST_MIC_GET_OUT_WAIT			8

#define UNIT_TO_HOST_VIP_KEY					9
#define HOST_TO_UNIT_REP_VIP_KEY				10

#define HOST_TO_UNIT_REPRESENT_APPLY			11
#define UNIT_TO_HOST_REPRESENT_APPLY			12

#define HOST_TO_UNIT_FIRE_WARNING_MODE			14	

#define HOST_TO_UNIT_INTO_UP_TIME_STATEMENT    	15
#define HOST_TO_UNIT_INTO_DOWN_TIME_STATEMENT	16

#define UNIT_TO_HOST_APPLY_SERVICE				17

#define HOST_TO_UNIT_SIGN_MODE					19
#define HOST_TO_UNIT_ENABLE_SIGN				20
#define HOST_TO_UNIT_SUPPLY_SIGN				21
#define UNIT_TO_HOST_SUPPLY_SIGN				22
#define HOST_TO_UNIT_CONTROL_SIGN				49

#define HOST_TO_UNIT_VOTE_MODE					25
#define HOST_TO_UNIT_ENABLE_VOTE				29
#define HOST_TO_UNIT_VOTE_NAME					51

#define HOST_TO_UNIT_POLLING_UNIT				40
#define UNIT_TO_HOST_REP_POLLING_UNIT			41

#define HOST_TO_UNIT_PRINT_MESSAGE				42
#define HOST_TO_UNIT_FIX_MESSAGE				43

#define HOST_TO_UNIT_SETID_MODE					44
#define UNIT_TO_HOST_SETID						45
#define HOST_TO_UNIT_IDREPEAT					46
#define HOST_TO_UNIT_SETID_CONFIRM				52

#define HOST_TO_UNIT_RECONNECT					47
#define UNIT_TO_HOST_STATE_TOO_LOW				48

#define HOST_TO_UNIT_VOICE_SEN					60
#define HOST_TO_UNIT_NO_SIGNAL_SEC				61

#define HOST_TO_UNIT_SET_LANG					30

#define HOST_TO_UNIT_SET_EQ_FILTER				35
#define HOST_TO_UNIT_MIC_SEN_PROC				36
#define UNIT_TO_HOST_MIC_SEN_REQ				37
#define HOST_TO_UNIT_MIC_EQ_PROC				38
#define UNIT_TO_HOST_MIC_EQ_REQ					39

#define HOST_TO_UNIT_RESET_PARM					63
#define HOST_TO_UNIT_MIC_SEN					64//回复PC声控关闭时间和灵敏度 20200518
#define UNIT_TO_HOST_MIC_SEN					65//回复PC声控关闭时间和灵敏度 20200518

void HostCommandSend(u8 cmd, u8 para1, u8 para2, u8 *data, u8 len);
void HostCommandSendEnterSystem(u8 in);
/*---------------------------------------------------------------------------------------------------------*/
/* WIFI Host COMMAND DEFINE END                                                                            */
/*---------------------------------------------------------------------------------------------------------*/






#endif

