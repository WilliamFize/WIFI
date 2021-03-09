#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
/* USBD DEFINE                                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
void USBD_IRQHandler(void)
{
    u32 u32IntSts = USBD_GET_INT_FLAG();
    u32 u32State = USBD_GET_BUS_STATE();

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_FLDET)
    {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_FLDET);

        if(USBD_IS_ATTACHED())
        {
            /* USB Plug In */
            USBD_ENABLE_USB();
        }
        else
        {
            /* USB Un-plug */
            USBD_DISABLE_USB();
        }
    }

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_BUS)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_BUS);

        if(u32State & USBD_STATE_USBRST)
        {
            /* Bus reset */
            USBD_ENABLE_USB();
            USBD_SwReset();
        }
        if(u32State & USBD_STATE_SUSPEND)
        {
            /* Enable USB but disable PHY */
            USBD_DISABLE_PHY();
        }
        if(u32State & USBD_STATE_RESUME)
        {
            /* Enable USB and enable PHY */
            USBD_ENABLE_USB();
        }
    }

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_USB)
    {
        // USB event
        if(u32IntSts & USBD_INTSTS_SETUP)
        {
            // Setup packet
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_SETUP);

            /* Clear the data IN/OUT ready flag of control end-points */
            USBD_STOP_TRANSACTION(EP0);
            USBD_STOP_TRANSACTION(EP1);

            USBD_ProcessSetupPacket();
        }

        // EP events
        if(u32IntSts & USBD_INTSTS_EP0)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP0);
            // control IN
            USBD_CtrlIn();
        }

        if(u32IntSts & USBD_INTSTS_EP1)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP1);

            // control OUT
            USBD_CtrlOut();
        }

        if(u32IntSts & USBD_INTSTS_EP2)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);
            // Interrupt IN
        }

        if(u32IntSts & USBD_INTSTS_EP3)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP3);
            // Interrupt OUT
            EP3_Handler();
        }

        if(u32IntSts & USBD_INTSTS_EP4)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP4);
        }

        if(u32IntSts & USBD_INTSTS_EP5)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP5);
        }

        if(u32IntSts & USBD_INTSTS_EP6)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP6);
        }

        if(u32IntSts & USBD_INTSTS_EP7)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP7);
        }
    }
}

void HID_ClassRequest(void)
{
    u8 buf[8];

    USBD_GetSetupPacket(buf);

    if(buf[0] & 0x80)    /* request data transfer direction */
    {
        // Device to host
        switch(buf[1])
        {
            case GET_REPORT:
//             {
//                 break;
//             }
            case GET_IDLE:
//             {
//                 break;
//             }
            case GET_PROTOCOL:
//            {
//                break;
//            }
            default:
            {
                /* Setup error, stall the device */
                USBD_SetStall(0);
                break;
            }
        }
    }
    else
    {
        // Host to device
        switch(buf[1])
        {
            case SET_REPORT:
            {
                if(buf[3] == 3)
                {
                    /* Request Type = Feature */
                    USBD_SET_DATA1(EP1);
                    USBD_SET_PAYLOAD_LEN(EP1, 0);
                }
                break;
            }
            case SET_IDLE:
            {
                /* Status stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0);
                break;
            }
            case SET_PROTOCOL:
//             {
//                 break;
//             }
            default:
            {
                // Stall
                /* Setup error, stall the device */
                USBD_SetStall(0);
                break;
            }
        }
    }
}

void HID_Init(void)
{
	SYS_UnlockReg();
	CLK_EnableModuleClock(USBD_MODULE);
    CLK_SetModuleClock(USBD_MODULE, 0, CLK_CLKDIV_USB(3));
	USBD_Open(&gsInfo, HID_ClassRequest, NULL);
	
	/*****************************************************/
	/* Init setup packet buffer */
    /* Buffer range for setup packet -> [0 ~ 0x7] */
    USBD->STBUFSEG = SETUP_BUF_BASE;

    /*****************************************************/
    /* EP0 ==> control IN endpoint, address 0 */
    USBD_CONFIG_EP(EP0, USBD_CFG_CSTALL | USBD_CFG_EPMODE_IN | 0);
    /* Buffer range for EP0 */
    USBD_SET_EP_BUF_ADDR(EP0, EP0_BUF_BASE);

    /* EP1 ==> control OUT endpoint, address 0 */
    USBD_CONFIG_EP(EP1, USBD_CFG_CSTALL | USBD_CFG_EPMODE_OUT | 0);
    /* Buffer range for EP1 */
    USBD_SET_EP_BUF_ADDR(EP1, EP1_BUF_BASE);

    /*****************************************************/
    /* EP2 ==> Interrupt IN endpoint, address 1 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_IN | INT_IN_EP_NUM);
    /* Buffer range for EP2 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /* EP3 ==> Interrupt OUT endpoint, address 2 */
    USBD_CONFIG_EP(EP3, USBD_CFG_EPMODE_OUT | INT_OUT_EP_NUM);
    /* Buffer range for EP3 */
    USBD_SET_EP_BUF_ADDR(EP3, EP3_BUF_BASE);
    /* trigger to receive OUT data */
    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);

	/*****************************************************/
	USBD_Start();
	NVIC_EnableIRQ(USBD_IRQn);
	SYS_LockReg();
}
/*---------------------------------------------------------------------------------------------------------*/
/* USBD DEFINE END                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
/* WPA2-PSK FUNTION DEFINE                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define USB_RECV_QUEUE_LEN	8	

struct
{
	u8 data[USB_RECV_QUEUE_LEN][EP3_MAX_PKT_SIZE];
	volatile u8 w_p;
	volatile u8 r_p;
}usb_recv;

void EP3_Handler(void)  /* Interrupt OUT handler */
{
    u8 *ptr;
    ptr = (u8 *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP3));
	USBD_MemCopy(usb_recv.data[usb_recv.w_p], ptr, EP3_MAX_PKT_SIZE);
	USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
	usb_recv.w_p = (usb_recv.w_p + 1) & (USB_RECV_QUEUE_LEN - 1);
}

u8 UsbStringCompare(u8 *buf, WPA2_PSK_T *wpa)
{	
	if(*buf++ != 0xAA)
		return FALSE;
	if(*buf++ != 0xEE)
		return FALSE;

	wpa->ssid_len = *buf++;

	if(wpa->ssid_len == 0)
		return FALSE;
	
	memcpy(wpa->ssid, buf, wpa->ssid_len);

	buf = buf + wpa->ssid_len;

	if(*buf++ != 0xAA)
		return FALSE;
	if(*buf++ != 0xEE)
		return FALSE;

	wpa->key_len = *buf++;

	if(wpa->key_len == 0)
		return FALSE;

	memcpy(wpa->key, buf, wpa->key_len);
		
	return TRUE;
}

const u8 sucess_string[EP2_MAX_PKT_SIZE] = "Receive ok\n";
const u8 fail_string[EP2_MAX_PKT_SIZE]   = "Input error\n";

void UsbRecvPolling(void)
{
	u8 *ptr;
	WPA2_PSK_T	wpa; 
		
	if(usb_recv.r_p != usb_recv.w_p)
	{
		ptr = usb_recv.data[usb_recv.r_p];
		if(UsbStringCompare(ptr, &wpa) == TRUE)
		{
			memcpy(&wifi.wpa, &wpa, sizeof(WPA2_PSK_T));
			ptr = (u8 *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2));
			USBD_MemCopy(ptr, (u8 *)sucess_string, EP2_MAX_PKT_SIZE);
			USBD_SET_PAYLOAD_LEN(EP2, EP2_MAX_PKT_SIZE);
			OLEDDMAClearPic();
			IMAGE_SSID_SET_OK_DISPLAY();
			OLEDDMAUpdateImmediately();
			WifiCoreCommandSend(MCU_TO_WIFI_CORE_SET_SSID, wifi.wpa.ssid, wifi.wpa.ssid_len);
			delay_ms(100);
			WifiCoreCommandSend(MCU_TO_WIFI_CORE_SET_WPA_KEY, wifi.wpa.key, wifi.wpa.key_len);
			delay_ms(2000);
			SystemPowerDown();
		}
		else
		{
			ptr = (u8 *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2));
			USBD_MemCopy(ptr, (u8 *)fail_string, EP2_MAX_PKT_SIZE);
			USBD_SET_PAYLOAD_LEN(EP2, EP2_MAX_PKT_SIZE);
		}
		usb_recv.r_p = (usb_recv.r_p + 1) & (USB_RECV_QUEUE_LEN - 1);
	}
}

#define PC_TO_UNIT_GET_UID		0x00
#define PC_TO_UNIT_SEND_SKEY	0x01
#define UNIT_TO_PC_SEND_UID		0x02

void UsbRecvUidAes(void)
{
	u8 name[16] = "~!@#$%^&*(";
	u8 key[16]  = ")_+{}123YU";
	u8 skey[176];
	u8 cmd[EP2_MAX_PKT_SIZE] = {0xAA, 0xEE};
	u8 i;
	u8 *ptr;
	
	memcpy(name + 10, info.mcu_uid, 6);
	memcpy(key + 10, info.mcu_uid + 6, 6);
	
	ScheduleKey(key, skey, 4, 10);
	AesEncrypt(name, skey, 10);
	
	for(i = 0; i < 16; i++)
	{
		if(name[i] != info.uid_key[i])
			break;
	}

	if(i != 16)
	{
		IMAGE_PLEASE_CRACK_DISPLAY();
		OLEDDMAUpdateImmediately();
		while(1)
		{
			if(usb_recv.r_p != usb_recv.w_p)
			{
				ptr = usb_recv.data[usb_recv.r_p];
				if(ptr[0] == 0xAA && ptr[1] == 0xEE)
				{
					switch(ptr[3])
					{
						case PC_TO_UNIT_GET_UID:
							cmd[2] = 13;
							cmd[3] = UNIT_TO_PC_SEND_UID;
							memcpy(cmd + 4, info.mcu_uid, 12);
							ptr = (u8 *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2));
							USBD_MemCopy(ptr, cmd, EP2_MAX_PKT_SIZE);
							USBD_SET_PAYLOAD_LEN(EP2, EP2_MAX_PKT_SIZE);
							break;
						case PC_TO_UNIT_SEND_SKEY:
							memcpy(info.uid_key, &ptr[4], 16);
							
							for(i = 0; i < 16; i++)
							{
								if(name[i] != info.uid_key[i])
									break;
							}
							
							if(i == 16)
							{
								IMAGE_CRACK_SUCESS_DISPLAY();
								OLEDDMAUpdateImmediately();
								delay_ms(2000);
								SystemPowerDown();
							}
							break;
						default:
							break;
					}
				}
				usb_recv.r_p = (usb_recv.r_p + 1) & (USB_RECV_QUEUE_LEN - 1);
			}

			if(timer0_delay_1ms_count == 0)
			{
				WaitUsbAesUidKeyInputPolling();
				timer0_delay_1ms_count = TIMER0_DELAY_1MS;
			}
		}
	}
}
/*---------------------------------------------------------------------------------------------------------*/
/* WPA2-PSK FUNTION DEFINE END                                                                             */
/*---------------------------------------------------------------------------------------------------------*/





