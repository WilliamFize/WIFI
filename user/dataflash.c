#include "types.h"

#define FMCDataFlashPageBaseAddress    		0x0001F000UL
#define FMCDataFlashPageMin            		0
#define FMCDataFlashPageMax            		7
#define PerDataSaveBytes             		4

#define FMCDataFlashPageNAddress(Number)    (FMCDataFlashPageBaseAddress+(Number)*FMC_FLASH_PAGE_SIZE)
#define FMCDataFlashDataNAddress(Number)    (FMCDataFlashPageBaseAddress+(Number)*PerDataSaveBytes)

#define DataNotUseFlag               		0xffffffffUL

#define MyDataflashSaveDataEndNumber    	1023
#define MyDataflashSaveDataBeginNumber  	0


u16 DataFlashWriteNumber = MyDataflashSaveDataBeginNumber; 
u16 DataFlashReadNumber  = MyDataflashSaveDataBeginNumber;

void DataFlashClean_NS(void)
{
	u8 i;
	for(i = FMCDataFlashPageMin; i <= FMCDataFlashPageMax; i++)
		FMC_Erase(FMCDataFlashPageNAddress(i));
}

void DataFlashFindDataNumber_NS(u16 DataCount)
{
	u16 HalfNumber;
	u16 BeginNumber;
	u16 EndNumber;
	
	BeginNumber = MyDataflashSaveDataBeginNumber;
	EndNumber   = MyDataflashSaveDataEndNumber;
	
	while(BeginNumber <= EndNumber)
	{
		HalfNumber = (BeginNumber + EndNumber) / 2;
		if(FMC_Read(FMCDataFlashDataNAddress(HalfNumber)) == DataNotUseFlag)
		{
			if(HalfNumber == BeginNumber)//以前未使用过dataflash 
			{
				DataFlashClean_NS();
				DataFlashWriteNumber = MyDataflashSaveDataBeginNumber;
				DataFlashReadNumber  = MyDataflashSaveDataBeginNumber;
				break;
			}
			else if(FMC_Read(FMCDataFlashDataNAddress(HalfNumber - 1)) != DataNotUseFlag)
			{
				if(HalfNumber < DataCount)
				{
					DataFlashClean_NS();
					DataFlashWriteNumber = MyDataflashSaveDataBeginNumber;
					DataFlashReadNumber  = MyDataflashSaveDataBeginNumber;
				}
				else
				{
					DataFlashReadNumber  = HalfNumber - DataCount;
					DataFlashWriteNumber = HalfNumber;
				}
				break;
			}
			else
				EndNumber = HalfNumber;
		}
		else
		{
			if(HalfNumber == EndNumber)//全部空间刚好用完
			{
				DataFlashReadNumber  = HalfNumber + 1 - DataCount;
				DataFlashWriteNumber = MyDataflashSaveDataEndNumber + 1;
				break;
			}
			else if(FMC_Read(FMCDataFlashDataNAddress(HalfNumber + 1)) == DataNotUseFlag)
			{
				if(HalfNumber + 1 < DataCount)
				{
					DataFlashClean_NS();
					DataFlashWriteNumber = MyDataflashSaveDataBeginNumber;
					DataFlashReadNumber  = MyDataflashSaveDataBeginNumber;
				}
				else
				{
					DataFlashReadNumber  = HalfNumber + 1 - DataCount;
					DataFlashWriteNumber = HalfNumber + 1;
				}
				break;
			}
			else
				BeginNumber = HalfNumber + 1;
		}
	}
}


void DataFlashRead_NS(u32 *SaveData,u16 DataCount)
{
	u16 Save_number;

	for(Save_number = 0; Save_number < DataCount; Save_number++)
	{
		SaveData[Save_number] = FMC_Read(FMCDataFlashDataNAddress(DataFlashReadNumber + Save_number));
	}
}

void DataFlashSave(u32 *SaveData,u16 DataCount)
{
	u16  Save_number;
	SYS_UnlockReg();
 	FMC_ENABLE_ISP();

	if(DataFlashWriteNumber + DataCount - 1 > MyDataflashSaveDataEndNumber)
	{
		DataFlashClean_NS();
		DataFlashReadNumber  = MyDataflashSaveDataBeginNumber;
		DataFlashWriteNumber = MyDataflashSaveDataBeginNumber;
	}

	for(Save_number = 0; Save_number < DataCount; Save_number++)
		FMC_Write(FMCDataFlashDataNAddress(Save_number + DataFlashWriteNumber), SaveData[Save_number]);

	DataFlashReadNumber  = DataFlashWriteNumber;
	DataFlashWriteNumber = DataFlashWriteNumber + DataCount;
	
	FMC_DISABLE_ISP();
    SYS_LockReg();
}

void DataFlashInit(u32 *SaveData,u16 DataCount)
{
	SYS_UnlockReg();
 	FMC_ENABLE_ISP();
	DataFlashFindDataNumber_NS(DataCount);
	DataFlashRead_NS(SaveData,DataCount);
	U32_Change_U8_4(FMC_ReadUID(0), info.mcu_uid);
	U32_Change_U8_4(FMC_ReadUID(1), info.mcu_uid + 4);
	U32_Change_U8_4(FMC_ReadUID(2), info.mcu_uid + 8);
	FMC_DISABLE_ISP();
    SYS_LockReg();
}

/********************************END_FILE**************************************/


