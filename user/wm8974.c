#include "types.h"

static void	WM8974_SDO(u8 Level);
static void	WM8974_SCK(u8 Level);
static void	WM8974_SDA_Mode(u8 Mode);
static u8	WM8974_SDI(void);

void Wm8974RegisterInit(void);
void Wm8974SetInpgaDbVolume(float n_db);
void Wm8974SetInpgaHexVolume(u8 data);
void Wm8974SetDacDbVolume(float n_db);
void Wm8974SetDacHexVolume(u8 data);
void Wm8974SetAdcDbVolume(float n_db);
void Wm8974SetSpkVolCtrl(u8 flag);
void Wm8974SetMonoVolCtrl(u8 flag);
void Wm8974SetEQValue(u8 band, u8 data);
void Wm8974SetFilter(u8 enable);



static void	WM8974_SDO(u8 Level)
{
	GPIO_WM8974_SDA_PO(Level);
}

static void	WM8974_SCK(u8 Level)
{
	GPIO_WM8974_SCL_PO(Level);
}

static void	WM8974_SDA_Mode(u8 Mode)
{
	if(Mode==IIC_IO_IN)
	{
		GPIO_WM8974_SDA_IN();
	}
	else
	{
		GPIO_WM8974_SDA_OUT();
	}
}

static u8	WM8974_SDI(void)
{
	return GPIO_WM8974_SDA_PI();
}

static T_I2C_Master_PIN_OPT WM8974_OPT_STRUCT=
{
	0x34,
	WM8974_SCK,
	WM8974_SDO,
	WM8974_SDI,
	WM8974_SDA_Mode,
};

// x = 2*(n_db) + 255, -127 <= n_db <= 0;
void Wm8974RegisterInit(void)
{
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x00,  0x055);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x38,  0x040);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x32,  0x000);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x01,  0x01D);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x02,  0x015);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x03,  0x0ED);

	//IIS
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x04,  0x010);

	//LEFT 
	//IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x04,  0x008);
	
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x05,  0x000);

	// FS = 24K, BCK = 768K
	//IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x06,  0x04D);
	//IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x07,  0x004);

	// FS = 48K, BCK = 1.5M
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x06,  0x00D);

	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0A,  0x008);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0B,  0x0FF);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0E,  0x108);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0F,  0x0FF);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x12,  0x02C);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x20,  0x020);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x21,  0x10F);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x22,  0x011);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x23,  0x009);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x2C,  0x003);
	//Wm8974SetInpgaDbVolume(12);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x2F,  0x000);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x31,  0x00A);
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x32,  0x001);
	Wm8974SetSpkVolCtrl(TRUE);
	Wm8974SetMonoVolCtrl(TRUE);
}

//only 0.25 or 0.00
void Wm8974SetInpgaDbVolume(float n_db)
{
	u8 data;
	data = (n_db + 12) / 0.75;
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x2D, data);
}

void Wm8974SetInpgaHexVolume(u8 data)
{
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x2D, data);
}

void Wm8974SetDacDbVolume(float n_db)
{
	u8 data;
	data = 2*(n_db) + 255;
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0B, data);
}

void Wm8974SetDacHexVolume(u8 data)
{
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0B, data);
}

void Wm8974SetAdcDbVolume(float n_db)
{
	u8 data;
	data = 2*(n_db) + 255;
	IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0F, data);
}

void Wm8974SetSpkVolCtrl(u8 flag)
{
	/*if(flag == TRUE)
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x36, 0x0B9);
	else
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x36, 0x0F9);*/
	if(flag == TRUE)
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x36, 0x0B9);
	else
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x36, 0x0F9);
}

void Wm8974SetMonoVolCtrl(u8 flag)
{
	if(flag == TRUE)
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x38, 0x001);
	else
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x38, 0x041);
}

void Wm8974SetFilter(u8 enable)
{
	if(enable) {
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0E, 0x188);
	}
	else {
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x0E, 0x108);
	}
}

void Wm8974SetEQValue(u8 band, u8 data)
{
	if(band < 5) {
		IIC_BUS_Write_7Bitadd_9Bitdata(&WM8974_OPT_STRUCT, 0x12 + band, data);
	}
}



