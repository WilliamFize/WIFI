#include "types.h"

int strcmp_fixName(u8 * pBtnName, const char * fixName)
{
	u8 *pBtn = pBtnName;
	const char *fix = fixName;
	
	while(*fix != '\0')
	{
		if(*pBtn != *fix)
			return -1;
		pBtn++;
		fix++;
	}
	return 0;
}

void StringMac2ByteHex(u8* stringhex, u8* bytehex, u8 len)
{
	u8 i, j;
	u8 temp = 0x00;

	for(i = 0, j = 0; i < len; i++)
	{
		if(stringhex[i] == ':')
		{
			bytehex[j] = temp;
			temp = 0x00;
			j++;
		}
		else
		{
			temp <<= 4;
			if(stringhex[i] >= '0' && stringhex[i] <= '9')
				temp  |= stringhex[i] - '0';
			else if(stringhex[i] >= 'a' && stringhex[i] <= 'f')
				temp  |= stringhex[i] - 'a' + 10;
			else
				temp  |= stringhex[i] - 'A' + 10;
		}
	}
	bytehex[j] = temp;
}

void StringIp2ByteHex(u8* stringip, u8* bytehex, u8 len)
{
	u8 i, j;
	u8 temp = 0x00;
	
	for(i = 0, j = 0; i < len; i++)
	{
		if(stringip[i] == '.')
		{
			bytehex[j] = temp;
			temp = 0x00;
			j++;
		}
		else if(stringip[i] >= '0' && stringip[i] <= '9')
		{
			temp  *= 10;
			temp  += stringip[i] - '0';
		}
	}
	bytehex[j] = temp;
}

void GetComipleDate_to_ver(u8 *dst)
{
	const char month_list[12][4] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	u8 compile_date[20];
	
	u8 year_str[5];
	u8 month_str[4];
	u8 day, day_str[3];
	
	u8 i;

	sprintf(compile_date, "%s", __DATE__);
	sscanf(compile_date, "%s %d %s", month_str, &day, year_str);

	for(i = 0; i < 12; i++)
	{
		if(strcmp_fixName(month_str, month_list[i]) == 0)
		{
			month_str[0] = (i + 1) / 10 + '0';
			month_str[1] = (i + 1) % 10 + '0';
			month_str[2] = '\0';
			break;
		}
	}

	day_str[0] = (day / 10) + '0';
	day_str[1] = (day % 10) + '0';
	day_str[2] = '\0';

	memcpy(dst, year_str, 4);
	memcpy(dst + 4, month_str, 2);
	memcpy(dst + 6, day_str, 2);
	dst[8] = '\0';

}

u32 U8_4_Change_U32(u8 *U8_4)
{
	u32 U32;
	U32 = (u32)U8_4[0]<<24 | (u32)U8_4[1]<<16 | (u32)U8_4[2]<<8 | (u32)U8_4[3];
	return U32;
}

void U32_Change_U8_4(u32 U32, u8 *U8_4)
{
	U8_4[0] = U32 >> 24;
	U8_4[1] = U32 >> 16;
	U8_4[2] = U32 >> 8;
	U8_4[3] = U32;
}

//m^n函数
//返回值:m^n次方.
u32 M_Pow_N(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}



