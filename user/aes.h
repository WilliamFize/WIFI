#ifndef __AES_H__
#define __AES_H__

void AesEncrypt(unsigned char *blk,unsigned char *key,int Nr);
void Contrary_AesEncrypt(unsigned char *blk,unsigned char *key,int Nr);
void ScheduleKey(unsigned char *inkey, unsigned char *outkey,int Nk,int Nr);

#endif

