#ifndef __WM8974_H_
#define __WM8974_H_


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



#endif

