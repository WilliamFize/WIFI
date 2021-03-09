#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
/* KEY's BASE STRUCT DEFINE                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
typedef enum
{
	KEY_POWER_SW_VALUE,
	KEY_MIC_VALUE,
	KEY_VIP_VALUE,
	
	KEY_NULL_VALUE,
}KEY_VALUE_E;

#define KEY_INFO_COUNT	KEY_NULL_VALUE
#define KEY_MAX_COUNT	0xffff

typedef struct 
{
	const u8 			port;
	const u8			pin;
	const u8  			level;
	const KEY_VALUE_E	value;
}KEY_INFO_T;

static KEY_INFO_T key_info[] = 
{
	{GPIO_POWER_SW,		GPIO_POWER_SW_PIN,    	1,	KEY_POWER_SW_VALUE},
	{GPIO_KEY_MIC_KEY,	GPIO_KEY_MIC_KEY_PIN, 	0,	KEY_MIC_VALUE},
	{GPIO_KEY_VIP,		GPIO_KEY_VIP_PIN,		0,	KEY_VIP_VALUE},
};
/*---------------------------------------------------------------------------------------------------------*/
/* KEY's BASE STRUCT DEFINE END                                                                            */
/*---------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------*/
/* KEY's PARAMETER STRUCT DEFINE                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
typedef enum 
{
	KEY_STATE_NULL,
	KEY_STATE_PRESS,
	KEY_STATE_RELEASE,
}KEY_STATE_T;

typedef struct 
{
	
	u8  		value;
	u8			last_value;
	KEY_STATE_T state;
	u16			delay;
}KEY_PRESS_T;
static KEY_PRESS_T key_press = 
{
	.value = KEY_NULL_VALUE,
	.last_value = KEY_NULL_VALUE,
};
/*---------------------------------------------------------------------------------------------------------*/
/* KEY's PARAMETER STRUCT DEFINE END                                                                       */
/*---------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------*/
/* KEY's INPUT DEFINE                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
static void keyInputGet(void)
{
	static u8 last_value = KEY_NULL_VALUE;
	u8   value = KEY_NULL_VALUE;
	u8   i;

	for(i = 0; i < KEY_INFO_COUNT; i++)
	{
		if(info.master_unit)
		{
			if(GPIO_PIN_DATA(key_info[i].port, key_info[i].pin) == key_info[i].level)
			{
				value = key_info[i].value;
				break;
			}
		}
		else
		{
			if(GPIO_PIN_DATA(key_info[i].port, key_info[i].pin) == key_info[i].level)
			{
				value = key_info[i].value;
				if(value == KEY_VIP_VALUE) value = KEY_MIC_VALUE;
				break;
			}
		}
	}

	if(value != last_value) {
		if(value != KEY_NULL_VALUE && last_value == KEY_NULL_VALUE) {
			key_press.value = value;
			key_press.last_value = value;
			key_press.state = KEY_STATE_PRESS;
			key_press.delay = 0;
		}
		else {
			key_press.value = KEY_NULL_VALUE;
			key_press.state = KEY_STATE_RELEASE;
			key_press.delay = 0;
		}
		last_value = value;
	}
	else {
		if(key_press.delay < KEY_MAX_COUNT) key_press.delay++;
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/* KEY's INPUT DEFINE END                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* KEY's polling function                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void KeyInputPolling(void)
{
	keyInputGet();
	
	switch(key_press.state)
	{
		case KEY_STATE_PRESS:
			if(key_press.delay == 3000)
			{
				switch(key_press.value)
				{
					case KEY_POWER_SW_VALUE:
						SystemPowerDown();
						break;
					default:
						break;
				}
			}
			else if(key_press.delay == 30)
			{
//				timer0_1s_flag=0;
				switch(key_press.value)
				{
					case KEY_MIC_VALUE: 
						switch(info.unit_opration)
						{
							case UNIT_OPRATION_SETID_MODE:
								HostCommandSend(UNIT_TO_HOST_SETID, setid.current >> 8, setid.current, wifi.mac, 6);
								break;
							case UNIT_OPRATION_SIGN_MODE:
								if(sign.already == FALSE && sign.enable)
								{
									sign.already = TRUE;
									sign.already_total += 1;
									IMAGE_SIGN_NUM_DISPLAY();
									LedStaticControl(LED_CONTROL_ALREADY_SIGN);
									break;
								}
							default:
								if(mic.use)
								{
									if(mic.status == MIC_STATUS_CLOSE)
									{
										HostCommandSend(UNIT_TO_HOST_APPLY_OPENMIC, info.master_unit, 0x00, NULL, 0x00);
									}
									else
									{				
										HardwordCloseMic(TRUE, mic.led);
										if(popup.enable)
										{
											IMAGE_MIC_CLOSE_DISPLAY();
										}
									}
								}
								break;
						}
						break;
					case KEY_VIP_VALUE:
						if(info.master_unit && mic.use)
						{
							GPIO_DISPLAY_VIP_ON();
							HostCommandSend(UNIT_TO_HOST_VIP_KEY, 0x00, 0x00, NULL, 0);
						}
						break;
					case KEY_POWER_SW_VALUE:
						if(popup.enable)
						{
							if(popup.status != POPUP_SYS_INFO)
								DisplaySystemInfo();	
							else
								DisplayRestoreMeetingMode();
						}
						break;
				}
			}
			break;
		case KEY_STATE_RELEASE:
			if(key_press.delay == 30)
			{
				switch(key_press.last_value)
				{
					case KEY_VIP_VALUE:
						GPIO_DISPLAY_VIP_OFF();
						break;
					default:
						break;
				}
			}
			break;
		default:
			break;
	}
}

void WaitUsbAesUidKeyInputPolling(void)
{
	keyInputGet();
	
	if(key_press.value != KEY_NULL_VALUE)
	{
		if(key_press.state == KEY_STATE_PRESS)
		{
			if(key_press.delay == 3000)
			{
				if(key_press.value == KEY_POWER_SW_VALUE)
					SystemPowerDown();
			}
		}
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/* KEY's polling function END                                                                              */
/*---------------------------------------------------------------------------------------------------------*/



