#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
/* nuvoton adc define                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_SAMPLE_TIMES	6
typedef struct 
{
	u8  sample_count;
	u8  get_value_ok;
	u16 adc0_value[ADC_SAMPLE_TIMES];
	u16 adc1_value;
	u16 adc4_value;
	u16 adc5_value;
}Meet_unit_adc_T;

static Meet_unit_adc_T meet_unit_adc;

void AdcNopRuning(void)
{
	u8 i;
	for(i = 0; i < 50; i++)
	{
		ADC_START_CONV(ADC);
		while(ADC_IS_BUSY(ADC));
	}
	meet_unit_adc.get_value_ok = TRUE;
	meet_unit_adc.sample_count = 0;
}

void SystemAdcInit(void)
{
	SYS_UnlockReg();	

    CLK_EnableModuleClock(ADC_MODULE);

	CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL1_ADC_S_HIRC, CLK_CLKDIV_ADC(7));

	//GPIO_DISABLE_DIGITAL_PATH(PD, 0x3);//PD 0,1
	//GPIO_DISABLE_DIGITAL_PATH(PD, 0x13);//PD 0,1,4
	GPIO_DISABLE_DIGITAL_PATH(PD, 0x33);//PD 0,1,4,5

	//SYS->GPD_MFP &= ~(SYS_GPD_MFP_PD0_Msk | SYS_GPD_MFP_PD1_Msk);
    //SYS->GPD_MFP |= SYS_GPD_MFP_PD0_ADC0 | SYS_GPD_MFP_PD1_ADC1;
    //SYS->ALT_MFP1 &= ~(SYS_ALT_MFP1_PD0_Msk | SYS_ALT_MFP1_PD1_Msk);
    //SYS->ALT_MFP1 |= SYS_ALT_MFP1_PD0_ADC0 | SYS_ALT_MFP1_PD1_ADC1;

	//SYS->GPD_MFP  &= ~(SYS_GPD_MFP_PD0_Msk   | SYS_GPD_MFP_PD1_Msk   | SYS_GPD_MFP_PD4_Msk);
    //SYS->GPD_MFP  |=   SYS_GPD_MFP_PD0_ADC0  | SYS_GPD_MFP_PD1_ADC1  | SYS_GPD_MFP_PD4_ADC4;
    //SYS->ALT_MFP1 &= ~(SYS_ALT_MFP1_PD0_Msk  | SYS_ALT_MFP1_PD1_Msk  | SYS_ALT_MFP1_PD4_Msk);
    //SYS->ALT_MFP1 |=   SYS_ALT_MFP1_PD0_ADC0 | SYS_ALT_MFP1_PD1_ADC1 | SYS_ALT_MFP1_PD4_ADC4;

	SYS->GPD_MFP  &= ~(SYS_GPD_MFP_PD0_Msk   | SYS_GPD_MFP_PD1_Msk   | SYS_GPD_MFP_PD4_Msk   | SYS_GPD_MFP_PD5_Msk);
    SYS->GPD_MFP  |=   SYS_GPD_MFP_PD0_ADC0  | SYS_GPD_MFP_PD1_ADC1  | SYS_GPD_MFP_PD4_ADC4  | SYS_GPD_MFP_PD5_ADC5;
    SYS->ALT_MFP1 &= ~(SYS_ALT_MFP1_PD0_Msk  | SYS_ALT_MFP1_PD1_Msk  | SYS_ALT_MFP1_PD4_Msk  | SYS_ALT_MFP1_PD5_Msk);
    SYS->ALT_MFP1 |=   SYS_ALT_MFP1_PD0_ADC0 | SYS_ALT_MFP1_PD1_ADC1 | SYS_ALT_MFP1_PD4_ADC4 | SYS_ALT_MFP1_PD5_ADC5;

	SYS_LockReg();

	ADC->ADCR    = (ADC->ADCR & (~ADC_ADCR_ADMD_Msk)) | ADC_ADCR_ADMD_SINGLE_CYCLE;//Single cycle scan mode
	ADC->ADCR   |= ADC_ADCR_ADIE_Msk | ADC_ADCR_ADEN_Msk;//ADIE, ADEN
	//ADC->ADCHER |= 0x03;//channel 0,1
	//ADC->ADCHER |= 0x13;//channel 0,1,4
	ADC->ADCHER |= 0x33;//channel 0,1,4,5

	ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);
	
	NVIC_EnableIRQ(ADC_IRQn);

	AdcNopRuning();
}

void ADC_IRQHandler(void)
{
	meet_unit_adc.adc0_value[meet_unit_adc.sample_count] = ADC_GET_CONVERSION_DATA(ADC, 0);
	meet_unit_adc.adc1_value = ADC_GET_CONVERSION_DATA(ADC, 1);
	meet_unit_adc.adc4_value = ADC_GET_CONVERSION_DATA(ADC, 4);
	meet_unit_adc.adc5_value = ADC_GET_CONVERSION_DATA(ADC, 5);
	if(meet_unit_adc.sample_count < ADC_SAMPLE_TIMES)
		meet_unit_adc.sample_count++;
	meet_unit_adc.get_value_ok = TRUE;
	ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);
}

/*---------------------------------------------------------------------------------------------------------*/
/* nuvoton adc end                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/*AdcBubbleSort funtion define                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
u16 AdcBubbleSort(u16 *dat, u8 len)
{
	u16 temp;
	u8 i,j; 

	for(i = 0; i < len - 1; i++)
	for(j = 0; j < len - 1 - i; j++)
	if(dat[j] > dat[j + 1])
	{
		temp = dat[j];
		dat[j] = dat [j + 1];
		dat[j + 1] = temp;
	}

	return dat[len >> 1];
}
/*---------------------------------------------------------------------------------------------------------*/
/*AdcBubbleSort funtion end                                                                                */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/*BATTERY funtion define                                                                                   */
/*3.3V -> 0x15A~0x167																					   */
/*4.2V -> 0x1DC~0x1EB																					   */
/*---------------------------------------------------------------------------------------------------------*/
#define BATTERY_LEVEL_COUNT	5
#define BATTERY_LEVEL_SHAKE	0x000A

static const u16 battery_rank_list[BATTERY_LEVEL_COUNT][2] = 
{
	{0x0000,                       0x01D3},
	{0x01DA - BATTERY_LEVEL_SHAKE, 0x0207 + BATTERY_LEVEL_SHAKE},
	{0x0207 - BATTERY_LEVEL_SHAKE, 0x0234 + BATTERY_LEVEL_SHAKE},
	{0x0234 - BATTERY_LEVEL_SHAKE, 0x0262 + BATTERY_LEVEL_SHAKE},
	{0x0262 - BATTERY_LEVEL_SHAKE, 0xFFFF}
};

void Battery_conver(u16 level, u8 *grid)
{
	if(level <= battery_rank_list[*grid][0])
	{
		(*grid)--;
	}
	else
	{
		while(level >= battery_rank_list[*grid][1])
		{
			(*grid)++;
		}
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/*BATTERY funtion end                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/*SystemAdcRecvCheck define                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
//#define BATTERY_TEST
#define MIC_OPEN_LEVEL				0x02F3
#define MIC_OPEN_RECHECK_TIMER		150//1.5s
#define WM8974_ERROR_LEVEL			0x03EA
#define WM8974_ERROR_RECHECK_TIMER	100 //1s
#define USB_OUT_LEVEL				0x140//0x03D8// before 0x03F0


#ifdef BATTERY_TEST
typedef struct
{
	u16 max;
	u16 min;
	u16 level[5];
}BATTERY_TEST_T;
BATTERY_TEST_T battery_test =
{
	.max = 0x00,
	.min = 0xffff,
};

void Display_BAT_MAX_MIN(void)
{
	u8 dec[32];

	sprintf(dec, "MAX:0x%04X      ", battery_test.max);
	OLEDDMAShowStr(dec, OLED_8_16_4_COL0, OLED_8_16_4_PAGE1);
	sprintf(dec, "MIN:0x%04X      ", battery_test.min);
	OLEDDMAShowStr(dec, OLED_8_16_4_COL0, OLED_8_16_4_PAGE2);
	sprintf(dec, "CHA:0x%04X      ", meet_unit_adc.adc5_value);
	OLEDDMAShowStr(dec, OLED_8_16_4_COL0, OLED_8_16_4_PAGE3);
}
#endif

void VoiceModeNoSignalResetTimer(void)
{
	mic.nos_cnt = mic.nos_tmr;
}



void SystemReadAdcPolling(void)
{
	static u16 wm8974_recheck_count = 0;
	static u16 mic_recheck_count = 0;
	static u8  ui_update;
	u16 level;
	u8  usb_state;
	u8  u8_temp; 

	if(meet_unit_adc.sample_count == ADC_SAMPLE_TIMES)
	{
		meet_unit_adc.sample_count = 0;
		//check battery
		level = AdcBubbleSort(meet_unit_adc.adc0_value, ADC_SAMPLE_TIMES);
		
		#ifdef BATTERY_TEST
		if(battery_test.max < level)
			battery_test.max = level;
		if(battery_test.min > level)
			battery_test.min = level;
		#endif
		
		u8_temp = info.battery;
		Battery_conver(level, &u8_temp);

		usb_state = (meet_unit_adc.adc5_value >= USB_OUT_LEVEL) ? TRUE : FALSE;

		if(u8_temp != info.battery)
		{
			info.battery 	= u8_temp;

			if(info.wifi_core_startup > WIFI_CORE_STARTUP_WAIT_HOST)
			{
				OLEDDMAShowPic(image_bat_value[info.battery], 
					IMAGE_BAT_VALUE_WEIGH, IMAGE_BAT_VALUE_HIGH, IMAGE_BAT_VALUE_COL, IMAGE_BAT_VALUE_PAGE);
			}
			
			u8_temp = (u8_temp > 1) ? FALSE : TRUE;
			if(u8_temp != info.battery_low)
			{
				info.battery_low = u8_temp;
				if(info.host_connect)
					HostCommandSend(UNIT_TO_HOST_STATE_TOO_LOW, info.battery, wifi.rssi, NULL, 0);
			}
		}

		if(usb_state != info.usb_state)
		{	
			if(info.wifi_core_startup > WIFI_CORE_STARTUP_WAIT_HOST)
			{
				info.usb_state = usb_state;
				if(info.usb_state)
				{
					OLEDDMAShowPic(image_bat_charge, 
						IMAGE_BAT_CHARGE_WEIGH, IMAGE_BAT_CHARGE_HIGH, IMAGE_BAT_CHARGE_COL, IMAGE_BAT_CHARGE_PAGE);
				}
				else
				{
					OLEDDMAFill(IMAGE_BAT_CHARGE_WEIGH, IMAGE_BAT_CHARGE_HIGH, IMAGE_BAT_CHARGE_COL, IMAGE_BAT_CHARGE_PAGE);
				}
			}
		}

		#ifdef BATTERY_TEST
		if(battery_test.level[info.battery] < 0xFFFF)
			battery_test.level[info.battery]++;
		#else
		if(info.battery == 0)
		{
			IMAGE_BAT_TOO_LOW_DISPLAY();
			OLEDDMAUpdateImmediately();
			delay_ms(2000);
			SystemPowerDown();
		}
		#endif
	}
	
	if(meet_unit_adc.get_value_ok == TRUE)
	{
		//check mic
		if(mic_recheck_count)
			mic_recheck_count--;
		if(mic.use && mic.mode == MIC_MODE_VOICE)
		{
			if(meet_unit_adc.adc1_value >= mic.v_sen)
			{
				if(mic.status == MIC_STATUS_CLOSE && mic_recheck_count == 0)
				{
					HostCommandSend(UNIT_TO_HOST_APPLY_OPENMIC, info.master_unit, 0x00, NULL, 0x00);
					mic_recheck_count  = MIC_OPEN_RECHECK_TIMER;
				}
				VoiceModeNoSignalResetTimer();
			}
			else
			{
				if(mic.nos_tmr != 0 && mic.status == MIC_STATUS_OPEN)
				{
					if(mic.nos_cnt)
						mic.nos_cnt--;
					else
					{
						HardwordCloseMic(TRUE, mic.led);
						if(popup.enable)
							IMAGE_MIC_CLOSE_DISPLAY();
					}	
				}
			}
		}

		//check wm8974 micbase
		if(wm8974_recheck_count)
			wm8974_recheck_count--;
		else if(meet_unit_adc.adc4_value >= WM8974_ERROR_LEVEL)
		{
			Wm8974RegisterInit();
			Wm8974SpecialParmInit();
			wm8974_recheck_count = WM8974_ERROR_RECHECK_TIMER;
		}
		
		meet_unit_adc.get_value_ok = FALSE;
		ADC_START_CONV(ADC);
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/*SystemAdcRecvCheck end                                                                                   */
/*---------------------------------------------------------------------------------------------------------*/



