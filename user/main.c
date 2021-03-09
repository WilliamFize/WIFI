#include "types.h"



/*---------------------------------------------------------------------------------------------------------*/
/* Init System Define                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
void SystemClockInit(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
	
//	SYS_DISABLE_LVR();//禁止低压复位
    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Set core clock as HCLK_CLOCK */
    CLK_SetCoreClock(HCLK_CLOCK);

	/* Set tick clock src */
	CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLK_S_HIRC_DIV2);
	SysTick->CTRL = SysTick->CTRL & ~(1 << SysTick_CTRL_CLKSOURCE_Pos);

	
	/* Lock protected registers */
    SYS_LockReg();
}

typedef enum 
{
	SAVE_FIRST_USER_ADDR = 0x00,
	SAVE_UNIT_ID_ADDR,
	SAVE_WIFI_CORE_VER_ADDR,
	SAVE_INFO_STAT_BIT_ARRR,
	SAVE_UID_KEY_1_ADDR,
	SAVE_UID_KEY_2_ADDR,
	SAVE_UID_KEY_3_ADDR,
	SAVE_UID_KEY_4_ADDR,
	SAVE_MIC_VOICE_PARA_ADDR,
	SAVE_MIC_SEN_AND_FILTER_ADDR,
	SAVE_MIC_EQ1_TO_EQ4_ADDR,
	SAVE_MIC_EQ5_ADDR,
	SAVE_LANG_ADDR,
	SAVE_USER_DATA_LEN
}SYS_SAVE_DATA_T;

#define FIRST_USE_MCU_FLAG				0x20181016
#define INFO_STAT_BIT_ENABLE_MIC		0
#define INFO_STAT_BIT_ENABLE_SIGN		1
#define INFO_STAT_BIT_ENABLE_VOTE		2

u32    		system_save_data[SAVE_USER_DATA_LEN];
INFO_T 		info;
SET_ID_T 	setid;
SIGN_T 		sign;
WIFI_T		wifi;
VOTE_T  	vote;

void SystemGlobalSet(void)
{	
	system_save_data[SAVE_FIRST_USER_ADDR]		= FIRST_USE_MCU_FLAG;
		
	system_save_data[SAVE_UNIT_ID_ADDR] 		= setid.local;

	system_save_data[SAVE_WIFI_CORE_VER_ADDR]	= U8_4_Change_U32(info.ver + WIFI_CORE_VER_SHIFT);

	system_save_data[SAVE_INFO_STAT_BIT_ARRR]	= mic.enable  << INFO_STAT_BIT_ENABLE_MIC  |
												  sign.enable << INFO_STAT_BIT_ENABLE_SIGN |
												  vote.enable << INFO_STAT_BIT_ENABLE_VOTE;
	
	system_save_data[SAVE_UID_KEY_1_ADDR]		= U8_4_Change_U32(info.uid_key);
	system_save_data[SAVE_UID_KEY_2_ADDR]		= U8_4_Change_U32(info.uid_key + 4);
	system_save_data[SAVE_UID_KEY_3_ADDR]		= U8_4_Change_U32(info.uid_key + 8);
	system_save_data[SAVE_UID_KEY_4_ADDR]		= U8_4_Change_U32(info.uid_key + 12);

	system_save_data[SAVE_LANG_ADDR]			= info.lang;

	system_save_data[SAVE_MIC_VOICE_PARA_ADDR]	= (u32)mic.nos_tmr << 16 | mic.v_sen;

	system_save_data[SAVE_MIC_SEN_AND_FILTER_ADDR] = (u32)mic.sen << 16 | mic.filter_en;
	
	system_save_data[SAVE_MIC_EQ1_TO_EQ4_ADDR]  = U8_4_Change_U32(&mic.eq[0]);
	system_save_data[SAVE_MIC_EQ5_ADDR]         = mic.eq[4];
}

void SystemGlobalInit(void)
{
	DataFlashInit(system_save_data, SAVE_USER_DATA_LEN);
	
	
	mic.send_ch   		=  0x88;
	mic.open_total		=  MIC_OPEN_TOTAL_1;
	info.unit_opration	=  UNIT_OPRATION_HOST_DISCONNECT_MODE;
	info.time_statement = UP_STATEMENT;//20200907默认发言计时
	info.time_statement_max = 0;//20200907默认发言计时
//	info.time_statement	=  NO_STATEMENT;
	info.wifi_core_startup	=  WIFI_CORE_STARTUP_WAIT_UART;

	sprintf(info.ver, DEFAULT_DISPLAY_VER);
	
	if(system_save_data[SAVE_FIRST_USER_ADDR] != FIRST_USE_MCU_FLAG)
	{
		setid.local	= 0x3001;
		mic.enable	= TRUE;
		sign.enable	= TRUE;
		vote.enable	= TRUE;
		mic.nos_tmr = 3000;
		mic.v_sen	= 130 + 2 * 60;
		
		mic.sen = 4;// 0db
		mic.filter_en = 0;
		memset(mic.eq, 0x2C, 5);// 0db, band select 1
		
		info.lang	= LANG_CHINESE;
		
		SystemGlobalSet();
		DataFlashSave(system_save_data, SAVE_USER_DATA_LEN);
	}
	else
	{		
		setid.local	= system_save_data[SAVE_UNIT_ID_ADDR];
		
		sign.enable	= DATA_BIT_CHANGE_STAT(system_save_data[SAVE_INFO_STAT_BIT_ARRR], INFO_STAT_BIT_ENABLE_SIGN);

		vote.enable	= DATA_BIT_CHANGE_STAT(system_save_data[SAVE_INFO_STAT_BIT_ARRR], INFO_STAT_BIT_ENABLE_VOTE);

		mic.enable 	= DATA_BIT_CHANGE_STAT(system_save_data[SAVE_INFO_STAT_BIT_ARRR], INFO_STAT_BIT_ENABLE_MIC);

		U32_Change_U8_4(system_save_data[SAVE_WIFI_CORE_VER_ADDR], info.ver + WIFI_CORE_VER_SHIFT);

		U32_Change_U8_4(system_save_data[SAVE_UID_KEY_1_ADDR], info.uid_key);
		U32_Change_U8_4(system_save_data[SAVE_UID_KEY_2_ADDR], info.uid_key + 4);
		U32_Change_U8_4(system_save_data[SAVE_UID_KEY_3_ADDR], info.uid_key + 8);
		U32_Change_U8_4(system_save_data[SAVE_UID_KEY_4_ADDR], info.uid_key + 12);

		mic.nos_tmr = system_save_data[SAVE_MIC_VOICE_PARA_ADDR] >> 16;
		mic.v_sen   = system_save_data[SAVE_MIC_VOICE_PARA_ADDR];

		mic.sen		  = system_save_data[SAVE_MIC_SEN_AND_FILTER_ADDR] >> 16;
		mic.filter_en = system_save_data[SAVE_MIC_SEN_AND_FILTER_ADDR];

		U32_Change_U8_4(system_save_data[SAVE_MIC_EQ1_TO_EQ4_ADDR], &mic.eq[0]);
		mic.eq[4] = system_save_data[SAVE_MIC_EQ5_ADDR];

		info.lang	= system_save_data[SAVE_LANG_ADDR];
	}

	info.master_unit = !GPIO_MASTER_CHOOSE_PI();
	if(info.master_unit)
		mic.nos_tmr = 0;

	mic.sen_preset = mic.sen;
	memcpy(mic.eq_preset, mic.eq, 5);
	
}

void GpioNormalInit(void)
{
	GPIO_MIC_MUTE_INIT();
	GPIO_MIC_MUTE_SET_RELEASE();
	
	GPIO_E_DET_INIT();

	GPIO_MIC_LED_G_INIT();
	GPIO_MIC_LED_G_OFF();
	
	GPIO_MIC_LED_R_INIT();
	GPIO_MIC_LED_R_OFF();
	
	GPIO_POWER_SW_INIT();

	GPIO_POWER_CTL_INIT();
	GPIO_POWER_CTL_ON();

	GPIO_AU_MUTE_INIT();
	GPIO_AU_MUTE_SET_RELEASE();
	
	GPIO_OLED_POWER_CTL_INIT();
	GPIO_OLED_POWER_CTL_ON();

	GPIO_OLED_VBAT_INIT();
	GPIO_OLED_DC_INIT();
	GPIO_OLED_RST_INIT();

	GPIO_CHARGE_CHECK_INIT();
	
	GPIO_MASTER_CHOOSE_INIT();
	
	GPIO_KEY_VIP_INIT();
	GPIO_KEY_MIC_KEY_INIT();

	SYS->GPF_MFP  &= ~(SYS_GPF_MFP_PF3_Msk  | SYS_GPF_MFP_PF2_Msk);
    SYS->GPF_MFP  |= (SYS_GPF_MFP_PF3_GPIO  | SYS_GPF_MFP_PF2_GPIO);
	SYS->ALT_MFP1 &= ~(SYS_ALT_MFP1_PF3_Msk | SYS_ALT_MFP1_PF2_Msk);
    SYS->ALT_MFP1 |= SYS_ALT_MFP1_PF3_GPIO  | SYS_ALT_MFP1_PF2_GPIO;
	GPIO_DISPLAY_VIP_INIT();
	GPIO_DISPLAY_VIP_OFF();
	
	GPIO_DISPLAY_MIC_INIT();
	GPIO_DISPLAY_MIC_OFF();
}

/*---------------------------------------------------------------------------------------------------------*/
/* Init System Define End                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* System Process Define                                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
void SystemPowerDown(void)
{	
	SystemGlobalSet();
	DataFlashSave(system_save_data, SAVE_USER_DATA_LEN);
	
	HardwordCloseMic(FALSE, TRUE);

	if(info.host_connect)
	{
		HostCommandSendEnterSystem(FALSE);
		delay_ms(50);
	}
	
	GPIO_POWER_CTL_OFF();
	GPIO_OLED_POWER_CTL_OFF();
	OLEDCPUSendOff();
	
	while(1);
}

void HostDisconnectDo(void)
{
	info.host_connect 		= FALSE;
	info.fire_warning		= FALSE;
	info.unit_opration  	= UNIT_OPRATION_HOST_DISCONNECT_MODE;
//	info.time_statement 	= UP_STATEMENT;//20200907默认发言计时
	vote.result				= 0x00;
	wifi.low				= FALSE;
	mic.use					= FALSE;
	mic.led					= FALSE;
	popup.enable			= FALSE;

	HardwordCloseMic(FALSE, TRUE);
}

void LedStaticControl(LED_CONTROL_E ctrl)
{
	info.led_flash_count = 0;
	switch(ctrl)
	{
		case LED_CONTROL_ALL_CLOSE:
		case LED_CONTROL_MIC_CLOSE:
			GPIO_MIC_LED_R_OFF();
			GPIO_MIC_LED_G_OFF();
			GPIO_DISPLAY_MIC_OFF();
			break;
		case LED_CONTROL_ALREADY_SETID:
		case LED_CONTROL_ALREADY_SIGN:
		case LED_CONTROL_MIC_OPEN:
			GPIO_MIC_LED_R_ON();
			GPIO_MIC_LED_G_OFF();
			GPIO_DISPLAY_MIC_ON();
			break;
		case LED_CONTROL_MIC_APPLY:
		case LED_CONTROL_MIC_WAIT:
			GPIO_MIC_LED_R_OFF();
			GPIO_MIC_LED_G_ON();
			GPIO_DISPLAY_MIC_OFF();
			break;
	}	
}

/*---------------------------------------------------------------------------------------------------------*/
/* System Process Define End                                                                               */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/*System Polling Define                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define ENTER_SYS_POLLING_TIME		150	// 1.5s   1200	//
#define HOST_DISCONNECT_TIMES		6000	// 60s
#define AP_DISCONNECT_TIMES			1500	// 15s
#define UART_DISCONNECT_TIMES		500     // 5s
void SystemConnectPolling(void)
{		
	switch(info.wifi_core_startup)
	{
		case WIFI_CORE_STARTUP_FINISH:
		case WIFI_CORE_STARTUP_WAIT_HOST:
		case WIFI_CORE_STARTUP_HOST_DISCONNECT:
			if(wifi.connect)
			{
				if(info.host_connect)
				{
					if(info.host_lost_count >= HOST_DISCONNECT_TIMES)
					{
						HostDisconnectDo();
						info.host_lost_count = 0;
						DisplayHostLose();
					}
					else
						info.host_lost_count++;
				}
				else
				{
					if(info.overcount >= ENTER_SYS_POLLING_TIME)
					{
						if(wifi.rssi > 0)
						{
							DisplayHostLose();
							HostCommandSendEnterSystem(TRUE);
							if(info.wifi_core_startup != WIFI_CORE_STARTUP_FINISH)
								info.wifi_core_startup = WIFI_CORE_STARTUP_HOST_DISCONNECT;
						}
						info.overcount = 0;
					}
					else
						info.overcount++;
				}
			}
			break;
		case WIFI_CORE_STARTUP_WAIT_UART:
			if(info.overcount >= UART_DISCONNECT_TIMES)
			{
				info.wifi_core_startup = WIFI_CORE_STARTUP_UART_ERROR;
				DisplayUartError();
			}
			else
				info.overcount++;
			break;			
		case WIFI_CORE_STARTUP_WAIT_AP:
			if(info.overcount >= AP_DISCONNECT_TIMES)
			{
				info.wifi_core_startup = WIFI_CORE_STARTUP_AP_DISCONNECT;
				DisplayAPLose();
			}
			else 
				info.overcount++;
			break;
		default:
			break;
	}

	if(info.wifi_core_startup < WIFI_CORE_STARTUP_FINISH)
	{
		DisplayStartupFlash();
	}
}


#define LED_FIRE_WARNING_FLASH_TIMER 		25	
#define LED_SIGN_FLASH_TIMER				25
#define LED_SET_ID_SUCESS_FLASH_TIMER		20
void LedFlashPolling(void)
{
	if(info.fire_warning)
	{
		if(info.led_flash_count)
			info.led_flash_count--;
		else
		{
			GPIO_DISPLAY_MIC_PO(~ GPIO_DISPLAY_MIC_PI());
			GPIO_MIC_LED_R_PO(~ GPIO_MIC_LED_R_PI());
			info.led_flash_count = LED_FIRE_WARNING_FLASH_TIMER;
		}
	}
	else
	{
		if(info.unit_opration == UNIT_OPRATION_SIGN_MODE)
		{
			if(sign.already == FALSE && sign.enable)
			{
				if(info.led_flash_count)
					info.led_flash_count--;
				else
				{
					GPIO_DISPLAY_MIC_PO(~ GPIO_DISPLAY_MIC_PI());
					GPIO_MIC_LED_R_PO(~ GPIO_MIC_LED_R_PI());
					info.led_flash_count = LED_SIGN_FLASH_TIMER;
				}
			}
		}
		else if(info.unit_opration == UNIT_OPRATION_SETID_MODE)
		{
			if(setid.sucess)
			{
				if(info.led_flash_count)
				{
					info.led_flash_count--;
					GPIO_DISPLAY_MIC_OFF();
					GPIO_MIC_LED_R_OFF();
				}
				else
				{
					setid.sucess--;
					GPIO_DISPLAY_MIC_ON();
					GPIO_MIC_LED_R_ON();
					info.led_flash_count = LED_SET_ID_SUCESS_FLASH_TIMER;
				}
			}
			else
			{
				info.led_flash_count = LED_SET_ID_SUCESS_FLASH_TIMER;
			}
		}
	}
}

#define MIC_APPLY_DELAY_CLOSE_TIME	15
void MicStatementPolling(void)
{
	static u16 apply_count;
	
	if(mic.status == MIC_STATUS_APPLY)
	{
		if(apply_count < MIC_APPLY_DELAY_CLOSE_TIME)
			apply_count++;
		else
		{
			HardwordCloseMic(TRUE, mic.led);
			if(popup.enable)
				IMAGE_HOME_DISPLAY();
		}
	}
	else
	{
		apply_count = 0;

		if(mic.status == MIC_STATUS_OPEN)
		{
			switch(info.time_statement)
			{
				case NO_STATEMENT:
					break;
				case UP_STATEMENT:
					info.time_statement_count++;
					if(popup.enable && popup.status == POPUP_NULL)
					{
						IMAGE_MIC_TIME_DISPLAY();
					}
					break;
				case DOWN_STATEMENT:
					if(info.time_statement_count > 1)
					{
						info.time_statement_count--;
						if(popup.enable && popup.status == POPUP_NULL)
						{
							IMAGE_MIC_TIME_DISPLAY();
						}
					}
					else
					{
						HardwordCloseMic(TRUE, mic.led);
						if(popup.enable)
							IMAGE_MIC_CLOSE_DISPLAY();
					}
					break;
			}
		}
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/*System Polling Define End                                                                                */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* Main Funtion Define                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
void Wm8974SpecialParmInit(void)
{
	u8 i;
	SetMicSen2WM8974(mic.sen_preset);
	Wm8974SetFilter(mic.filter_en);
	for(i = 0; i < 5; i++) {
		Wm8974SetEQValue(i, mic.eq_preset[i]);
	}
}
void ClearMICFullstate(void)
{
	if(info.MICFULLFlag)
	{
		info.MICFULLFlag--;
		if((info.MICFULLFlag==0)&&(mic.status == MIC_STATUS_CLOSE))
		{
			if(popup.enable)
				IMAGE_MIC_CLOSE_DISPLAY();
		}			
	}
}
int main(void)
{
	SystemClockInit();
	GpioNormalInit();
	SystemGlobalInit();
	OLEDSpiInit();
	SystemTimer0Init();
	HID_Init();
	WifiCoreUSARTInit();
//	UsbRecvUidAes();
	Wm8974RegisterInit();
	Wm8974SpecialParmInit();
	SystemAdcInit();
	
	while(1)
	{
		WifiCoreRecvPolling();
		UsbRecvPolling();

		if(timer0_delay_1ms_count == 0)
		{
			KeyInputPolling();
			timer0_delay_1ms_count = TIMER0_DELAY_1MS;
		}
		
		if(timer0_delay_10ms_count == 0)
		{
			SystemReadAdcPolling();
			SystemConnectPolling();
			LedFlashPolling();
			//MicOpenFadePolling();
			timer0_delay_10ms_count = TIMER0_DELAY_10MS;
					
//			if(timer0_10ms_flag<5)
//			{
//				timer0_10ms_flag++;
//			}
//			else 
//			if(mic.use)
//			{
//				timer0_10ms_flag=0;
//				if(mic.status == MIC_STATUS_CLOSE)
//				{
//					HostCommandSend(UNIT_TO_HOST_APPLY_OPENMIC, info.master_unit, 0x00, NULL, 0x00);
//				}
//				else
//				{				
//					HardwordCloseMic(TRUE, mic.led);
//					if(popup.enable)
//					{
//						IMAGE_MIC_CLOSE_DISPLAY();
//					}
//				}
//			}
		}

		if(timer0_delay_1s_already)
		{
			MicStatementPolling();
			DisplayPopupTimeoutPolling();
			timer0_delay_1s_already = FALSE;
			ClearMICFullstate();//20200526话筒已满，显示3秒自动清状态
			
			OLEDNegation();//屏幕反显
		}

		OLEDDMAPolling();
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/* Main Funtion Define END                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/



