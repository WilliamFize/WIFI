#ifndef __STRCONV_H__
#define __STRCONV_H__

int  strcmp_fixName(u8 * pBtnName, const char * fixName);
void StringMac2ByteHex(u8* stringhex, u8* bytehex, u8 len);
void StringIp2ByteHex(u8* stringip, u8* bytehex, u8 len);
void GetComipleDate_to_ver(u8 *dst);
u32  U8_4_Change_U32(u8 *U8_4);
void U32_Change_U8_4(u32 U32, u8 *U8_4);
u32  M_Pow_N(u8 m,u8 n);


#endif

