#line 1 "..\\user\\linux_command.c"
#line 1 "..\\user\\types.h"



 
 
 
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;  
typedef signed short const sc16;  
typedef signed char  const sc8;   

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;
 
typedef volatile signed long  const vsc32;  
typedef volatile signed short const vsc16;  
typedef volatile signed char  const vsc8;   

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;  
typedef unsigned short const uc16;  
typedef unsigned char  const uc8;   





typedef volatile unsigned long  const vuc32;  
typedef volatile unsigned short const vuc16;  
typedef volatile unsigned char  const vuc8;  


 
 
 


 
 
 

 
 
 


 
 
 
typedef enum
{
	BUTTON_3_VOTE_ONCE_SIGN,
	BUTTON_3_VOTE_ONCE_NOT_SIGN,
	BUTTON_3_VOTE_LAST_SIGN,
	BUTTON_3_VOTE_LAST_NOT_SIGN,
	BUTTON_5_OPTION_ONCE_SIGN,
	BUTTON_5_OPTION_ONCE_NOT_SIGN,
	BUTTON_5_OPTION_LAST_SIGN,
	BUTTON_5_OPTION_LAST_NOT_SIGN,
	BUTTON_5_LEVEL_ONCE_SIGN,
	BUTTON_5_LEVEL_ONCE_NOT_SIGN,
	BUTTON_5_LEVEL_LAST_SIGN,
	BUTTON_5_LEVEL_LAST_NOT_SIGN,
	BUTTON_2_USER_OPTION_ONCE_SIGN,
	BUTTON_2_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_2_USER_OPTION_LAST_SIGN,
	BUTTON_2_USER_OPTION_LAST_NOT_SIGN,
	BUTTON_3_USER_OPTION_ONCE_SIGN,
	BUTTON_3_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_3_USER_OPTION_LAST_SIGN,
	BUTTON_3_USER_OPTION_LAST_NOT_SIGN,
	BUTTON_4_USER_OPTION_ONCE_SIGN,
	BUTTON_4_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_4_USER_OPTION_LAST_SIGN,
	BUTTON_4_USER_OPTION_LAST_NOT_SIGN,
	BUTTON_5_USER_OPTION_ONCE_SIGN,
	BUTTON_5_USER_OPTION_ONCE_NOT_SIGN,
	BUTTON_5_USER_OPTION_LAST_SIGN,
	BUTTON_5_USER_OPTION_LAST_NOT_SIGN,
}VOTE_TYPE_E;

typedef struct
{
	u8			enable;
	u8			result;
	u8			name[5][20];
	VOTE_TYPE_E	type;
}VOTE_T;
extern VOTE_T vote;
 
 
 


 
 
 
typedef struct
{
	u8	press;
	u8	sucess;
	u8	already;
	u16	current;
	u16	local;
}SET_ID_T;
extern SET_ID_T setid;
 
 
 

 
 
 
typedef struct
{
	u8	already;
	u8	enable;
	u16	total;
	u16	already_total;
}SIGN_T;
extern SIGN_T sign;
 
 
 

 
 
 

typedef struct
{
	u8 	ssid[16];
	u8 	ssid_len;
	u8 	key[16];
	u8 	key_len;
}WPA2_PSK_T;

typedef struct
{
	u8			rssi;
	u8 			connect;
	u8			low;
	u8 			mac[6];
	WPA2_PSK_T	wpa;
}WIFI_T;
extern WIFI_T wifi;
 
 
 


 
 
 
typedef enum
{
	UNIT_OPRATION_MEETING_MODE,
	UNIT_OPRATION_SIGN_MODE,
	UNIT_OPRATION_VOTE_MODE,
	UNIT_OPRATION_SETID_MODE,
	
	UNIT_OPRATION_IDREPEAT_MODE,
	UNIT_OPRATION_VOTE_RESULT_MODE,
	UNIT_OPRATION_HOST_DISCONNECT_MODE,
}UNIT_OPRATION_E;

typedef enum
{
	DOWN_STATEMENT,
	UP_STATEMENT,
	NO_STATEMENT,
}TIME_STATEMENT_E;

typedef enum
{
	LINUX_STARTUP_WAIT_UART,
	LINUX_STARTUP_WAIT_AP,
	LINUX_STARTUP_WAIT_HOST,
	LINUX_STARTUP_FINISH,
	
	LINUX_STARTUP_UART_ERROR,
	LINUX_STARTUP_NET_CARD_ERROR,
	LINUX_STARTUP_AP_DISCONNECT,
}LINUX_STARTUP_E;

typedef enum
{
	TFT_DISPLAY_NORMAL,
	TFT_DISPLAY_MODE,
	TFT_DISPLAY_REP_APPLY,
}TFT_DISPLAY_E;

typedef struct
{
	u8					master_unit;
	u8					host_connect;
	u8					battery;
	u8					battery_low;
	u8					light;
	u8					linux_ver[8];
	u8					mcu_uid[12];
	u8					uid_key[16];
	u8					unit_name[16];
	u8					fire_warning;
	u8					auto_backlight;
	
	TFT_DISPLAY_E		tft_display;
	LINUX_STARTUP_E		linux_startup;
	UNIT_OPRATION_E		unit_opration;
	TIME_STATEMENT_E	time_statement;
	
	u16					host_lost_count;
	u16					overcount;
	u16					led_flash_count;
	
	u32					time_statement_count;
	u32					time_statement_max;
}INFO_T;
extern INFO_T info;

typedef enum
{
	LED_CONTROL_MIC_CLOSE,
	LED_CONTROL_MIC_OPEN,
	LED_CONTROL_MIC_WAIT,
	LED_CONTROL_MIC_APPLY,

	LED_CONTROL_ALREADY_SIGN,
	LED_CONTROL_ALREADY_SETID,
	LED_CONTROL_ALL_CLOSE
}LED_CONTROL_E;

void SystemPowerDown(void);
void LedStaticControl(LED_CONTROL_E ctrl);
void HostDisconnectDo(void);
 
 
 

 
 
 
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"


  



    typedef unsigned int size_t;    
#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"




extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 193 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 209 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 232 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 247 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 270 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 502 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"



 

#line 251 "..\\user\\types.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 985 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 252 "..\\user\\types.h"

 
 
 
#line 1 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
 









 


















 









 




 



 

typedef enum IRQn
{
     
    NonMaskableInt_IRQn         = -14,     
    HardFault_IRQn              = -13,     
    SVCall_IRQn                 = -5,      
    PendSV_IRQn                 = -2,      
    SysTick_IRQn                = -1,      

     
    BOD_IRQn                  = 0,         
    WDT_IRQn                  = 1,         
    EINT0_IRQn                = 2,         
    EINT1_IRQn                = 3,         
    GPAB_IRQn                 = 4,         
    GPCDF_IRQn                = 5,         
    PWMA_IRQn                 = 6,         
    TMR0_IRQn                 = 8,         
    TMR1_IRQn                 = 9,         
    TMR2_IRQn                 = 10,        
    TMR3_IRQn                 = 11,        
    UART0_IRQn                = 12,        
    UART1_IRQn                = 13,        
    SPI0_IRQn                 = 14,        
    SPI1_IRQn                 = 15,        
    SPI2_IRQn                 = 16,        
    I2C0_IRQn                 = 18,        
    I2C1_IRQn                 = 19,        
    CAN0_IRQn                 = 20,        
    CAN1_IRQn                 = 21,        
    USBD_IRQn                 = 23,        
    PS2_IRQn                  = 24,        
    PDMA_IRQn                 = 26,        
    I2S_IRQn                  = 27,        
    PWRWU_IRQn                = 28,        
    ADC_IRQn                  = 29,        
    IRC_IRQn                  = 30,        
} IRQn_Type;






 

 





   


#line 1 "..\\Library\\CMSIS\\Include\\core_cm0.h"
 




 

























 











#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 45 "..\\Library\\CMSIS\\Include\\core_cm0.h"

















 




 



 

 













#line 120 "..\\Library\\CMSIS\\Include\\core_cm0.h"



 







#line 162 "..\\Library\\CMSIS\\Include\\core_cm0.h"

#line 1 "..\\Library\\CMSIS\\Include\\core_cmInstr.h"
 




 

























 












 



 

 
#line 1 "..\\Library\\CMSIS\\Include\\cmsis_armcc.h"
 




 

























 










 



 

 
 





 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}






 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}






 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}






 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}






 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}






 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}






 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}






 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}






 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}






 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}






 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}


#line 263 "..\\Library\\CMSIS\\Include\\cmsis_armcc.h"


#line 297 "..\\Library\\CMSIS\\Include\\cmsis_armcc.h"



 


 



 




 






 







 






 








 










 










 











 








 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}







 

__attribute__((section(".revsh_text"))) static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}









 









 








 



__attribute__((always_inline)) static __inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;
  int32_t s = 4   * 8 - 1;  

  result = value;                       
  for (value >>= 1U; value; value >>= 1U)
  {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;                         
  return(result);
}








 



#line 649 "..\\Library\\CMSIS\\Include\\cmsis_armcc.h"

   


 



 

#line 731 "..\\Library\\CMSIS\\Include\\cmsis_armcc.h"
 


#line 54 "..\\Library\\CMSIS\\Include\\core_cmInstr.h"

 
#line 84 "..\\Library\\CMSIS\\Include\\core_cmInstr.h"

   

#line 164 "..\\Library\\CMSIS\\Include\\core_cm0.h"
#line 1 "..\\Library\\CMSIS\\Include\\core_cmFunc.h"
 




 

























 












 



 

 
#line 54 "..\\Library\\CMSIS\\Include\\core_cmFunc.h"

 
#line 84 "..\\Library\\CMSIS\\Include\\core_cmFunc.h"

 

#line 165 "..\\Library\\CMSIS\\Include\\core_cm0.h"
















 
#line 198 "..\\Library\\CMSIS\\Include\\core_cm0.h"

 






 
#line 214 "..\\Library\\CMSIS\\Include\\core_cm0.h"

 




 










 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:28;               
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:15;               
    uint32_t T:1;                         
    uint32_t _reserved1:3;                
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 





















 
typedef union
{
  struct
  {
    uint32_t _reserved0:1;                
    uint32_t SPSEL:1;                     
    uint32_t _reserved1:30;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 



 







 



 
typedef struct
{
  volatile uint32_t ISER[1U];                
        uint32_t RESERVED0[31U];
  volatile uint32_t ICER[1U];                
        uint32_t RSERVED1[31U];
  volatile uint32_t ISPR[1U];                
        uint32_t RESERVED2[31U];
  volatile uint32_t ICPR[1U];                
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  volatile uint32_t IP[8U];                  
}  NVIC_Type;

 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    
        uint32_t RESERVED0;
  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
        uint32_t RESERVED1;
  volatile uint32_t SHP[2U];                 
  volatile uint32_t SHCSR;                   
} SCB_Type;

 















 



























 















 









 






 



 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 








 
 







 






 







 


 







 

 










 









 


 



 





 

 
 









 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}






 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}








 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] & (1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}






 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}






 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}








 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) < 0)
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] = ((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
  else
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )]  = ((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )]  & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
}










 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) < 0)
  {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2)));
  }
  else
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2)));
  }
}





 
static __inline void NVIC_SystemReset(void)
{
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FAUL << 16U) |
                 (1UL << 2U));
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                           

  for(;;)                                                            
  {
    __nop();
  }
}

 



 





 













 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  NVIC_SetPriority (SysTick_IRQn, (1UL << 2) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 










#line 107 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\system_NUC123.h"
 









 






 
 
 






 






extern uint32_t SystemCoreClock;     
extern uint32_t CyclesPerUs;         
extern uint32_t PllClock;            









 
extern void SystemInit(void);










 
extern void SystemCoreClockUpdate(void);





#line 108 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"


#pragma anon_unions



 



 

 



 

typedef struct
{































































































































































 

    volatile const  uint32_t ADDR[8];        
    volatile uint32_t ADCR;           
    volatile uint32_t ADCHER;         
    volatile uint32_t ADCMPR[2];      
    volatile uint32_t ADSR;           
    volatile const  uint32_t RESERVE0[3];  
    volatile const  uint32_t ADPDMA;         

} ADC_T;





 

 









 
























 






 


















 





















 


   
   


 



 

typedef struct
{




































































































































































































































































































































































 

    volatile uint32_t PWRCON;         
    volatile uint32_t AHBCLK;         
    volatile uint32_t APBCLK;         
    volatile uint32_t CLKSTATUS;      
    volatile uint32_t CLKSEL0;        
    volatile uint32_t CLKSEL1;        
    volatile uint32_t CLKDIV;         
    volatile uint32_t CLKSEL2;        
    volatile uint32_t PLLCON;         
    volatile uint32_t FRQDIV;         
    volatile const  uint32_t RESERVE0;
    volatile uint32_t APBDIV;         

} CLK_T;





 

 




























 







 


























































 



















 






 




































 



















 












 





















 






 


   
   


 



 

typedef struct
{






















































































































































 

    volatile uint32_t CTL;            
    volatile uint32_t DMASAR;         
    volatile const  uint32_t RESERVED0; 
    volatile uint32_t DMABCR;         
    volatile const  uint32_t RESERVED1;    
    volatile const  uint32_t DMACSAR;        
    volatile const  uint32_t RESERVED2;    
    volatile const  uint32_t DMACBCR;        
    volatile uint32_t DMAIER;         
    volatile uint32_t DMAISR;         
    volatile const  uint32_t RESERVED3[22];
    volatile uint32_t WDATA;          
    volatile uint32_t SEED;           
    volatile const  uint32_t CHECKSUM;       

} CRC_T;





 

 



























 



 



 



 



 






 






 



 



 


   
   

 



 

typedef struct
{






















































































































 

    volatile uint32_t ISPCON;         
    volatile uint32_t ISPADR;         
    volatile uint32_t ISPDAT;         
    volatile uint32_t ISPCMD;         
    volatile uint32_t ISPTRG;         
    volatile const  uint32_t DFBADR;         
    volatile uint32_t FATCON;         
    volatile const  uint32_t RESERVED[9];  
    volatile uint32_t ISPSTA;         

} FMC_T;





 

 
























 



 



 









 



 



 

























   
   



 



 

typedef struct
{










































































































































































 

    volatile uint32_t PMD;            
    volatile uint32_t OFFD;           
    volatile uint32_t DOUT;           
    volatile uint32_t DMASK;          
    volatile const  uint32_t PIN;            
    volatile uint32_t DBEN;           
    volatile uint32_t IMD;            
    volatile uint32_t IEN;            
    volatile uint32_t ISRC;           

} GPIO_T;




typedef struct
{
































 

    volatile uint32_t DBNCECON;       

} GPIO_DBNCECON_T;





 

 
















































 



 



 



 



 



 



 






 



 








   
   

 



 

typedef struct
{



























































































































































































 

    volatile uint32_t I2CON;          
    volatile uint32_t I2CADDR0;       
    volatile uint32_t I2CDAT;         
    volatile const  uint32_t I2CSTATUS;      
    volatile uint32_t I2CLK;          
    volatile uint32_t I2CTOC;         
    volatile uint32_t I2CADDR1;       
    volatile uint32_t I2CADDR2;       
    volatile uint32_t I2CADDR3;       
    volatile uint32_t I2CADM0;        
    volatile uint32_t I2CADM1;        
    volatile uint32_t I2CADM2;        
    volatile uint32_t I2CADM3;        
    volatile const  uint32_t RESERVED[2];
	volatile uint32_t I2CWKUPCON;     
    volatile uint32_t I2CWKUPSTS;     

} I2C_T;





 

 


















 






 



 



 



 









 



 



 


   
   

 



 

typedef struct
{










































































































































































































































































 

    volatile uint32_t CON;            
    volatile uint32_t CLKDIV;         
    volatile uint32_t IE;             
    volatile uint32_t STATUS;         
    volatile  uint32_t TXFIFO;         
    volatile const  uint32_t RXFIFO;         

} I2S_T;





 

 

























































 






 

























 
























































   
   

 



 

typedef struct
{


































































































































 

    volatile uint32_t CSR;            
    volatile uint32_t SAR;            
    volatile uint32_t DAR;            
    volatile uint32_t BCR;            
    volatile const  uint32_t POINT;          
    volatile const  uint32_t CSAR;           
    volatile const  uint32_t CDAR;           
    volatile const  uint32_t CBCR;           
    volatile uint32_t IER;            
    volatile uint32_t ISR;            
    volatile const  uint32_t RESERVE[22];  
    volatile const  uint32_t SBUF;           

} PDMA_T;




typedef struct
{
















































































































































































 

    volatile uint32_t GCRCSR;         
    volatile uint32_t PDSSR0;         
    volatile uint32_t PDSSR1;         
    volatile uint32_t GCRISR;         
    volatile uint32_t PDSSR2;         

} PDMA_GCR_T;






 

 





















 



 



 



 






 






 





















 


















 















 
























 

















   
   


 



 

typedef struct
{




























































































































































 

    volatile uint32_t PS2CON;         
    volatile uint32_t PS2TXDATA0;     
    volatile uint32_t PS2TXDATA1;     
    volatile uint32_t PS2TXDATA2;     
    volatile uint32_t PS2TXDATA3;     
    volatile uint32_t PS2RXDATA;      
    volatile uint32_t PS2STATUS;      
    volatile uint32_t PS2INTID;       

} PS2_T;





 

 



























 



 



























 





   
   

 



 

typedef struct
{




























































































































































































































































































































































































































































































































































































































































































































































































 

    volatile uint32_t PPR;            
    volatile uint32_t CSR;            
    volatile uint32_t PCR;            
    volatile uint32_t CNR0;           
    volatile uint32_t CMR0;           
    volatile const  uint32_t PDR0;           
    volatile uint32_t CNR1;           
    volatile uint32_t CMR1;           
    volatile const  uint32_t PDR1;           
    volatile uint32_t CNR2;           
    volatile uint32_t CMR2;           
    volatile const  uint32_t PDR2;           
    volatile uint32_t CNR3;           
    volatile uint32_t CMR3;           
    volatile const  uint32_t PDR3;           
    volatile const  uint32_t RESERVED0[1]; 
    volatile uint32_t PIER;           
    volatile uint32_t PIIR;           
    volatile const  uint32_t RESERVE1[2];  
    volatile uint32_t CCR0;           
    volatile uint32_t CCR2;           
    volatile uint32_t CRLR0;          
    volatile uint32_t CFLR0;          
    volatile uint32_t CRLR1;          
    volatile uint32_t CFLR1;          
    volatile uint32_t CRLR2;          
    volatile uint32_t CFLR2;          
    volatile uint32_t CRLR3;          
    volatile uint32_t CFLR3;          
    volatile uint32_t CAPENR;         
    volatile uint32_t POE;            
    volatile uint32_t TCON;           
    volatile uint32_t TSTATUS;        
    volatile uint32_t SYNCBUSY0;      
    volatile uint32_t SYNCBUSY1;      
    volatile uint32_t SYNCBUSY2;      
    volatile uint32_t SYNCBUSY3;      
    volatile const  uint32_t RESERVE2[10]; 
    volatile uint32_t CAPPDMACTL;     
    volatile uint32_t CAP0PDMA;       
    volatile uint32_t CAP1PDMA;       
    volatile uint32_t CAP2PDMA;       
    volatile uint32_t CAP3PDMA;       

} PWM_T;






 

 












 












 




























































 



 



 



 































 
























 










































 










































 



 



 



 












 













 













 



 



 



 



 




































 



 



 



 


   
   

 



 

typedef struct
{






































































































































































































































































































































































 

    volatile uint32_t CNTRL;          
    volatile uint32_t DIVIDER;        
    volatile uint32_t SSR;            
    volatile const  uint32_t RESERVE0;     
    volatile const  uint32_t RX[2];          
    volatile const  uint32_t RESERVE1;     
    volatile const  uint32_t RESERVE2;     
    volatile  uint32_t TX[2];          
    volatile const  uint32_t RESERVE3;     
    volatile const  uint32_t RESERVE4;     
    volatile const  uint32_t RESERVE5;     
    volatile uint32_t VARCLK;         
    volatile uint32_t DMA;            
    volatile uint32_t CNTRL2;         
    volatile uint32_t FIFO_CTL;       
    volatile uint32_t STATUS;                 

} SPI_T;





 

 






















































 






 















 









 
























 
























 



































   
   


 



 


typedef struct
{
































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































 

    volatile const  uint32_t PDID;           
    volatile uint32_t RSTSRC;         
    volatile uint32_t IPRSTC1;        
    volatile uint32_t IPRSTC2;        
    volatile const  uint32_t RESERVE0[2];
    volatile uint32_t BODCR;          
    volatile const  uint32_t RESERVE1[2];
    volatile uint32_t PORCR;          
    volatile const  uint32_t RESERVE2[2];
    volatile uint32_t GPA_MFP;        
    volatile uint32_t GPB_MFP;        
    volatile uint32_t GPC_MFP;        
    volatile uint32_t GPD_MFP;        
    volatile const  uint32_t RESERVE3;
    volatile uint32_t GPF_MFP;        
    volatile const  uint32_t RESERVE4[2];
    volatile uint32_t ALT_MFP;        
    volatile uint32_t ALT_MFP1;       
    volatile const  uint32_t RESERVE5[26];
    volatile uint32_t GPA_IOCR;       
    volatile uint32_t GPB_IOCR;       
    volatile const  uint32_t RESERVE6;
    volatile uint32_t GPD_IOCR;       
    volatile const  uint32_t RESERVE7[12];
    volatile uint32_t REGWRPROT;      
    volatile const  uint32_t RESERVE8[12];
    volatile uint32_t GPA_MFPH;       
    volatile uint32_t GPB_MFPL;       
    volatile uint32_t GPB_MFPH;       
    volatile uint32_t GPC_MFPL;       
    volatile uint32_t GPC_MFPH;       
    volatile uint32_t GPD_MFPL;       
    volatile uint32_t GPD_MFPH;       
    volatile const  uint32_t RESERVE9[2];
    volatile uint32_t GPF_MFPL;       

} GCR_T;






 

 





















 









 



















































 





















 



 







 






 






 






 















 































































 



























 






 
























 












 






 


















 
























 





















 


















 


















 


















 












 













   



typedef struct
{































 

    volatile const  uint32_t IRQSRC[32];     
    volatile uint32_t NMISEL;         
    volatile uint32_t MCUIRQ;         

} GCR_INT_T;





 

 



 






 



   
   

 



 

typedef struct
{









































































































































 

    volatile uint32_t TCSR;           
    volatile uint32_t TCMPR;          
    volatile uint32_t TISR;           
    volatile const  uint32_t TDR;            
    volatile const  uint32_t TCAP;           
    volatile uint32_t TEXCON;         
    volatile uint32_t TEXISR;         

} TIMER_T;






 


 






























 



 






 



 



 





















 


   
   


 




 

typedef struct
{


    




















































































































































































































































































































































































































































 

    union {
    volatile uint32_t DATA;           
    volatile uint32_t THR;            
    volatile uint32_t RBR;            
    };
    volatile uint32_t IER;            
    volatile uint32_t FCR;            
    volatile uint32_t LCR;            
    volatile uint32_t MCR;            
    volatile uint32_t MSR;            
    volatile uint32_t FSR;            
    volatile uint32_t ISR;            
    volatile uint32_t TOR;            
    volatile uint32_t BAUD;           
    volatile uint32_t IRCR;           
    volatile uint32_t ALT_CSR;        
    volatile uint32_t FUN_SEL;        

} UART_T;






 

 



 



 




































 















 


















 









 










 







































 





























































 






 












 









 















 



   
   

 



 


typedef struct
{

































































 

    volatile uint32_t BUFSEG;         
    volatile uint32_t MXPLD;          
    volatile uint32_t CFG;            
    volatile uint32_t CFGP;           

} USBD_EP_T;





typedef struct
{




























































































































































































































 

    volatile uint32_t INTEN;          
    volatile uint32_t INTSTS;         
    volatile uint32_t FADDR;          
    volatile const  uint32_t EPSTS;          
    volatile uint32_t ATTR;           
    volatile const  uint32_t FLDET;          
    volatile uint32_t STBUFSEG;       
    volatile const  uint32_t RESERVE0[29]; 
    volatile uint32_t DRVSE0;         
    volatile const  uint32_t RESERVE2[283];
        USBD_EP_T EP[8];          

} USBD_T;






 

 


















 







































 



 



























 






























 



 



 



 



 















 






 


   
   


 



 

typedef struct
{













































































 

    volatile uint32_t WTCR;           
    volatile uint32_t WTCRALT;        

} WDT_T;






 

 






























 


   
   


 



 

typedef struct
{









































































 

    volatile uint32_t WWDTRLD;        
    volatile uint32_t WWDTCR;         
    volatile uint32_t WWDTSR;         
    volatile const  uint32_t WWDTCVR;        

} WWDT_T;





 

 



 















 






 


   
   
   


 
 
 



 
 






 
#line 8413 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"





































#line 8456 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"









   

 
 
 




 
#line 8481 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"




































#line 8523 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"







   











 

typedef volatile unsigned char  vu8;        
typedef volatile unsigned short vu16;       
typedef volatile unsigned long  vu32;       





 







 







 








 







 








 







 







 






 








 







 








 







 







 






 


   







 













 
#line 8724 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"

 










   


 
 
 
#line 1 "..\\Library\\StdDriver\\inc\\SYS.h"
 









 










 



 



 


 
 
 
#line 54 "..\\Library\\StdDriver\\inc\\SYS.h"


 
 
 
#line 65 "..\\Library\\StdDriver\\inc\\SYS.h"


 
 
 










 





































































































































































































































































































































































































































































































































































































































































































































































































 
 
 







 







































































































































































































































   



 







 








 








 








 








 









 








 








 








 












 








 








 








 








 








 








 








 








 








 








 








 














 









 
static __inline void SYS_LockReg(void)
{
    ((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->REGWRPROT = 0;
}








 
static __inline void SYS_UnlockReg(void)
{
    while(((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->REGWRPROT != (1ul << 0))
    {
        ((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->REGWRPROT = 0x59;
        ((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->REGWRPROT = 0x16;
        ((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->REGWRPROT = 0x88;
    }
}


void SYS_ClearResetSrc(uint32_t u32Src);
uint32_t SYS_GetBODStatus(void);
uint32_t SYS_GetResetSrc(void);
uint32_t SYS_IsRegLocked(void);
uint32_t  SYS_ReadPDID(void);
void SYS_ResetChip(void);
void SYS_ResetCPU(void);
void SYS_ResetModule(uint32_t u32ModuleIndex);
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel);
void SYS_DisableBOD(void);


   

   

   








 
#line 8743 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\ADC.h"
 









 



#line 1 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
 









 


















 


#line 8760 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"



#line 16 "..\\Library\\StdDriver\\inc\\ADC.h"









 



 



 
 
 
 


















 
 
 



 
 
 
#line 70 "..\\Library\\StdDriver\\inc\\ADC.h"

 
 
 




 
 
 




 
 
 





 
 
 



 
 
 




   



 










 








 







 








 












 












 








 









 









 








 







 
















 
#line 246 "..\\Library\\StdDriver\\inc\\ADC.h"






 
















 
#line 279 "..\\Library\\StdDriver\\inc\\ADC.h"






 










 







 








 


void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask);
void ADC_Close(ADC_T *adc);
void ADC_EnableHWTrigger(ADC_T *adc,
                         uint32_t u32Source,
                         uint32_t u32Param);
void ADC_DisableHWTrigger(ADC_T *adc);
void ADC_EnableInt(ADC_T *adc, uint32_t u32Mask);
void ADC_DisableInt(ADC_T *adc, uint32_t u32Mask);



   

   

   







 
#line 8744 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\FMC.h"
 









 



#line 16 "..\\Library\\StdDriver\\inc\\FMC.h"









 



 



 


 
 
 







 
 
 



 
 
 
#line 62 "..\\Library\\StdDriver\\inc\\FMC.h"


   



 

 
 
 









 












 













 













 














 











 













 












 













 















 














 



 
 
 











 
static __inline void FMC_Write(uint32_t u32addr, uint32_t u32data)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x21;    
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = u32addr;               
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPDAT = u32data;               
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = 0x1;                   
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                             
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG);                  
}










 
static __inline uint32_t FMC_Read(uint32_t u32addr)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x00;  
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = u32addr;          
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = 0x1;              
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                        
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG);             

    return ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPDAT;
}













 
static __inline int32_t FMC_Erase(uint32_t u32addr)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x22;  
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = u32addr;                
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = 0x1;                    
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                              
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG);                   

     
    if(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCON & (1ul << 6))
    {
        ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCON |= (1ul << 6);
        return -1;
    }
    return 0;
}










 
static __inline uint32_t FMC_ReadUID(uint8_t u8index)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x04;  
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = (u8index << 2);       
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = 0x1;                  
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                            
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG);                 

    return ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPDAT;
}











 
static __inline uint32_t FMC_ReadCID(void)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x0B;            
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = 0x0;                            
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = (1ul << 0);           
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                                      
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG & (1ul << 0)) ;   

    return ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPDAT;
}











 
static __inline uint32_t FMC_ReadDID(void)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x0C;           
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = 0;                             
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = (1ul << 0);          
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                                     
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG & (1ul << 0));   

    return ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPDAT;
}












 
static __inline uint32_t FMC_ReadPID(void)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x0C;           
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = 0x04;                          
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = (1ul << 0);          
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                                     
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG & (1ul << 0));   

    return ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPDAT;
}










 
static __inline uint32_t FMC_ReadUCID(uint32_t u32Index)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x04;           
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = (0x04 * u32Index) + 0x10;      
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = (1ul << 0);          
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                                     
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG & (1ul << 0));   

    return ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPDAT;
}















 
static __inline void FMC_SetVectorPageAddr(uint32_t u32PageAddr)
{
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPCMD = 0x2e;  
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPADR = u32PageAddr;        
    ((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG = 0x1;                
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);                          
    while(((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPTRG);               
}














 
static __inline uint32_t FMC_GetVECMAP(void)
{
    return (((FMC_T *) ((( uint32_t)0x50000000) + 0x0C000))->ISPSTA & (0xFFFul << 9));
}

extern void FMC_Open(void);
extern void FMC_Close(void);
extern void FMC_EnableAPUpdate(void);
extern void FMC_DisableAPUpdate(void);
extern void FMC_EnableConfigUpdate(void);
extern void FMC_DisableConfigUpdate(void);
extern void FMC_EnableLDUpdate(void);
extern void FMC_DisableLDUpdate(void);
extern int32_t FMC_ReadConfig(uint32_t *u32Config, uint32_t u32Count);
extern int32_t FMC_WriteConfig(uint32_t *u32Config, uint32_t u32Count);
extern void FMC_SetBootSource(int32_t i32BootSrc);
extern int32_t FMC_GetBootSource(void);
extern uint32_t FMC_ReadDataFlashBaseAddr(void);

   

   

   








#line 8745 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\GPIO.h"
 









 











 



 



 


 
 
 





 
 
 






 
 
 



 
 
 






#line 82 "..\\Library\\StdDriver\\inc\\GPIO.h"















 
#line 146 "..\\Library\\StdDriver\\inc\\GPIO.h"


   




 















 
















 
















 
















 
















 
















 
















 

















 

































 










 











 










 






















 

















 



















 

















 



void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs);
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin);


   

   

   







 
#line 8746 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\I2C.h"
 









 



#line 16 "..\\Library\\StdDriver\\inc\\I2C.h"









 



 



 

 
 
 
#line 49 "..\\Library\\StdDriver\\inc\\I2C.h"




   



 









 










 










 










 










 











 










 











 











 










 


void I2C_ClearTimeoutFlag(I2C_T *i2c);
void I2C_Close(I2C_T *i2c);
void I2C_Trigger(I2C_T *i2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Si, uint8_t u8Ack);
void I2C_DisableInt(I2C_T *i2c);
void I2C_EnableInt(I2C_T *i2c);
uint32_t I2C_GetBusClockFreq(I2C_T *i2c);
uint32_t I2C_SetBusClockFreq(I2C_T *i2c, uint32_t u32BusClock);
uint32_t I2C_GetIntFlag(I2C_T *i2c);
uint32_t I2C_GetStatus(I2C_T *i2c);
uint32_t I2C_Open(I2C_T *i2c, uint32_t u32BusClock);
uint8_t I2C_GetData(I2C_T *i2c);
void I2C_SetSlaveAddr(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddr, uint8_t u8GCMode);
void I2C_SetSlaveAddrMask(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddrMask);
void I2C_EnableTimeout(I2C_T *i2c, uint8_t u8LongTimeout);
void I2C_DisableTimeout(I2C_T *i2c);
void I2C_EnableWakeup(I2C_T *i2c);
void I2C_DisableWakeup(I2C_T *i2c);
void I2C_SetData(I2C_T *i2c, uint8_t u8Data);
uint8_t I2C_WriteByte(I2C_T *i2c, uint8_t u8SlaveAddr, const uint8_t data);
uint32_t I2C_WriteMultiBytes(I2C_T *i2c, uint8_t u8SlaveAddr, const uint8_t *data, uint32_t u32wLen);
uint8_t I2C_WriteByteOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, const uint8_t data);
uint32_t I2C_WriteMultiBytesOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, const uint8_t *data, uint32_t u32wLen);
uint8_t I2C_WriteByteTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, const uint8_t data);
uint32_t I2C_WriteMultiBytesTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, const uint8_t *data, uint32_t u32wLen);
uint8_t I2C_ReadByte(I2C_T *i2c, uint8_t u8SlaveAddr);
uint32_t I2C_ReadMultiBytes(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t *rdata, uint32_t u32rLen);
uint8_t I2C_ReadByteOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr);
uint32_t I2C_ReadMultiBytesOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t *rdata, uint32_t u32rLen);
uint8_t I2C_ReadByteTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr);
uint32_t I2C_ReadMultiBytesTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t *rdata, uint32_t u32rLen);
   

   

   

#line 8747 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\PWM.h"
 








 











 



 



 
#line 43 "..\\Library\\StdDriver\\inc\\PWM.h"
 
 
 






   




 










 
#line 78 "..\\Library\\StdDriver\\inc\\PWM.h"








 









 












 
















 












 













 















 
#line 178 "..\\Library\\StdDriver\\inc\\PWM.h"


uint32_t PWM_ConfigCaptureChannel(PWM_T *pwm,
                                  uint32_t u32ChannelNum,
                                  uint32_t u32UnitTimeNsec,
                                  uint32_t u32CaptureEdge);
uint32_t PWM_ConfigOutputChannel(PWM_T *pwm,
                                 uint32_t u32ChannelNum,
                                 uint32_t u32Frequncy,
                                 uint32_t u32DutyCycle);
void PWM_Start(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_Stop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_ForceStop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
void PWM_DisableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
uint32_t PWM_GetADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnablePDMA(PWM_T *pwm, uint32_t u32ChannelMask, uint32_t u32RisingFirst);
void PWM_DisablePDMA(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration);
void PWM_DisableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void PWM_DisableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void PWM_ClearCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
uint32_t PWM_GetCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType);
void PWM_DisableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType);
void PWM_DisablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);



   

   

   







 
#line 8748 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\SPI.h"
 









 











 



 



 














#line 52 "..\\Library\\StdDriver\\inc\\SPI.h"







   




 






 







 







 







 







 







 







 








 







 







 







 







 







 








 








 








 







 







 








 








 










 







 







 







 







 







 







 










 







 







 








 








 









 




 
uint32_t SPI_Open(SPI_T *spi, uint32_t u32MasterSlave, uint32_t u32SPIMode, uint32_t u32DataWidth, uint32_t u32BusClock);
void SPI_Close(SPI_T *spi);
void SPI_ClearRxFIFO(SPI_T *spi);
void SPI_ClearTxFIFO(SPI_T *spi);
void SPI_DisableAutoSS(SPI_T *spi);
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock);
void SPI_EnableFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold);
void SPI_DisableFIFO(SPI_T *spi);
uint32_t SPI_GetBusClock(SPI_T *spi);
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask);
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask);
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask);





 



 



 




#line 8749 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\TIMER.h"
 








 











 



 



 

#line 43 "..\\Library\\StdDriver\\inc\\TIMER.h"

   




 










 












 











 










 
static __inline void TIMER_Start(TIMER_T *timer)
{
    timer->TCSR |= (1ul << 30);
}









 
static __inline void TIMER_Stop(TIMER_T *timer)
{
    timer->TCSR &= ~(1ul << 30);
}










 
static __inline void TIMER_EnableWakeup(TIMER_T *timer)
{
    timer->TCSR |= (1ul << 23);
}









 
static __inline void TIMER_DisableWakeup(TIMER_T *timer)
{
    timer->TCSR &= ~(1ul << 23);
}









 
static __inline void TIMER_EnableCaptureDebounce(TIMER_T *timer)
{
    timer->TEXCON |= (1ul << 6);
}









 
static __inline void TIMER_DisableCaptureDebounce(TIMER_T *timer)
{
    timer->TEXCON &= ~(1ul << 6);
}









 
static __inline void TIMER_EnableEventCounterDebounce(TIMER_T *timer)
{
    timer->TEXCON |= (1ul << 7);
}









 
static __inline void TIMER_DisableEventCounterDebounce(TIMER_T *timer)
{
    timer->TEXCON &= ~(1ul << 7);
}









 
static __inline void TIMER_EnableInt(TIMER_T *timer)
{
    timer->TCSR |= (1ul << 29);
}









 
static __inline void TIMER_DisableInt(TIMER_T *timer)
{
    timer->TCSR &= ~(1ul << 29);
}









 
static __inline void TIMER_EnableCaptureInt(TIMER_T *timer)
{
    timer->TEXCON |= (1ul << 5);
}









 
static __inline void TIMER_DisableCaptureInt(TIMER_T *timer)
{
    timer->TEXCON &= ~(1ul << 5);
}










 
static __inline uint32_t TIMER_GetIntFlag(TIMER_T *timer)
{
    return (timer->TISR & (1ul << 0) ? 1 : 0);
}









 
static __inline void TIMER_ClearIntFlag(TIMER_T *timer)
{
    timer->TISR = (1ul << 0);
}










 
static __inline uint32_t TIMER_GetCaptureIntFlag(TIMER_T *timer)
{
    return timer->TEXISR;
}









 
static __inline void TIMER_ClearCaptureIntFlag(TIMER_T *timer)
{
    timer->TEXISR = (1ul << 0);
}










 
static __inline uint32_t TIMER_GetWakeupFlag(TIMER_T *timer)
{
    return (timer->TISR & (1ul << 1) ? 1 : 0);
}









 
static __inline void TIMER_ClearWakeupFlag(TIMER_T *timer)
{
    timer->TISR = (1ul << 1);
}









 
static __inline uint32_t TIMER_GetCaptureData(TIMER_T *timer)
{
    return timer->TCAP;
}









 
static __inline uint32_t TIMER_GetCounter(TIMER_T *timer)
{
    return timer->TDR;
}

uint32_t TIMER_Open(TIMER_T *timer, uint32_t u32Mode, uint32_t u32Freq);
void TIMER_Close(TIMER_T *timer);
void TIMER_Delay(TIMER_T *timer, uint32_t u32Usec);
void TIMER_EnableCapture(TIMER_T *timer, uint32_t u32CapMode, uint32_t u32Edge);
void TIMER_DisableCapture(TIMER_T *timer);
void TIMER_EnableEventCounter(TIMER_T *timer, uint32_t u32Edge);
void TIMER_DisableEventCounter(TIMER_T *timer);
uint32_t TIMER_GetModuleClock(TIMER_T *timer);

   

   

   







 
#line 8750 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\WDT.h"
 








 











 



 



 
 
 
 
#line 42 "..\\Library\\StdDriver\\inc\\WDT.h"

 
 
 





   




 









 










 










 











 











 











 












 










 
static __inline void WDT_Close(void)
{
    ((WDT_T *) ((( uint32_t)0x40000000) + 0x4000))->WTCR = 0;
    return;
}









 
static __inline void WDT_EnableInt(void)
{
    ((WDT_T *) ((( uint32_t)0x40000000) + 0x4000))->WTCR |= (1ul << 6);
    return;
}









 
static __inline void WDT_DisableInt(void)
{
    
    ((WDT_T *) ((( uint32_t)0x40000000) + 0x4000))->WTCR &= ~((1ul << 6) | (1ul << 2) | (1ul << 3) | (1ul << 5));
    return;
}

void WDT_Open(uint32_t u32TimeoutInterval, uint32_t u32ResetDelay, uint32_t u32EnableReset, uint32_t u32EnableWakeup);

   

   

   







 
#line 8751 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\WWDT.h"
 








 











 



 



 
 
 
 
#line 50 "..\\Library\\StdDriver\\inc\\WWDT.h"



   




 









 










 











 











 










 












 


void WWDT_Open(uint32_t u32PreScale, uint32_t u32CmpValue, uint32_t u32EnableInt);

   

   

   







 
#line 8752 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\UART.h"
 









 












 



 



 
    
 
 
 



   
 
 
 











 
 
 
















 
 
 



 
 
 



 
 
 




 
 
 




   




 











 











 












 










 












 












 











 











 











 












 











 












 












 



















 


















 



































 











 
static __inline void UART_CLEAR_RTS(UART_T* uart)
{
    (uart)->MCR |= (1ul << 9);
    (uart)->MCR &= ~(1ul << 1);
}








 
static __inline void UART_SET_RTS(UART_T* uart)
{
    (uart)->MCR |= (1ul << 9) | (1ul << 1);
}










 












 



void UART_ClearIntFlag(UART_T* uart , uint32_t u32InterruptFlag);
void UART_Close(UART_T* uart);
void UART_DisableFlowCtrl(UART_T* uart);
void UART_DisableInt(UART_T*  uart, uint32_t u32InterruptFlag);
void UART_EnableFlowCtrl(UART_T* uart);
void UART_EnableInt(UART_T*  uart, uint32_t u32InterruptFlag);
void UART_Open(UART_T* uart, uint32_t u32baudrate);
uint32_t UART_Read(UART_T* uart, uint8_t *pu8RxBuf, uint32_t u32ReadBytes);
void UART_SetLine_Config(UART_T* uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits);
void UART_SetTimeoutCnt(UART_T* uart, uint32_t u32TOC);
void UART_SelectIrDAMode(UART_T* uart, uint32_t u32Buadrate, uint32_t u32Direction);
void UART_SelectRS485Mode(UART_T* uart, uint32_t u32Mode, uint32_t u32Addr);
uint32_t UART_Write(UART_T* uart, uint8_t *pu8TxBuf, uint32_t u32WriteBytes);


   

   

   







 

#line 8753 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\I2S.h"
 








 



#line 15 "..\\Library\\StdDriver\\inc\\I2S.h"








 



 



 





 



 





 



 
#line 60 "..\\Library\\StdDriver\\inc\\I2S.h"

#line 69 "..\\Library\\StdDriver\\inc\\I2S.h"

 



 



   



 
 
 
 








 
static __inline void I2S_ENABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == 0)
        i2s->CON |= (1ul << 16);
    else
        i2s->CON |= (1ul << 17);
}









 
static __inline void I2S_DISABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == 0)
        i2s->CON &= ~(1ul << 16);
    else
        i2s->CON &= ~(1ul << 17);
}






 







 







 







 







 







 







 







 







 







 







 







 










 
static __inline void I2S_SET_MONO_RX_CHANNEL(I2S_T *i2s, uint32_t u32Ch)
{
    u32Ch == (1ul << 23) ?
    (i2s->CON |= (1ul << 23)) :
    (i2s->CON &= ~(1ul << 23));
}







 







 



















 














 







 







 



 
uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat);
void I2S_Close(I2S_T *i2s);
void I2S_EnableInt(I2S_T *i2s, uint32_t u32Mask);
void I2S_DisableInt(I2S_T *i2s, uint32_t u32Mask);
uint32_t I2S_EnableMCLK(I2S_T *i2s, uint32_t u32BusClock);
void I2S_DisableMCLK(I2S_T *i2s);

   


   

   



 

#line 8754 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\USBD.h"
 









 







 



 



 


typedef struct s_usbd_info
{
    const uint8_t *gu8DevDesc;             
    const uint8_t *gu8ConfigDesc;          
    const uint8_t **gu8StringDesc;         
    const uint8_t **gu8HidReportDesc;      
    const uint32_t *gu32HidReportSize;     
    const uint32_t *gu32ConfigHidDescIdx;  

} S_USBD_INFO_T;

extern const S_USBD_INFO_T gsInfo;

   





 







#line 65 "..\\Library\\StdDriver\\inc\\USBD.h"


 




 
#line 84 "..\\Library\\StdDriver\\inc\\USBD.h"

 
#line 93 "..\\Library\\StdDriver\\inc\\USBD.h"

 



 
#line 105 "..\\Library\\StdDriver\\inc\\USBD.h"

 







 



 
 
 














#line 148 "..\\Library\\StdDriver\\inc\\USBD.h"















   





 










 












 












 











 











 











 











 











 











 











 














 











 














 











 















 












 











 












 












 













 











 













 













 











 











 










 












 















 
static __inline void USBD_MemCopy(uint8_t *dest, uint8_t *src, int32_t size)
{
    while(size--) *dest++ = *src++;
}











 
static __inline void USBD_SetStall(uint8_t epnum)
{
    uint32_t u32CfgAddr;
    uint32_t u32Cfg;
    int i;

    for(i = 0; i < 8; i++)
    {
        u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&((USBD_T *) ((( uint32_t)0x40000000) + 0x60000))->EP[0].CFG;  
        u32Cfg = *((volatile uint32_t *)(u32CfgAddr));

        if((u32Cfg & 0xf) == epnum)
        {
            u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&((USBD_T *) ((( uint32_t)0x40000000) + 0x60000))->EP[0].CFGP;  
            u32Cfg = *((volatile uint32_t *)(u32CfgAddr));

            *((volatile uint32_t *)(u32CfgAddr)) = (u32Cfg | (1ul << 1));
            break;
        }
    }
}









 
static __inline void USBD_ClearStall(uint8_t epnum)
{
    uint32_t u32CfgAddr;
    uint32_t u32Cfg;
    int i;

    for(i = 0; i < 8; i++)
    {
        u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&((USBD_T *) ((( uint32_t)0x40000000) + 0x60000))->EP[0].CFG;  
        u32Cfg = *((volatile uint32_t *)(u32CfgAddr));

        if((u32Cfg & 0xf) == epnum)
        {
            u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&((USBD_T *) ((( uint32_t)0x40000000) + 0x60000))->EP[0].CFGP;  
            u32Cfg = *((volatile uint32_t *)(u32CfgAddr));

            *((volatile uint32_t *)(u32CfgAddr)) = (u32Cfg & ~(1ul << 1));
            break;
        }
    }
}











 
static __inline uint32_t USBD_GetStall(uint8_t epnum)
{
    uint32_t u32CfgAddr;
    uint32_t u32Cfg;
    int i;

    for(i = 0; i < 8; i++)
    {
        u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&((USBD_T *) ((( uint32_t)0x40000000) + 0x60000))->EP[0].CFG;  
        u32Cfg = *((volatile uint32_t *)(u32CfgAddr));

        if((u32Cfg & 0xf) == epnum)
        {
            u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&((USBD_T *) ((( uint32_t)0x40000000) + 0x60000))->EP[0].CFGP;  
            break;
        }
    }

    return ((*((volatile uint32_t *)(u32CfgAddr))) & (1ul << 1));
}


extern volatile uint8_t g_usbd_RemoteWakeupEn;

typedef void (*VENDOR_REQ)(void);            
typedef void (*CLASS_REQ)(void);             
typedef void (*SET_INTERFACE_REQ)(void);     
typedef void (*SET_CONFIG_CB)(void);        

 
void USBD_Open(const S_USBD_INFO_T *param, CLASS_REQ pfnClassReq, SET_INTERFACE_REQ pfnSetInterface);
void USBD_Start(void);
void USBD_GetSetupPacket(uint8_t *buf);
void USBD_ProcessSetupPacket(void);
void USBD_StandardRequest(void);
void USBD_PrepareCtrlIn(uint8_t *pu8Buf, uint32_t u32Size);
void USBD_CtrlIn(void);
void USBD_PrepareCtrlOut(uint8_t *pu8Buf, uint32_t u32Size);
void USBD_CtrlOut(void);
void USBD_SwReset(void);
void USBD_SetVendorRequest(VENDOR_REQ pfnVendorReq);
void USBD_SetConfigCallback(SET_CONFIG_CB pfnSetConfigCallback);
void USBD_LockEpStall(uint32_t u32EpBitmap);

   

   

   




 
#line 8755 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\PDMA.h"
 









 



#line 16 "..\\Library\\StdDriver\\inc\\PDMA.h"




 



 



 

 
 
 




 
 
 





 
 
 
#line 66 "..\\Library\\StdDriver\\inc\\PDMA.h"


   



 









 










 











 











 











 











 












 
#line 163 "..\\Library\\StdDriver\\inc\\PDMA.h"









 


void PDMA_Open(uint32_t u32Mask);
void PDMA_Close(void);
void PDMA_SetTransferCnt(uint32_t u32Ch, uint32_t u32Width, uint32_t u32TransCount);
void PDMA_SetTransferAddr(uint32_t u32Ch, uint32_t u32SrcAddr, uint32_t u32SrcCtrl, uint32_t u32DstAddr, uint32_t u32DstCtrl);
void PDMA_SetTransferMode(uint32_t u32Ch, uint32_t u32Periphral, uint32_t u32ScatterEn, uint32_t u32DescAddr);
void PDMA_Trigger(uint32_t u32Ch);
void PDMA_EnableInt(uint32_t u32Ch, uint32_t u32Mask);
void PDMA_DisableInt(uint32_t u32Ch, uint32_t u32Mask);




 



 



 


#line 8756 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\PS2.h"
 








 



 
 
 
#line 18 "..\\Library\\StdDriver\\inc\\PS2.h"









 



 




 

 
 
 










 











 











 












 
static __inline void PS2_CLEAR_TX_FIFO(void)
{
    ((PS2_T *) ((( uint32_t)0x40100000) + 0x00000))->PS2CON |= (1ul << 8);
    ((PS2_T *) ((( uint32_t)0x40100000) + 0x00000))->PS2CON &= ~(1ul << 8);
}









 










 











 










 










 










 










 










 










 










 










 










 



 
 
 

void PS2_Open(void);
void PS2_Close(void);
uint8_t PS2_Read(void);
int32_t PS2_Write(uint32_t *pu32Buf, uint32_t u32ByteCount);
void PS2_EnableInt(uint32_t u32Mask);
void PS2_DisableInt(uint32_t u32Mask);


   

   

   







 

#line 8757 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\CLK.h"
 









 










 



 



 








 
 
 













 
 
 








#line 72 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 93 "..\\Library\\StdDriver\\inc\\CLK.h"





#line 106 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 115 "..\\Library\\StdDriver\\inc\\CLK.h"


 
 
 









#line 137 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 146 "..\\Library\\StdDriver\\inc\\CLK.h"






#line 160 "..\\Library\\StdDriver\\inc\\CLK.h"




 
 
 






 
 
 










#line 198 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 205 "..\\Library\\StdDriver\\inc\\CLK.h"


 
 
 

 

#line 223 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 232 "..\\Library\\StdDriver\\inc\\CLK.h"


#line 240 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 259 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 275 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 282 "..\\Library\\StdDriver\\inc\\CLK.h"

#line 301 "..\\Library\\StdDriver\\inc\\CLK.h"





   




 







 
static __inline uint32_t CLK_GetPLLClockFreq(void)
{
    uint32_t u32PllFreq = 0, u32PllReg;
    uint32_t u32FIN, u32NF, u32NR, u32NO;
    uint8_t au8NoTbl[4] = {1, 2, 2, 4};

    u32PllReg = ((CLK_T *) ((( uint32_t)0x50000000) + 0x00200))->PLLCON;

    if(u32PllReg & ((1ul << 16) | (1ul << 18)))
        return 0;            

    if(u32PllReg & 0x00080000UL)
        u32FIN = (22118400UL);     
    else
        u32FIN = (12000000UL);      

    if(u32PllReg & (1ul << 17))
        return u32FIN;       

     
    u32NO = au8NoTbl[((u32PllReg & (3ul << 14)) >> 14)];
    u32NF = ((u32PllReg & (0x1FFul << 0)) >> 0) + 2;
    u32NR = ((u32PllReg & (0x1Ful << 9)) >> 9) + 2;

     
    u32PllFreq = (((u32FIN >> 2) * u32NF) / (u32NR * u32NO) << 2);

    return u32PllFreq;
}










 
static __inline void CLK_SysTickDelay(uint32_t us)
{
    ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = us * CyclesPerUs;
    ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL  = (0x00);
    ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) | (1UL );

     
    while((((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL & (1UL << 16U)) == 0);
    
     
    ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = 0;    
}


void CLK_DisableCKO(void);
void CLK_EnableCKO(uint32_t u32ClkSrc, uint32_t u32ClkDiv, uint32_t u32ClkDivBy1En);
void CLK_PowerDown(void);
void CLK_Idle(void);
uint32_t CLK_GetHXTFreq(void);
uint32_t CLK_GetHCLKFreq(void);
uint32_t CLK_GetPCLKFreq(void);
uint32_t CLK_GetCPUFreq(void);
uint32_t CLK_SetCoreClock(uint32_t u32Hclk);
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc);
void CLK_EnableXtalRC(uint32_t u32ClkMask);
void CLK_DisableXtalRC(uint32_t u32ClkMask);
void CLK_EnableModuleClock(uint32_t u32ModuleIdx);
void CLK_DisableModuleClock(uint32_t u32ModuleIdx);
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq);
void CLK_DisablePLL(void);
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask);
void CLK_EnableSysTick(uint32_t u32ClkSrc, uint32_t u32Count);
void CLK_DisableSysTick(void);


   

   

   







 
#line 8758 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"
#line 1 "..\\Library\\StdDriver\\inc\\CRC.h"
 








 











 



 



 
 
 
 





 
 
 





 
 
 




   




 











 












 










 












 













 










 










 



 
void CRC_Open(uint32_t u32Mode, uint32_t u32Attribute, uint32_t u32Seed, uint32_t u32DataLen);
void CRC_StartDMATransfer(uint32_t u32SrcAddr, uint32_t u32ByteCount);
uint32_t CRC_GetChecksum(void);

   

   

   







 
#line 8759 "..\\Library\\Device\\Nuvoton\\NUC123\\Include\\NUC123.h"




#line 257 "..\\user\\types.h"
#line 1 "..\\user\\dwin.h"



 
 
 
#line 80 "..\\user\\dwin.h"


 
 
 


 
 
 
#line 138 "..\\user\\dwin.h"
 
 
 


 
 
 
#line 158 "..\\user\\dwin.h"
 
 
 


 
 
 






 
 
 

void DwinUSARTInit(void);
void DwinSendRegRequest(u8 reg);
void DwinSendRegValue(u8 reg, u8 val);
void DwinSendResRequest(u16 id);
void DwinSendResValue  (u16 id, u16 val);
void DwinJumpTo(u16 dlgId);
void DwinSetChar(u16 tbId, u8 c);
void DwinSetString(u16 tbId, u8 * str, u8 len);
void DwinSetIcon(u16 picId, u16 icoId);
void DwinRecvPolling(void);
void DwinSetBrightness(u8 auto_flag, u8 light);
extern u16 dwin_cur_id;




#line 258 "..\\user\\types.h"
#line 1 "..\\user\\delay.h"




void SysTimerDelay(u32 us);
void delay_us(u32 us);
void delay_ms(u32 ms);






#line 259 "..\\user\\types.h"
#line 1 "..\\user\\system_timer.h"







void SystemTimer0Init(void);


extern u16 timer0_delay_10ms_count;
extern u16 timer0_delay_1ms_count;
extern u16 timer0_delay_1s_count;
extern u8  timer0_delay_1s_already;








#line 260 "..\\user\\types.h"
#line 1 "..\\user\\system_adc.h"



void SystemAdcInit(void);
void SystemReadAdcPolling(void);
void VoiceModeNoSignalResetTimer(void);






#line 261 "..\\user\\types.h"
#line 1 "..\\user\\linux_command.h"



 
 
 
#line 20 "..\\user\\linux_command.h"

#line 31 "..\\user\\linux_command.h"





void LinuxUSARTInit(void);
void LinuxCommandSend(u8 cmd, u8 *data, u8 len);
u16  LinuxRecvPolling(void);
 
 
 


 
 
 






















































void HostCommandSend(u8 cmd, u8 para1, u8 para2, u8 *data, u8 len);
void HostCommandSendEnterSystem(u8 in);
void HostDisplaySignInfo(void);
void ExitMessageDisplay(void);
 
 
 








#line 262 "..\\user\\types.h"
#line 1 "..\\user\\wm8974.h"




void Wm8974RegisterInit(void);
void Wm8974SetDacDbVolume(s8 n_db);
void Wm8974SetDacHexVolume(u8 data);
void Wm8974SetAdcDbVolume(s8 n_db);
void Wm8974SetSpkVolCtrl(u8 flag);
void Wm8974SetMonoVolCtrl(u8 flag);




#line 263 "..\\user\\types.h"
#line 1 "..\\user\\io_define.h"



#line 5 "..\\user\\io_define.h"

#line 12 "..\\user\\io_define.h"





#line 23 "..\\user\\io_define.h"

#line 30 "..\\user\\io_define.h"







#line 44 "..\\user\\io_define.h"









#line 59 "..\\user\\io_define.h"

#line 67 "..\\user\\io_define.h"

















#line 90 "..\\user\\io_define.h"

#line 97 "..\\user\\io_define.h"

#line 104 "..\\user\\io_define.h"









































#line 151 "..\\user\\io_define.h"

#line 159 "..\\user\\io_define.h"




#line 264 "..\\user\\types.h"
#line 1 "..\\user\\dataflash.h"




void DataFlashInit(u32 *SaveData,u16 DataCount);
void DataFlashSave(u32 *SaveData,u16 DataCount);




 


#line 265 "..\\user\\types.h"
#line 1 "..\\user\\i2c_simulate.h"







typedef void	(*T_SimSerial_PO)			(u8 Level);		
typedef u8 		(*T_SimSerial_PI)			(void);			
typedef void	(*T_SimSerial_PIN_Mode)	(u8 Mode);		


typedef struct
{
	u8						Slave_Address;
	T_SimSerial_PO			SCK;
	T_SimSerial_PO			SDO;
	T_SimSerial_PI			SDI;
	T_SimSerial_PIN_Mode	SDA_Mode;
}T_I2C_Master_PIN_OPT;


void IIC_BUS_Write_One_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u8 txd);
void IIC_BUS_Write_More_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,uc8 *txd,u8 dat_Length);      
u8   IIC_BUS_Read_One_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr);                                  
void IIC_BUS_Read_More_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u8 *rxd,u8 dat_Length);        
void IIC_BUS_Write_4_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,uc32 data);
void IIC_BUS_Write_More_Byte_2_Byte_Rigister_Address(T_I2C_Master_PIN_OPT * PIN_OPT,u16 Sub_Addr,u16 dat_Length,const u8 *txd);
void IICDataDownload(uc8 *Register,T_I2C_Master_PIN_OPT * IICCompment,u16 ArrayLength);
void IIC_BUS_Read_More_Byte_2_Byte_Rigister_Address(T_I2C_Master_PIN_OPT * PIN_OPT,u16 Sub_Addr,u8 *rxd,u16 dat_Length);
void IIC_BUS_Write_7Bitadd_9Bitdata(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u16 txd);




 















#line 266 "..\\user\\types.h"
#line 1 "..\\user\\strconv.h"



int  strcmp_fixName(u8 * pBtnName, const char * fixName);
void StringMac2ByteHex(u8* stringhex, u8* bytehex, u8 len);
void StringIp2ByteHex(u8* stringip, u8* bytehex, u8 len);
void GetComipleDate_to_ver(u8 *dst);
u32  U8_4_Change_U32(u8 *U8_4);
void U32_Change_U8_4(u32 U32, u8 *U8_4);




#line 267 "..\\user\\types.h"
#line 1 "..\\user\\audio_control.h"



 
 
 
typedef enum
{
	VOL_FADE_MIN,
	VOL_FADE_HOLD_MUTE,
	VOL_FADE_RELEASE,
	VOL_FADE_NORMAL,
}VOL_FADE_T;

typedef struct
{
	u8 			real_value;
	u8 			expect_value;
	u8			value;
	u8 			fade_delay_count;
	u8			hold_status_count;
	
	VOL_FADE_T	status;
	u16			mute_flag;
}VOL_T;

typedef enum
{
	MIC_STATUS_CLOSE,
	MIC_STATUS_OPEN,
	MIC_STATUS_WAIT,
	MIC_STATUS_APPLY,
}MIC_STATUS_T;

typedef enum
{
	MIC_MODE_FIFO = 1,
	MIC_MODE_NORMAL,
	MIC_MODE_VOICE,
	MIC_MODE_APPLY,
}MIC_MODE_E;

typedef enum
{
	MIC_OPEN_TOTAL_1 = 1,
	MIC_OPEN_TOTAL_2 = 2,
	MIC_OPEN_TOTAL_4 = 4,
	MIC_OPEN_TOTAL_6 = 6,
}MIC_OPEN_TOTAL_E;

typedef struct
{	
	MIC_STATUS_T 		status;
	u8					enable;
	u8 					recv_ch;
	u8					send_ch;
	u8					display;
	u8					use;
	MIC_MODE_E			mode;
	MIC_OPEN_TOTAL_E	open_total;
	u16					v_sen;
	u16					nos_tmr;
	u16					nos_cnt;
}MIC_T;

typedef struct
{	
	u8			old_status;
	u8			now_status;
	u8			hold_count;
}E_DET_T;
 
 
 


 
 
 

#line 87 "..\\user\\audio_control.h"








 
 
 



void AudioControlPolling(void);
void VOL_FAST_SET_MUTE(u16 x);
void HardwordOpenMic(u8 sender_ch, u8 led_change);
void HardwordCloseMic(u8 send_to_host, u8 led_change);
void NormalMicSwitch(void);
extern VOL_T 	vol;
extern MIC_T	mic;
extern E_DET_T	e_det;





#line 268 "..\\user\\types.h"
#line 1 "..\\user\\key.h"



void KeyInputPolling(void);
void WaitUsbAesUidKeyInputPolling(void);



 


#line 269 "..\\user\\types.h"
#line 1 "..\\user\\hid_transfer.h"



 
 
 
 



 
#line 18 "..\\user\\hid_transfer.h"

 




 




 
 





#line 46 "..\\user\\hid_transfer.h"

 



 







void HID_Init(void);
void HID_ClassRequest(void);
 
 
 


 
 
 
void UsbRecvPolling(void);
void UsbRecvUidAes(void);
void EP3_Handler(void);
 
 
 





#line 270 "..\\user\\types.h"
#line 1 "..\\user\\aes.h"



void AesEncrypt(unsigned char *blk,unsigned char *key,int Nr);
void Contrary_AesEncrypt(unsigned char *blk,unsigned char *key,int Nr);
void ScheduleKey(unsigned char *inkey, unsigned char *outkey,int Nk,int Nr);



#line 271 "..\\user\\types.h"
 
 
 






#line 2 "..\\user\\linux_command.c"

 
 
 



typedef struct
{
	u8 data[50];
	u8 len;
}linux_recv_queue_t;
typedef struct
{
	linux_recv_queue_t recv_queue[100];
	u8 revcnt;
	u8 find_step;
	u8 write;
	u8 read;
}linux_recv_packet_t;
static linux_recv_packet_t linux_recv_packet;





void LinuxUSARTInit(void)
{
	SYS_UnlockReg();

	linux_recv_packet.find_step = 0x00;
	linux_recv_packet.read = 0;
	linux_recv_packet.write = 0;
	
	CLK_EnableModuleClock(((((1) & 0x03) << 30)|(((17) & 0x1f) << 0)| (((1) & 0x03) << 28)|(((3) & 0x07) << 25)|(((24) & 0x1f) << 20)| (((0) & 0x03) << 18)|(((0x0F) & 0xff) << 10)|(((8) & 0x1f) << 5)));

    CLK_SetModuleClock(((((1) & 0x03) << 30)|(((17) & 0x1f) << 0)| (((1) & 0x03) << 28)|(((3) & 0x07) << 25)|(((24) & 0x1f) << 20)| (((0) & 0x03) << 18)|(((0x0F) & 0xff) << 10)|(((8) & 0x1f) << 5)), (0x3UL<<24), (((1)-1) << 8));

	

	((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->GPB_MFP  &= ~((1UL<<4) | (1UL<<5));
    ((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->GPB_MFP  |= ((1UL<<4) | (1UL<<5));
	((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->ALT_MFP1 &= ~(0 | 0);
    ((GCR_T *) ((( uint32_t)0x50000000) + 0x00000))->ALT_MFP1 |= 0| 0;

	SYS_ResetModule(((0x4<<24) | 17 ));

    UART_Open(((UART_T *) ((( uint32_t)0x40100000) + 0x50000)), 115200);

	NVIC_SetPriority(UART1_IRQn, 0);
	
	UART_EnableInt(((UART_T *) ((( uint32_t)0x40100000) + 0x50000)), (1ul << 0));

	SYS_LockReg();
}

void UART1_IRQHandler(void)
{
    u8 u8InChar = 0xFF;
    u32 u32IntSts = ((UART_T *) ((( uint32_t)0x40100000) + 0x50000))->ISR;

    if(u32IntSts & (1ul << 8))
    {
        while((((((UART_T *) ((( uint32_t)0x40100000) + 0x50000)))->ISR & (1ul << 0))>>0))
        {
             
            u8InChar = ((((UART_T *) ((( uint32_t)0x40100000) + 0x50000)))->RBR);

            switch(linux_recv_packet.find_step)
			{
				case 0x00:
							if(u8InChar == 0x5A)
								linux_recv_packet.find_step = 0x01;
							break;
				case 0x01:
							if(u8InChar == 0xA5)
								linux_recv_packet.find_step = 0x02;
							else
								linux_recv_packet.find_step = 0x00;
							break;
				case 0x02:
							if(u8InChar < 1 || u8InChar >= 50)
							{
								linux_recv_packet.find_step = 0x00;
							}
							else
							{
								linux_recv_packet.recv_queue[linux_recv_packet.write].len = u8InChar;
								linux_recv_packet.revcnt = 0;
								linux_recv_packet.find_step = 0x03;
							}
							break;
				case 0x03:
							if(linux_recv_packet.revcnt < linux_recv_packet.recv_queue[linux_recv_packet.write].len)
							{
								linux_recv_packet.recv_queue[linux_recv_packet.write].data[linux_recv_packet.revcnt++] = u8InChar;
							}
							else
							{
								linux_recv_packet.find_step = 0x00;
								if(u8InChar == 0xFC)
								{
									linux_recv_packet.write = (linux_recv_packet.write + 1) % 100;
								}
							}
							break;
			}
        }
    }
}

void LinuxWriteByte(u8 * data, u8 len)
{
	u8  i = 0;
	
	for(i=0;i<len;i++)
	{
		while((((((UART_T *) ((( uint32_t)0x40100000) + 0x50000)))->FSR & (1ul << 23))>>23));              
		((((UART_T *) ((( uint32_t)0x40100000) + 0x50000)))->THR = (data[i]));
	}
}
 
 
 


 
 
 
void HostCommandSend(u8 cmd, u8 para1, u8 para2, u8 *data, u8 len)
{
	u8 head[7];
	u8 tail;

	head[0] = 0x5A;
	head[1] = 0xA5;
	head[2] = len + 4;
	head[3] = 0xAA;
	head[4] = cmd;
	head[5] = para1;
	head[6] = para2;
	tail	= 0xFC;
	
	LinuxWriteByte(head, 7);

	if(data != 0)
	{
		LinuxWriteByte(data, len);
	}

	LinuxWriteByte(&tail, 1);
}

void HostCommandSendEnterSystem(u8 in)
{
	u8 data[4];
	data[0] = info.master_unit;
	data[1] = !in;
	data[2] = info.battery;
	data[3] = wifi.rssi;
	LinuxCommandSend(0xAB, data, 4);
}

void HostDisplaySignInfo(void)
{	
	DwinSendResValue(24, sign.total);
	DwinSendResValue(26, sign.already_total);
	if(sign.total > sign.already_total)
		DwinSendResValue(28, sign.already_total*64/sign.total);
	else
		DwinSendResValue(28, 64);
}

static void RestoreMeetingModeDisplay(void)
{
	info.tft_display = TFT_DISPLAY_NORMAL;
	mic.display = 1;
	mic.use = (info.unit_opration == UNIT_OPRATION_MEETING_MODE || mic.mode != MIC_MODE_APPLY || info.master_unit) ? 1 : 0;
	if(info.time_statement != NO_STATEMENT && mic.status == MIC_STATUS_OPEN)
	{
		if(info.master_unit)
			DwinJumpTo(28);
		else
			DwinJumpTo(29);
	}
	else
	{
		if(info.master_unit)
			DwinJumpTo(1);
		else
			DwinJumpTo(13);
	}
	LedStaticControl(mic.status);
	DwinSetBrightness(0x01, info.light);
}

static void RestoreSignModeDisplay(void)
{
	info.tft_display = TFT_DISPLAY_MODE;
	mic.display = 0;
	mic.use = (mic.mode != MIC_MODE_APPLY || info.master_unit) ? 1 : 0;
	if(sign.already)
	{
		DwinJumpTo(19);
		LedStaticControl(LED_CONTROL_ALREADY_SIGN);
	}
	else
	{
		DwinJumpTo(18);
		LedStaticControl(LED_CONTROL_ALL_CLOSE);
	}
	DwinSetBrightness(0x02, info.light);
}

static void RestoreVoteModeDisplay(void)
{
	info.tft_display = TFT_DISPLAY_MODE;
	mic.display  	 = 1;
	mic.use          = (mic.mode != MIC_MODE_APPLY || info.master_unit) ? 1 : 0;
	if(vote.type <= BUTTON_3_VOTE_LAST_NOT_SIGN)
	{
		if(vote.result == 0x00)
			DwinJumpTo(21);
		else
			DwinJumpTo(36 + vote.result - 0x01);
	}
	else if(vote.type <= BUTTON_5_OPTION_LAST_NOT_SIGN)
	{
		if(vote.result == 0x00)
			DwinJumpTo(63);
		else
			DwinJumpTo(64 + vote.result - 0x01);
	}
	else if(vote.type <= BUTTON_5_LEVEL_LAST_NOT_SIGN)
	{
		if(vote.result == 0x00)
			DwinJumpTo(26);
		else
			DwinJumpTo(39 + vote.result - 0x01);
	}
	else
	{
		if(vote.result == 0x00)
			DwinJumpTo(22 + (vote.type - BUTTON_2_USER_OPTION_ONCE_SIGN) / 4);
		else
		{
			DwinJumpTo(44 + (vote.type - BUTTON_2_USER_OPTION_ONCE_SIGN) / 4);
			DwinSetString(69, vote.name[vote.result - 1], 20);
		}
	}
	LedStaticControl(mic.status);
	DwinSetBrightness(0x02, info.light);
}

static void RestoreVoteResultModeDisplay(void)
{
	info.tft_display = TFT_DISPLAY_MODE;
	mic.display  	 = 1;
	mic.use          = (mic.mode != MIC_MODE_APPLY || info.master_unit) ? 1 : 0;
	DwinJumpTo(32);
	LedStaticControl(mic.status);
	DwinSetBrightness(0x02, info.light);
}

static void OpenMicTimeStatementDisplay(void)
{
	if(info.time_statement != NO_STATEMENT && mic.status == MIC_STATUS_OPEN)
	{
		info.time_statement_count = info.time_statement_max;
		if(info.tft_display == TFT_DISPLAY_NORMAL)
		{
			if(info.master_unit)
				DwinJumpTo(28);
			else
				DwinJumpTo(29);
			
			DwinSendResValue(52, info.time_statement_count / 3600);
			DwinSendResValue(55, info.time_statement_count % 3600 / 60);
			DwinSendResValue(58, info.time_statement_count % 60);
		}
		{timer0_delay_1s_already = 0;timer0_delay_1s_count = 10000;};
	}
}

static u8 VoteJoinQuery(void)
{
	if(vote.enable)
	{
		if(vote.type % 2 == 0)
		{
			if(sign.already)
				return 1;
			else
				return 0;
		}
		else
		{
			return 1;
		}
	}
	else
		return 0;
}

void ExitMessageDisplay(void)
{
	if(dwin_cur_id == 52 || 
	   dwin_cur_id == 53 || 
	   dwin_cur_id == 54)
	{
		if(info.tft_display == TFT_DISPLAY_NORMAL)
		{
			if(info.master_unit)
				DwinJumpTo(1);
			else
				DwinJumpTo(13);
		}
		else if(info.tft_display == TFT_DISPLAY_REP_APPLY)
		{
			DwinJumpTo(15);
		}
	}
}

static void HostRecvCheck(u8 *data, u8 len)
{
	u8  cmd   		= data[0];
	u8  para1 		= data[1];
	u8  para2		= data[2];
	u8  *content	= &data[3];
	u16 u16_temp 	= 0;
	u8  u8_temp  	= 0;
	u8  detail[36];

	switch(cmd)
	{
		case 0:
			if(para1 == 0)
			{
				HostDisconnectDo();
			}
			else
			{
				SystemPowerDown();
			}
			break;
		case 2:
			if(para1 == 0x00)
			{
				info.host_connect 	= 1;
				info.linux_startup	= LINUX_STARTUP_FINISH;
				
				vol . mute_flag &= ~(0x0008);
				
				switch(content[0])
				{
					case UNIT_OPRATION_MEETING_MODE:
						info.unit_opration  = UNIT_OPRATION_MEETING_MODE;
						mic.mode   			= content[1];
						mic.open_total		= content[2];
						RestoreMeetingModeDisplay();
						break;
					case UNIT_OPRATION_SIGN_MODE:
						info.unit_opration  = UNIT_OPRATION_SIGN_MODE;						
						sign.total 			= ((u16)content[1] << 8) | content[2];
						sign.already_total 	= ((u16)content[3] << 8) | content[4];
						sign.already   		= content[5];
						mic.mode   			= content[6];
						mic.open_total 		= content[7];
						HostDisplaySignInfo();
						if(sign.enable)
							RestoreSignModeDisplay();
						else
							RestoreMeetingModeDisplay();
						break;
					case UNIT_OPRATION_VOTE_MODE:
						info.unit_opration  = UNIT_OPRATION_VOTE_MODE;
						vote.type			= content[1];
						mic.mode    		= content[2];
						mic.open_total  	= content[3];
						vote.result			= content[4];
						sign.already		= content[5];
						if(VoteJoinQuery())
							RestoreVoteModeDisplay();
						else
							RestoreMeetingModeDisplay();
						break;
					default:
						break;
				}
			}		
			break;
		case 46:
			if(info.unit_opration != UNIT_OPRATION_IDREPEAT_MODE)
			{
				info.unit_opration  = UNIT_OPRATION_IDREPEAT_MODE;
				info.host_connect   = 1;
				info.linux_startup	= LINUX_STARTUP_FINISH;
				mic.use				= 0;
				
				DwinSetBrightness(0x02, info.light);
				HardwordCloseMic(0, 0);
				LedStaticControl(LED_CONTROL_ALL_CLOSE);
				DwinJumpTo(50);
			}
			break;
		default:
			break;
	}

	if(info.host_connect)
	{
		switch(cmd)
		{
			case 10:
			case 5:
				switch(para1)
				{
					case 0x00:
						HardwordOpenMic(content[0], mic.display);
						OpenMicTimeStatementDisplay();
						break;
					case 0x01:
					case 0x04:
						DwinSetIcon(22, 2);
						break;
					case 0x03:
						if(mic.mode == MIC_MODE_APPLY)
						{
							DwinSetIcon(22, 6);
							mic.status = MIC_STATUS_APPLY;
						}
						else
						{
							DwinSetIcon(22, 5);
							mic.status = MIC_STATUS_WAIT;
						}
						
						if(mic.display)
							LedStaticControl(mic.status);
						break;
				}
				ExitMessageDisplay();
				break;
			case 7:
				if(para1 == 0x00)
				{
					HardwordOpenMic(content[0], mic.display);
					OpenMicTimeStatementDisplay();
				}
				else
				{
					HardwordCloseMic(0, mic.display);
					if(info.time_statement != NO_STATEMENT && info.tft_display == TFT_DISPLAY_NORMAL)
					{
						if(info.master_unit)
							DwinJumpTo(1);
						else
							DwinJumpTo(13);
					}
				}
				DwinSetBrightness(0x03, info.light);
				ExitMessageDisplay();
				break;
			case 40:
				if(info.unit_opration == UNIT_OPRATION_MEETING_MODE)
					u8_temp   = !mic.enable 	<< 1 |
								!sign.enable  	<< 3 |
								!vote.enable  	<< 4;
				else
					u8_temp   =  sign.already 	<< 0 |
								!mic.enable 	<< 1 |
								!sign.enable  	<< 3 |
								!vote.enable  	<< 4;
				detail[0] = info.battery;
				detail[1] = wifi.rssi;
				HostCommandSend(41, u8_temp, vote.result, detail, 2);
				break;
			case 47:
				HostDisconnectDo();
				break;
			case 19:
				if(para1 == 0)
				{
					sign.total = ((u16)content[0] << 8) | content[1];
					sign.already_total = ((u16)content[2] << 8) | content[3];

					HostDisplaySignInfo();

					if(info.unit_opration != UNIT_OPRATION_SIGN_MODE)
					{
						info.unit_opration = UNIT_OPRATION_SIGN_MODE;
						sign.already = 0;
						mic.use = (mic.mode != MIC_MODE_APPLY || info.master_unit) ? 1 : 0;
						
						if(sign.enable)
						{
							info.tft_display = TFT_DISPLAY_MODE;
							mic.display  	 = 0;
							
							DwinJumpTo(18);
							DwinSetBrightness(0x02, info.light);
							LedStaticControl(LED_CONTROL_ALL_CLOSE);
						}
						else
						{
							info.tft_display = TFT_DISPLAY_NORMAL;
							mic.display	 	 = 1;
						}
						
						if(mic.use == 0)
							HardwordCloseMic(0, mic.display);
					}
				}
				break;
			case 20:
				if(para1 == 0)
				{
					if(info.unit_opration == UNIT_OPRATION_SIGN_MODE)
						RestoreSignModeDisplay();
					sign.enable  = 1;
				}
				else
				{
					if(info.unit_opration == UNIT_OPRATION_SIGN_MODE)
						RestoreMeetingModeDisplay();
					sign.enable  = 0;
				}
				break;
			case 21:
				HostCommandSend(22, 0x00, 0x00, 0, 0);
				sign.already = 1;
				break;
			case 49:
				if(sign.enable && sign.already == 0)
				{
					sign.already_total += 1;
					HostDisplaySignInfo();
					DwinJumpTo(19);
					LedStaticControl(LED_CONTROL_ALREADY_SIGN);
				}
				sign.already = 1;
				break;
			case 14:
				if(para1 == 0)
				{
					if(info.fire_warning == 0)
					{
						info.fire_warning = 1;
						info.tft_display  = TFT_DISPLAY_MODE;
						mic.display  	  = 0;
						mic.use			  = 0;
						DwinSetBrightness(0x02, info.light);
						LedStaticControl(LED_CONTROL_ALL_CLOSE);
						DwinJumpTo(59);
					}
				}
				else
				{
					info.fire_warning = 0;		
					u8_temp = VoteJoinQuery();
					if(info.unit_opration == UNIT_OPRATION_MEETING_MODE ||
					  (info.unit_opration == UNIT_OPRATION_SIGN_MODE && sign.enable == 0) ||
					  (info.unit_opration == UNIT_OPRATION_VOTE_MODE && u8_temp == 0) || 
					  (info.unit_opration == UNIT_OPRATION_VOTE_RESULT_MODE && u8_temp == 0))
					{
						RestoreMeetingModeDisplay();
					}
					else if(info.unit_opration == UNIT_OPRATION_SIGN_MODE)
					{
						RestoreSignModeDisplay();
					}
					else if(info.unit_opration == UNIT_OPRATION_VOTE_MODE)
					{
						RestoreVoteModeDisplay();
					}
					else if(info.unit_opration == UNIT_OPRATION_VOTE_RESULT_MODE)
					{
						RestoreVoteResultModeDisplay();
					}
					else if(info.unit_opration == UNIT_OPRATION_SETID_MODE)
					{
						if(setid.already)
							LedStaticControl(LED_CONTROL_ALREADY_SETID);
						else
							LedStaticControl(LED_CONTROL_ALL_CLOSE);
						DwinJumpTo(30);
					}
					else if(info.unit_opration == UNIT_OPRATION_IDREPEAT_MODE)
					{
						LedStaticControl(LED_CONTROL_ALL_CLOSE);
						DwinJumpTo(50);
					}
				}
				break;
			case 44:
				u16_temp = ((u16)para1 << 8) | para2;

				if(info.unit_opration != UNIT_OPRATION_SETID_MODE)
				{
					info.unit_opration	 = UNIT_OPRATION_SETID_MODE;
					setid.current		 = u16_temp;
					setid.sucess    	 = 0;
					setid.already   	 = 0;
					mic.use				 = 0;

					DwinJumpTo(30);
					sprintf(detail, "W%03d", setid.current - 0x3000);
					DwinSetString(12, detail, 4);
					sprintf(detail, "W%03d", setid.local - 0x3000);
					DwinSetString(17, detail, 4);

					DwinSetBrightness(0x02, info.light);
					HardwordCloseMic(0, 0);
					LedStaticControl(LED_CONTROL_ALL_CLOSE);
				}

				if(setid.press)
				{
					setid.press = 0;
					if(u16_temp == setid.current + 1)
					{	
						setid.already = 1;
						setid.local = setid.current;
						sprintf(detail, "W%03d", setid.local - 0x3000);
						DwinSetString(291, detail, 4);

						setid.sucess++;
						
						detail[0] = setid.local >> 8;
						detail[1] = setid.local;
						LinuxCommandSend(0x5C, detail, 2);

						sprintf(detail, "W%03d", setid.local - 0x3000);
						DwinSetString(17, detail, 4);
					}
				}
				
				if(setid.current != u16_temp)
				{
					setid.current = u16_temp;
					sprintf(detail, "W%03d", setid.current - 0x3000);
					DwinSetString(12, detail, 4);
				}			
				break;
			case 3:
				info.unit_opration	= UNIT_OPRATION_MEETING_MODE;
				mic.mode    		= para1;
				mic.open_total  	= para2;
				
				RestoreMeetingModeDisplay();
				break;
			case 50:
				mic.mode    		= para1;
				mic.open_total  	= para2;
				if(info.tft_display != TFT_DISPLAY_MODE)
				{
					if(info.master_unit)
						DwinJumpTo(1);
					else
						DwinJumpTo(13);
				}
				DwinSetBrightness(0x03, info.light);
				HardwordCloseMic(0, mic.display);
				break;
			case 15:
			case 16:
				if(para1 == 0)
				{
					if(cmd == 15)
					{
						info.time_statement 	      = UP_STATEMENT;
						info.time_statement_max 	  = 0;
						DwinSendResValue(61, 1);
					}
					else
					{
						info.time_statement 	      = DOWN_STATEMENT;
						info.time_statement_max 	  = (u16)content[0] << 8 | content[1];
						DwinSendResValue(61, 0);
					}
					OpenMicTimeStatementDisplay();
				}
				else
				{
					info.time_statement = NO_STATEMENT;
					if(info.tft_display == TFT_DISPLAY_NORMAL)
					{
						if(info.master_unit)
							DwinJumpTo(1);
						else
							DwinJumpTo(13);
					}
				}
				DwinSetBrightness(0x03, info.light);
				break;
			case 25:
				if(para1 == 0x00)
				{
					info.unit_opration	 = UNIT_OPRATION_VOTE_MODE;
					vote.result	 		 = 0x00;
					vote.type		 	 = para2;
					if(VoteJoinQuery())
					{
						info.tft_display = TFT_DISPLAY_MODE;
						mic.display  	 = 1;
						DwinSetBrightness(0x02, info.light);
						if(vote.type <= BUTTON_3_VOTE_LAST_NOT_SIGN)
							DwinJumpTo(21);
						else if(vote.type <= BUTTON_5_OPTION_LAST_NOT_SIGN)
							DwinJumpTo(63);
						else if(vote.type <= BUTTON_5_LEVEL_LAST_NOT_SIGN)
							DwinJumpTo(26);
						else
							DwinJumpTo(22 + (vote.type - BUTTON_2_USER_OPTION_ONCE_SIGN) / 4);
					}
					else
					{
						info.tft_display = TFT_DISPLAY_NORMAL;
						mic.display	 	 = 1;
					}
				}
				else if(para1 == 0x01)
				{
					info.unit_opration = UNIT_OPRATION_VOTE_RESULT_MODE;
					DwinSendResValue(32, (u16)content[0] << 8 | content[1]);
					DwinSendResValue(34, (u16)content[2] << 8 | content[3]);
					DwinSendResValue(36, (u16)content[4] << 8 | content[5]);
					DwinSendResValue(38, ((u16)content[0] << 8 | content[1]) +
									((u16)content[2] << 8 | content[3]) +
									((u16)content[4] << 8 | content[5]));
					if(VoteJoinQuery())
						DwinJumpTo(32);
				}

				mic.use = (mic.mode != MIC_MODE_APPLY || info.master_unit) ? 1 : 0; 
				if(mic.use == 0)
					HardwordCloseMic(0, mic.display);
				break;
			case 29:
				if(para1 == 0)
				{
					vote.enable  = 1;
					if(VoteJoinQuery())
					{
						if(info.unit_opration == UNIT_OPRATION_VOTE_MODE)
						{
							RestoreVoteModeDisplay();
						}
						else if(info.unit_opration == UNIT_OPRATION_VOTE_RESULT_MODE)
						{
							RestoreVoteResultModeDisplay();
						}
					}
				}
				else
				{
					vote.enable  = 0;
					if(info.unit_opration == UNIT_OPRATION_VOTE_MODE || 
					   info.unit_opration == UNIT_OPRATION_VOTE_RESULT_MODE)
					{
						RestoreMeetingModeDisplay();
					}
				}
				break;
			case 51:
				u8_temp  = para1 - 1;
				memset(vote.name[u8_temp], 0, 20);
				memcpy(vote.name[u8_temp], content, len - 3);
				DwinSetString(90 + (111 - 90) * u8_temp, 
					vote.name[u8_temp], 20);
				break;
			case 43:
				if(info.tft_display != TFT_DISPLAY_MODE)
				{
					if(para1 == 0x01)
						DwinJumpTo(52);
					else
						DwinJumpTo(53);
					DwinSetBrightness(0x03, info.light);
				}
				break;
			case 42:
				if(para1 == 0x01)
				{
					memset(info.unit_name, 0, 16);
					memcpy(info.unit_name, content, len - 3);
					DwinSetString(228, info.unit_name, 16);
					DwinSetBrightness(0x03, info.light);
				}
				else if(para1 == 0x02)
				{
					if(info.tft_display != TFT_DISPLAY_MODE)
					{
						memset(detail, 0, 36);
						memcpy(detail, content, len - 3);
						DwinSetString(333, detail, 36);
						DwinJumpTo(54);
						DwinSetBrightness(0x03, info.light);
					}
				}
				break;
			case 11:
				if(info.master_unit)
				{
					if(para1 == 0x00)
					{
						DwinJumpTo(15);
						info.tft_display = TFT_DISPLAY_REP_APPLY;
					}
					else
					{
						if(info.time_statement != NO_STATEMENT && mic.status == MIC_STATUS_OPEN)
							DwinJumpTo(28);
						else
							DwinJumpTo(1);
						info.tft_display = TFT_DISPLAY_NORMAL;
					}
					DwinSetBrightness(0x03, info.light);
				}
				break;
			case 60:
				mic.v_sen = 310 - 2 * para1;
				DwinSetBrightness(0x03, info.light);
				break;
			case 61:
				if(info.master_unit == 0)
				{
					mic.nos_tmr = para1 * 100;
					VoiceModeNoSignalResetTimer();
					DwinSetBrightness(0x03, info.light);
				}
				break;
			default:
				break;
		}
	}
}
 
 
 

 
 
 
void LinuxCommandSend(u8 cmd, u8 *data, u8 len)
{
	u8 head[4];
	u8 tail;

	head[0] = 0x5A;
	head[1] = 0xA5;
	head[2] = len + 1;
	head[3] = cmd;
	tail    = 0xFC;
	
	LinuxWriteByte(head, 4);

	if(data != 0)
	{
		LinuxWriteByte(data, len);
	}

	LinuxWriteByte(&tail, 1);
}

static const u8 rssi_conv_list[5][2] =
{
	{65,  0},
	{75,  60},
	{80,  70},
	{90,  80},
	{100, 90},
};

u16 LinuxRecvPolling(void)
{
	u16  type;
	u8  *eff_data;
	u8   eff_data_len;
	u8	 dec[30];
	u8   u8_temp = 0;
	
	if(linux_recv_packet.read != linux_recv_packet.write)
	{
		type         = linux_recv_packet.recv_queue[linux_recv_packet.read].data[0];
		eff_data     = linux_recv_packet.recv_queue[linux_recv_packet.read].data + 1;
		eff_data_len = linux_recv_packet.recv_queue[linux_recv_packet.read].len  - 1;

		switch(type)
		{
			case 0x02:

				LinuxCommandSend(0x58, &mic.recv_ch, 1);

				LinuxCommandSend(0x5A, 0, 0);

				HostCommandSendEnterSystem(1);

				wifi.connect 		= 1;
				info.linux_startup	= LINUX_STARTUP_WAIT_HOST;
				info.overcount 		= 0;
				
				break;
			case 0x03:
				
				break;
			case 0x04:
				
				
				
				memcpy(wifi.mac, eff_data, 6);

				dec[0] = setid.local >> 8;
				dec[1] = setid.local;
				LinuxCommandSend(0x5C, dec, 2);
				
				break;
			case 0x06:
				
				dec[0] = 'M';
				GetComipleDate_to_ver(dec + 1);
				dec[9] = 'L';
				memcpy(dec + 10, eff_data, 8);
				memcpy(info.linux_ver, eff_data, 8);
				DwinSetString(249, dec, 18);
				
				break;
			case 0x07:		
				u8_temp = wifi.rssi;	
				while(eff_data[0] >= rssi_conv_list[u8_temp][0] && u8_temp < 4)u8_temp++;
				while(eff_data[0] <  rssi_conv_list[u8_temp][1] && u8_temp > 0)u8_temp--;
				if(wifi.rssi != u8_temp)
				{
					wifi.rssi = u8_temp;
					if(wifi.rssi == 0)
					{
						HostDisconnectDo();
						DwinJumpTo(71);
						HostCommandSendEnterSystem(0);
					}
					else
					{
						u8_temp = (u8_temp > 1) ? 0 : 1;
						if(u8_temp != wifi.low)
						{
							wifi.low = u8_temp;
							if(info.host_connect)
								HostCommandSend(48, info.battery, wifi.rssi, 0, 0);
						}
					}
					DwinSendResValue(6, wifi.rssi);
				}
				break;
			case 0x08:
				wifi.connect = 0;
				wifi.rssi	 = 0;
				HostDisconnectDo();
				DwinSendResValue(6, 0);
				DwinJumpTo(55);
				break;
			case 0x09:
				wifi.connect = 1;
				info.host_lost_count = 0;
				break;
			case 0x01:
				LinuxCommandSend(0x01, eff_data, eff_data_len);
				break;
			case 0xAC:
				if(wifi.rssi > 0)
				{
					HostRecvCheck(eff_data, eff_data_len);
					info.host_lost_count = 0;
				}
				break;
			case 0x0A:
				LinuxCommandSend(0x5D,   wifi.wpa.ssid, wifi.wpa.ssid_len);
				info.linux_startup 	= LINUX_STARTUP_WAIT_AP;
				info.overcount 		= 0;
				break;
			case 0x0B:
				LinuxCommandSend(0x5E, wifi.wpa.key, wifi.wpa.key_len);
				break;
			case 0x0C:
				DwinJumpTo(69);
				info.linux_startup = LINUX_STARTUP_NET_CARD_ERROR;
				break;
			default:
				
				break;
		}
		
		linux_recv_packet.read = (linux_recv_packet.read + 1) % 100;

		return type;
	}
	
	return 0x00;
}
 
 
 




