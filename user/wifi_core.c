#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
/* UART INIT DEFINE                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define WIFI_CORE_RECV_MIN_DATA		1
#define WIFI_CORE_RECV_DATA_LEN		50
#define WIFI_CORE_RECV_QUEUE_LEN	16

struct
{
	struct
	{
		u8 data[WIFI_CORE_RECV_DATA_LEN];
		u8 len;
	}q[WIFI_CORE_RECV_QUEUE_LEN];
	volatile u8 revcnt;
	volatile u8 find_step;
	volatile u8 w_p;
	volatile u8 r_p;
}wifi_core_recv;

#define WIFI_CORE_PACKET_FIND_0x5A 	0x00
#define WIFI_CORE_PACKET_FIND_0xA5 	0x01
#define WIFI_CORE_PACKET_FIND_LEN  	0x02
#define WIFI_CORE_PACKET_FIND_DATA 	0x03

void WifiCoreUSARTInit(void)
{
	SYS_UnlockReg();

	wifi_core_recv.find_step = WIFI_CORE_PACKET_FIND_0x5A;
	wifi_core_recv.r_p = 0;
	wifi_core_recv.w_p = 0;
	
	CLK_EnableModuleClock(UART1_MODULE);

    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART_S_HIRC, CLK_CLKDIV_UART(1));

	SYS->GPB_MFP  &= ~(SYS_GPB_MFP_PB4_Msk | SYS_GPB_MFP_PB5_Msk);
    SYS->GPB_MFP  |= (SYS_GPB_MFP_PB4_UART1_RXD | SYS_GPB_MFP_PB5_UART1_TXD);
	SYS->ALT_MFP  &= ~(SYS_ALT_MFP_PB4_Msk | SYS_ALT_MFP_PB5_Msk);
    SYS->ALT_MFP  |= SYS_ALT_MFP_PB4_UART1_RXD| SYS_ALT_MFP_PB5_UART1_TXD;

	SYS_ResetModule(UART1_RST);

    UART_Open(UART1, 115200);

	NVIC_SetPriority(UART1_IRQn, 0);
	
	UART_EnableInt(UART1, UART_IER_RDA_IEN_Msk);

	SYS_LockReg();
}

void UART1_IRQHandler(void)
{
    u8 u8InChar = 0xFF;
    u32 u32IntSts = UART1->ISR;

    if(u32IntSts & UART_ISR_RDA_INT_Msk)
    {
        while(UART_IS_RX_READY(UART1))
        {
            /* Get the character from UART Buffer */
            u8InChar = UART_READ(UART1);

            switch(wifi_core_recv.find_step)
			{
				case WIFI_CORE_PACKET_FIND_0x5A:
							if(u8InChar == 0x5A)
								wifi_core_recv.find_step = WIFI_CORE_PACKET_FIND_0xA5;
							break;
				case WIFI_CORE_PACKET_FIND_0xA5:
							if(u8InChar == 0xA5)
								wifi_core_recv.find_step = WIFI_CORE_PACKET_FIND_LEN;
							else
								wifi_core_recv.find_step = WIFI_CORE_PACKET_FIND_0x5A;
							break;
				case WIFI_CORE_PACKET_FIND_LEN:
							if(u8InChar < WIFI_CORE_RECV_MIN_DATA || u8InChar >= WIFI_CORE_RECV_DATA_LEN)//小于命令数量，舍弃消息
							{
								wifi_core_recv.find_step = WIFI_CORE_PACKET_FIND_0x5A;
							}
							else
							{
								wifi_core_recv.q[wifi_core_recv.w_p].len = u8InChar;
								wifi_core_recv.revcnt = 0;
								wifi_core_recv.find_step = WIFI_CORE_PACKET_FIND_DATA;
							}
							break;
				case WIFI_CORE_PACKET_FIND_DATA:
							if(wifi_core_recv.revcnt < wifi_core_recv.q[wifi_core_recv.w_p].len)
							{
								wifi_core_recv.q[wifi_core_recv.w_p].data[wifi_core_recv.revcnt++] = u8InChar;
							}
							else
							{
								wifi_core_recv.find_step = WIFI_CORE_PACKET_FIND_0x5A;
								if(u8InChar == 0xFC)
								{
									wifi_core_recv.w_p = (wifi_core_recv.w_p + 1) & (WIFI_CORE_RECV_QUEUE_LEN - 1);
								}
							}
							break;
			}
        }
    }
}

void WifiCoreWriteByte(u8 * data, u8 len)
{
	u8  i = 0;
	
	for(i=0;i<len;i++)
	{
		while(UART_IS_TX_FULL(UART1));              
		UART_WRITE(UART1, data[i]);
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/* UART INIT DEFINE END                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* WIFI Host COMMAND DEFINE                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
void HostCommandSend(u8 cmd, u8 para1, u8 para2, u8 *data, u8 len)
{
	u8 head[7];
	u8 tail;

	head[0] = 0x5A;
	head[1] = 0xA5;
	head[2] = len + 4;
	head[3] = MCU_TO_HOST_COMMAND;
	head[4] = cmd;
	head[5] = para1;
	head[6] = para2;
	tail	= 0xFC;
	
	WifiCoreWriteByte(head, 7);

	if(data != NULL)
	{
		delay_ms(1);
		WifiCoreWriteByte(data, len);
	}

	WifiCoreWriteByte(&tail, 1);
}

void HostCommandSendEnterSystem(u8 in)
{
	u8 data[4];
	data[0] = info.master_unit;
	data[1] = !in;
	data[2] = info.battery;
	data[3] = wifi.rssi;
	WifiCoreCommandSend(MCU_TO_HOST_ENTER_SYSTEM, data, 4);
}

static void HostRecvCheck(u8 *data, u8 len)
{
	u8  cmd   		= data[0];
	u8  para1 		= data[1];
	u8  para2		= data[2];
	u8  *content	= &data[3];
	u16 u16_temp 	= 0;
	u8  u8_temp  	= 0;
	u8  detail[32];

	switch(cmd)
	{
		case HOST_TO_UNIT_POWER_CONTROL:
			if(para1 == 0)
			{
				HostDisconnectDo();
			}
			else
			{
				SystemPowerDown();
			}
			break;
		case HOST_TO_UNIT_REP_ENTER_SYSTEM:
			if(para1 == 0x00)
			{
				info.host_connect = TRUE;
				info.wifi_core_startup = WIFI_CORE_STARTUP_FINISH;
				DisplayStatusInfo();
								
				switch(content[0])
				{
					case UNIT_OPRATION_MEETING_MODE:
						info.unit_opration  = UNIT_OPRATION_MEETING_MODE;
						mic.mode   			= content[1];
						mic.open_total		= content[2];
						DisplayRestoreMeetingMode();
						break;
					case UNIT_OPRATION_SIGN_MODE:
						info.unit_opration  = UNIT_OPRATION_SIGN_MODE;						
						sign.total 			= ((u16)content[1] << 8) | content[2];
						sign.already_total 	= ((u16)content[3] << 8) | content[4];
						sign.already   		= content[5];
						mic.mode   			= content[6];
						mic.open_total 		= content[7];
						DisplayRestoreSignMode();
						break;
					case UNIT_OPRATION_VOTE_MODE:
						info.unit_opration  = UNIT_OPRATION_VOTE_MODE;
						vote.type			= content[1];
						mic.mode    		= content[2];
						mic.open_total  	= content[3];
						vote.result			= content[4];
						sign.already		= content[5];
						DisplayRestoreVoteMode();
						break;
					case UNIT_OPRATION_SETID_MODE:
						info.unit_opration  = UNIT_OPRATION_SETID_MODE;
						setid.current = (u16)(content[1] << 8) | content[2];
						setid.already = FALSE;
						setid.sucess  = 0;
						DisplayRestoreSetIDMode();
						break;
					default:
						break;
				}
			}		
			break;
		case HOST_TO_UNIT_IDREPEAT:
			if(info.unit_opration != UNIT_OPRATION_IDREPEAT_MODE)
			{
				if(info.host_connect == FALSE)
				{
					info.host_connect   = TRUE;
					DisplayStatusInfo();
				}
				else
				{
					HardwordCloseMic(FALSE, FALSE);
				}
				info.unit_opration  = UNIT_OPRATION_IDREPEAT_MODE;
				info.wifi_core_startup	= WIFI_CORE_STARTUP_FINISH;
				DisplayRestoreIDRepeatMode();
			}
			break;
		default:
			break;
	}

	if(info.host_connect)
	{
		switch(cmd)
		{
			case HOST_TO_UNIT_REP_VIP_KEY:
			case HOST_TO_UNIT_REP_APPLY_OPENMIC:
				switch(para1)
				{
					case 0x00://准予开唛
						HardwordOpenMic(content[0], mic.led);
						if(info.time_statement != NO_STATEMENT)
							DisplayMicStartTimeStatement();
						else
						{
							if(popup.enable)
								IMAGE_MIC_OPEN_DISPLAY();
						}
						break;
					case 0x01://话筒已满
					case 0x04://等待队列已满
						if(popup.enable)
						{
							IMAGE_MIC_FULL_DISPLAY();
							info.MICFULLFlag=3;//20200526话筒已满，显示3秒自动清状态
						}
							
						break;
					case 0x03://进入等待队列
						if(mic.mode == MIC_MODE_APPLY)
						{
							mic.status = MIC_STATUS_APPLY;
							if(popup.enable)
								IMAGE_MIC_APPLYING_DISPLAY();
							LedStaticControl(mic.status);
						}
						else
						{
							mic.status = MIC_STATUS_WAIT;
							if(popup.enable)
								IMAGE_MIC_WAITING_DISPLAY();
							LedStaticControl(mic.status);
						}
						break;
				}
				break;
			case HOST_TO_UNIT_CONTROL_MIC:
				if(para1 == 0x00)//打开话筒
				{
					HardwordOpenMic(content[0], mic.led);
					if(info.time_statement != NO_STATEMENT)
						DisplayMicStartTimeStatement();
					else
					{
						if(popup.enable)
							IMAGE_MIC_OPEN_DISPLAY();
					}
				}
				else//关闭话筒
				{
					HardwordCloseMic(FALSE, mic.led);
					if(popup.enable)
						IMAGE_MIC_CLOSE_DISPLAY();
				}
				break;
			case HOST_TO_UNIT_POLLING_UNIT:
				if(info.unit_opration == UNIT_OPRATION_MEETING_MODE)
					u8_temp   = !mic.enable 	<< 1 |
								!sign.enable  	<< 3 |
								!vote.enable  	<< 4;
				else
					u8_temp   =  sign.already 	<< 0 |
								!mic.enable 	<< 1 |
								!sign.enable  	<< 3 |
								!vote.enable  	<< 4;
				detail[0] = info.battery;
				detail[1] = wifi.rssi;
//				detail[2] = (mic.v_sen-130)/2;//20200520增加回复主机声控灵敏度和声控关闭时间			
//				if(info.master_unit == FALSE)
//				{
//					detail[3] = mic.nos_tmr/100;
//				}
//				else
//				{
//					detail[3] = 0;
//				}
				HostCommandSend(UNIT_TO_HOST_REP_POLLING_UNIT, u8_temp, vote.result, detail, 2);
				break;
			case HOST_TO_UNIT_RECONNECT:
				HostDisconnectDo();
				break;
			case HOST_TO_UNIT_SIGN_MODE:
				if(para1 == 0)
				{
					sign.total = ((u16)content[0] << 8) | content[1];
					sign.already_total = ((u16)content[2] << 8) | content[3];

					if(info.unit_opration != UNIT_OPRATION_SIGN_MODE)
					{
						info.unit_opration = UNIT_OPRATION_SIGN_MODE;
						sign.already = FALSE;
						mic.use = (mic.mode != MIC_MODE_APPLY || info.master_unit) ? TRUE : FALSE;
						popup.enable = FALSE;
						
						if(sign.enable)
						{
							mic.led  	 = FALSE;
							IMAGE_SIGN_DISPLAY();
							LedStaticControl(LED_CONTROL_ALL_CLOSE);
						}
						else
						{
							mic.led	 	 = TRUE;
							IMAGE_SIGN_BANNED_DISPLAY();
						}
						
						if(mic.use == FALSE)
						{
							HardwordCloseMic(FALSE, mic.led);
						}
					}

					if(sign.enable)
						IMAGE_SIGN_NUM_DISPLAY();
				}
				break;
			case HOST_TO_UNIT_ENABLE_SIGN:
				if(para1 == 0)
					sign.enable  = TRUE;
				else
					sign.enable  = FALSE;

				if(info.unit_opration == UNIT_OPRATION_SIGN_MODE)
					DisplayRestoreSignMode();
				break;
			case HOST_TO_UNIT_SUPPLY_SIGN:
				HostCommandSend(UNIT_TO_HOST_SUPPLY_SIGN, 0x00, 0x00, NULL, 0);
				sign.already = TRUE;
				break;
			case HOST_TO_UNIT_CONTROL_SIGN:
				if(sign.enable && sign.already == FALSE)
				{
					sign.already_total += 1;
					IMAGE_SIGN_NUM_DISPLAY();
					LedStaticControl(LED_CONTROL_ALREADY_SIGN);
					sign.already = TRUE;//20200526单元禁止签到后，应该为不能控制（协助）签到；可以在结束后补充签到
				}			
				break;
			case HOST_TO_UNIT_FIRE_WARNING_MODE:
				if(para1 == 0)
				{
					if(info.fire_warning == FALSE)
					{
						info.fire_warning = TRUE;
						mic.led  	      = FALSE;
						mic.use			  = FALSE;
						popup.enable      = FALSE;
						LedStaticControl(LED_CONTROL_ALL_CLOSE);
						OLEDDMAFill(128, 48, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1);
						IMAGE_FIRE_WARNNING_DISPLAY();
					}
				}
				else
				{
					info.fire_warning = FALSE;		

					switch(info.unit_opration)
					{
						case UNIT_OPRATION_VOTE_MODE:
						case UNIT_OPRATION_VOTE_RESULT_MODE:
							DisplayRestoreVoteMode();
							break;
						case UNIT_OPRATION_MEETING_MODE:
							DisplayRestoreMeetingMode();
							break;
						case UNIT_OPRATION_SIGN_MODE:
							DisplayRestoreSignMode();
							break;
						case UNIT_OPRATION_IDREPEAT_MODE:
							DisplayRestoreIDRepeatMode();
							break;
						case UNIT_OPRATION_SETID_MODE:
							DisplayRestoreSetIDMode();
							break;
						default:
							break;
					}
				}
				break;
			case HOST_TO_UNIT_SETID_MODE:
				u16_temp = ((u16)para1 << 8) | para2;

				if(info.unit_opration != UNIT_OPRATION_SETID_MODE)
				{
					info.unit_opration	 = UNIT_OPRATION_SETID_MODE;
					setid.current		 = u16_temp;
					setid.sucess    	 = 0;
					setid.already   	 = FALSE;
				
					HardwordCloseMic(FALSE, FALSE);
					DisplayRestoreSetIDMode();
				}

				/*if(setid.press)
				{
					setid.press = FALSE;
					if(u16_temp == setid.current + 1)
					{	
						setid.already = TRUE;
						setid.local = setid.current;
						setid.sucess++;
						
						detail[0] = setid.local >> 8;
						detail[1] = setid.local;
						WifiCoreCommandSend(MCU_TO_WIFI_CORE_ID, detail, 2);
						IMAGE_SET_LOCAL_ID_DISPLAY();
						OLEDDMAShowNumFill(setid.local - 0x3000, 3, OLED_8_16_4_COL7,  OLED_8_16_4_PAGE0);
					}
				}*/
				
				if(setid.current != u16_temp)
				{
					setid.current = u16_temp;
					IMAGE_SET_CURRENT_ID_DISPLAY();
				}			
				break;
			case HOST_TO_UNIT_SETID_CONFIRM:
				u16_temp = ((u16)para1 << 8) | para2;
				
				setid.already = TRUE;
				setid.local = u16_temp;
				setid.sucess++;
				
				detail[0] = setid.local >> 8;
				detail[1] = setid.local;
				WifiCoreCommandSend(MCU_TO_WIFI_CORE_ID, detail, 2);
				IMAGE_SET_LOCAL_ID_DISPLAY();
				OLEDDMAShowNumFill(setid.local - 0x3000, 3, OLED_8_16_4_COL7,  OLED_8_16_4_PAGE0);
				break;
			case HOST_TO_UNIT_ENTER_MEETING_MODE:
				info.unit_opration	= UNIT_OPRATION_MEETING_MODE;
				mic.mode    		= para1;
				mic.open_total  	= para2;
				DisplayRestoreMeetingMode();
				break;
			case HOST_TO_UNIT_CHANGE_MIC_MANAGE:
				mic.mode    		= para1;
				mic.open_total  	= para2;
//				if(mic.status != MIC_STATUS_CLOSE)//切换话筒管理模式时。话筒数量已满没更新状态20200518
//				{
					HardwordCloseMic(FALSE, mic.led);
					if(popup.enable)
						IMAGE_MIC_CLOSE_DISPLAY();
//				}
				break;
			case HOST_TO_UNIT_INTO_UP_TIME_STATEMENT:
			case HOST_TO_UNIT_INTO_DOWN_TIME_STATEMENT:
				if(para1 == 0)
				{
					if(cmd == HOST_TO_UNIT_INTO_UP_TIME_STATEMENT)
					{
						info.time_statement 	      = UP_STATEMENT;
						info.time_statement_max 	  = 0;
						DisplayMicStartTimeStatement();
					}
					else if(info.master_unit == FALSE)//20200518只代表机有计时
					{
						info.time_statement 	      = DOWN_STATEMENT;
						info.time_statement_max 	  = (u16)content[0] << 8 | content[1];
						DisplayMicStartTimeStatement();
					}
					
				}
				else
				{
					info.time_statement = NO_STATEMENT;
					if(popup.enable)
					{
						switch(mic.status)
						{
							case MIC_STATUS_CLOSE:
							case MIC_STATUS_OPEN:
								IMAGE_HOME_DISPLAY();
								break;
							case MIC_STATUS_WAIT:
								IMAGE_MIC_WAITING_DISPLAY();
								break;
							case MIC_STATUS_APPLY:
								IMAGE_MIC_APPLYING_DISPLAY();
								break;
						}	
					}
				}
				break;
			case HOST_TO_UNIT_VOTE_MODE:
				if(para1 == 0x00)
				{
					info.unit_opration = UNIT_OPRATION_VOTE_MODE;
					vote.result	 	   = 0x00;
					vote.type		   = para2;
				}
				else if(para1 == 0x01)
				{
					info.unit_opration = UNIT_OPRATION_VOTE_RESULT_MODE;
				}

				DisplayRestoreVoteMode();

				if(mic.use == FALSE)
				{
					HardwordCloseMic(FALSE, mic.led);
				}
				break;
			case HOST_TO_UNIT_ENABLE_VOTE:
				if(para1 == 0)
					vote.enable  = TRUE;
				else
					vote.enable  = FALSE;
				break;
			case HOST_TO_UNIT_FIX_MESSAGE:
				if(popup.enable)
				{
					if(para1 == 0x01)
					{
						IMAGE_GO_TO_DOOR_DISPLAY();
					}
					else
					{
						IMAGE_GO_TO_CONSOLE_DISPLAY();
					}
				}
				break;
			case HOST_TO_UNIT_VOICE_SEN:
				mic.v_sen = 130+ 2 * para1;
				break;
			case HOST_TO_UNIT_NO_SIGNAL_SEC:
				if(info.master_unit == FALSE)
				{
					mic.nos_tmr = para1 * 100;
					VoiceModeNoSignalResetTimer();
				}
				break;
			case HOST_TO_UNIT_SET_LANG:
				if(para1 == 0x00 || para1 == 0x01) {
					if(para1 == 0x00)
						info.lang = LANG_ENGLISH;
					else
						info.lang = LANG_CHINESE;

					switch(info.unit_opration)
					{
						case UNIT_OPRATION_VOTE_MODE:
						case UNIT_OPRATION_VOTE_RESULT_MODE:
							DisplayRestoreVoteMode();
							break;
						case UNIT_OPRATION_MEETING_MODE:
							DisplayRestoreMeetingMode();
							break;
						case UNIT_OPRATION_SIGN_MODE:
							DisplayRestoreSignMode();
							break;
						case UNIT_OPRATION_IDREPEAT_MODE:
							DisplayRestoreIDRepeatMode();
							break;
						case UNIT_OPRATION_SETID_MODE:
							DisplayRestoreSetIDMode();
							break;
						default:
							break;
					}
				}
				break;
			case HOST_TO_UNIT_SET_EQ_FILTER:
				mic.filter_en = para1;
				Wm8974SetFilter(para1);
				break;
			case HOST_TO_UNIT_MIC_SEN_PROC:
				switch(para1) {
					case 0x00://设置麦克风灵敏度
						mic.sen_preset = para2;
						SetMicSen2WM8974(mic.sen_preset);
						break;
					case 0x01://获取麦克风灵敏度
						HostCommandSend(UNIT_TO_HOST_MIC_SEN_REQ, 0x00, mic.sen_preset, NULL, 0x00);
						break;
					case 0x02://保存麦克风灵敏度
						mic.sen = mic.sen_preset;
						break;
					case 0x03://恢复麦克风灵敏度默认值
						mic.sen_preset = 4;// 0db
						mic.sen = mic.sen_preset;
						SetMicSen2WM8974(mic.sen_preset);
						break;
					default:
						break;
				}
				break;
			case HOST_TO_UNIT_MIC_EQ_PROC:
				switch(para1) {
					case 0x00://设置麦克风某段EQ
						u8_temp  = (para2 >> 4) - 1;
						mic.eq_preset[u8_temp] = content[0];
						Wm8974SetEQValue(u8_temp, mic.eq_preset[u8_temp]);
						break;
					case 0x01://获取麦克风所有EQ值
						detail[0] = 1 << 4;
						detail[1] = mic.eq_preset[0];
						detail[2] = 2 << 4;
						detail[3] = mic.eq_preset[1];
						detail[4] = 3 << 4;
						detail[5] = mic.eq_preset[2];
						detail[6] = 4 << 4;
						detail[7] = mic.eq_preset[3];
						detail[8] = 5 << 4;
						detail[9] = mic.eq_preset[4];
						HostCommandSend(UNIT_TO_HOST_MIC_EQ_REQ, 0x00, 0x00, detail, 10);
						break;
					case 0x02://保存麦克风所有EQ值
						memcpy(mic.eq, mic.eq_preset, 5);
						break;
					default:
						break;
				}
				break;
			case HOST_TO_UNIT_RESET_PARM:
				mic.sen_preset = 4;// 0db
				mic.sen = mic.sen_preset;
				SetMicSen2WM8974(mic.sen_preset);

				memset(mic.eq_preset, 0x2C, 5);
				memcpy(mic.eq, mic.eq_preset, 5);
				Wm8974SetEQValue(0, mic.eq_preset[0]);
				Wm8974SetEQValue(1, mic.eq_preset[1]);
				Wm8974SetEQValue(2, mic.eq_preset[2]);
				Wm8974SetEQValue(3, mic.eq_preset[3]);
				Wm8974SetEQValue(4, mic.eq_preset[4]);
				break;
			case HOST_TO_UNIT_MIC_SEN://回复PC声控关闭时间和灵敏度20200518
				detail[0] = (mic.v_sen-130)/2;
				if(info.master_unit == FALSE)
				{
					detail[1] = mic.nos_tmr/100;
				}
				else
				{
					detail[1] = 0;
				}
				HostCommandSend(UNIT_TO_HOST_MIC_SEN, 0x00, 0x00, detail, 2);		
				break;
			
			default:
				break;
		}
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/* WIFI Host COMMAND DEFINE END                                                                            */
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/* WIFI_CORE COMMAND DEFINE                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void WifiCoreCommandSend(u8 cmd, u8 *data, u8 len)
{
	u8 head[4];
	u8 tail;

	head[0] = 0x5A;
	head[1] = 0xA5;
	head[2] = len + 1;
	head[3] = cmd;
	tail    = 0xFC;
	
	WifiCoreWriteByte(head, 4);

	if(data != NULL)
	{
		delay_ms(1);
		WifiCoreWriteByte(data, len);
	}

	WifiCoreWriteByte(&tail, 1);
}

static const u8 rssi_conv_list[5][2] =
{
	/*{100,  75},
	{80,   65},
	{70,   55},
	{60,   45},
	{50,   0},*/
	{100,  65},
	{70,   55},
	{60,   45},
	{50,   35},
	{40,   0},
};

u16 WifiCoreRecvPolling(void)
{
	u16  type;
	u8  *eff_data;
	u8   eff_data_len;
	u8	 dec[30];
	u8   u8_temp = 0;
	
	if(wifi_core_recv.r_p != wifi_core_recv.w_p)
	{
		type         = wifi_core_recv.q[wifi_core_recv.r_p].data[0];
		eff_data     = wifi_core_recv.q[wifi_core_recv.r_p].data + 1;
		eff_data_len = wifi_core_recv.q[wifi_core_recv.r_p].len  - 1;

		switch(type)
		{
			case WIFI_CORE_TO_MCU_POWER_ON:
				HostCommandSendEnterSystem(TRUE);
				wifi.connect 		= TRUE;
				wifi.rssi	 		= 4;
				if(info.wifi_core_startup < WIFI_CORE_STARTUP_FINISH)
					info.wifi_core_startup	= WIFI_CORE_STARTUP_WAIT_HOST;
				else
					info.wifi_core_startup	= WIFI_CORE_STARTUP_HOST_DISCONNECT;
				info.overcount 		= 0;
				break;
			case WIFI_CORE_TO_MCU_VER:
				memcpy(info.ver + WIFI_CORE_VER_SHIFT, eff_data, 3);
				break;
			case WIFI_CORE_TO_MCU_RSSI:		
				u8_temp = wifi.rssi;	
				while(eff_data[0] <= rssi_conv_list[u8_temp][1] && u8_temp < 4)u8_temp++;
				while(eff_data[0] >  rssi_conv_list[u8_temp][0] && u8_temp > 0)u8_temp--;
				if(wifi.rssi != u8_temp)
				{
					wifi.rssi = u8_temp;
					if(wifi.rssi == 0)
					{
						HostDisconnectDo();
						IMAGE_RSSI_TOO_LOW_DISPLAY();
						HostCommandSendEnterSystem(FALSE);

						//test rssi over
						//sprintf(dec, "rssi over:%02d    ", eff_data[0]);
						//OLEDDMAShowStr(dec, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);
						//OLEDDMAUpdateImmediately();
						//while(1);
					}
					else
					{
						u8_temp = (u8_temp > 1) ? FALSE : TRUE;
						if(u8_temp != wifi.low)
						{
							wifi.low = u8_temp;
							if(info.host_connect)
								HostCommandSend(UNIT_TO_HOST_STATE_TOO_LOW, info.battery, wifi.rssi, NULL, 0);
						}
					}
					
					if(info.wifi_core_startup > WIFI_CORE_STARTUP_WAIT_HOST)
					{
						if(wifi.rssi > 1)
						{
							OLEDDMAShowPic(image_rssi_value[4], 
								IMAGE_RSSI_VALUE_WEIGH, IMAGE_RSSI_VALUE_HIGH, IMAGE_RSSI_VALUE_COL, IMAGE_RSSI_VALUE_PAGE);
						}
						else
						{
							OLEDDMAShowPic(image_rssi_value[wifi.rssi], 
								IMAGE_RSSI_VALUE_WEIGH, IMAGE_RSSI_VALUE_HIGH, IMAGE_RSSI_VALUE_COL, IMAGE_RSSI_VALUE_PAGE);
						}
					}

				}
				break;
			case WIFI_CORE_TO_MCU_WIFI_DISCONNECT:
				wifi.connect = FALSE;
				wifi.rssi	 = 0;
				HostDisconnectDo();
				DisplayAPLose();
				break;
			case WIFI_CORE_TO_MCU_WIFI_RECONNECT:
				wifi.connect = TRUE;
				wifi.rssi	 = 4;
				info.host_lost_count = 0;
				break;
			case WIFI_CORE_TO_MCU_SSID:
				info.wifi_core_startup = WIFI_CORE_STARTUP_WAIT_AP;
				wifi.wpa.ssid_len = eff_data_len;
		
				memcpy(wifi.wpa.ssid, eff_data, eff_data_len);
				
				dec[0] = setid.local >> 8;
				dec[1] = setid.local;
				WifiCoreCommandSend(MCU_TO_WIFI_CORE_ID, dec, 2);
				break;
			case WIFI_CORE_TO_MCU_MAC:
				memcpy(wifi.mac, eff_data, eff_data_len);
				break;
			case HOST_TO_MCU_COMMAND:
				if(wifi.rssi > 0)
				{
					HostRecvCheck(eff_data, eff_data_len);
					info.host_lost_count = 0;
				}
				break;
			default:
				
				break;
		}
		
		wifi_core_recv.r_p = (wifi_core_recv.r_p + 1) & (WIFI_CORE_RECV_QUEUE_LEN - 1);

		return type;
	}
	
	return WIFI_CORE_TO_MCU_NO_COMMAND;
}
/*---------------------------------------------------------------------------------------------------------*/
/* WIFI_CORE COMMAND DEFINE END                                                                            */
/*---------------------------------------------------------------------------------------------------------*/




