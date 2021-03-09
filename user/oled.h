#ifndef __LCD_H_
#define __LCD_H_

#define OLED_8_16_4_COL0	0
#define OLED_8_16_4_COL1	8
#define OLED_8_16_4_COL2	16
#define OLED_8_16_4_COL3	24
#define OLED_8_16_4_COL4	32
#define OLED_8_16_4_COL5	40
#define OLED_8_16_4_COL6	48
#define OLED_8_16_4_COL7	56
#define OLED_8_16_4_COL8	64
#define OLED_8_16_4_COL9	72
#define OLED_8_16_4_COL10	80
#define OLED_8_16_4_COL11	88
#define OLED_8_16_4_COL12	96
#define OLED_8_16_4_COL13	104
#define OLED_8_16_4_COL14	112
#define OLED_8_16_4_COL15	120

#define OLED_8_16_4_PAGE0	0
#define OLED_8_16_4_PAGE1	2
#define OLED_8_16_4_PAGE2	4
#define OLED_8_16_4_PAGE3	6
#define OLED_8_16_4_PAGEM	3

void OLEDCPUSendOn(void);
void OLEDCPUSendOff(void);
void OLEDSpiInit(void);

void OLEDDMAFill(u8 w, u8 h, u8 col, u8 page);
void OLEDDMAShowPic(uc8 *pic, u8 w, u8 h, u8 col, u8 page);
void OLEDDMAClearPic(void);
void OLEDDMAShowChar(u8 ch, u8 x, u8 y);
void OLEDDMAShowStr(uc8 *str, u8 x, u8 y);
void OLEDDMAShowNum(u32 num, u8 x, u8 y);
void OLEDDMAShowNumFill(u32 num, u8 len, u8 col, u8 page);

void OLEDDMAPolling(void);
void OLEDDMAUpdateImmediately(void);
void OLEDDMAUpdate(void);

void OLEDNegation(void);
#endif

/********************************END_FILE******************************/



