#include "types.h"

void SysTimerDelay(u32 us)
{
	SysTick->LOAD = us * 11; /* using 22MHz cpu clock*/
    SysTick->VAL   =  (0x00);
    SysTick->CTRL = SysTick->CTRL | (1<<SysTick_CTRL_ENABLE_Pos);//using cpu clock
    /* Waiting for down-count to zero */
    while((SysTick->CTRL & (1 << 16)) == 0);
}

void delay_us(u32 us)
{
	SysTimerDelay(us);
}

void delay_ms(u32 ms)
{
	while(ms)
	{
		SysTimerDelay(1000);
		--ms;
	}
}


