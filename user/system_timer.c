#include "types.h"


void SystemTimer0Init(void)
{
	SYS_UnlockReg();
	CLK->CLKSEL1 |= CLK_CLKSEL1_TMR0_S_Msk;//use 22M
	CLK->APBCLK  |= CLK_APBCLK_TMR0_EN_Msk; 
	TIMER0->TCSR  = 0;//disable timer
	TIMER0->TISR  = 0x3;//write 1 to clear for safty 
	TIMER0->TCMPR = 100;//100us
	TIMER0->TCSR  = (1    << TIMER_TCSR_IE_Pos)       | //enable IE
					(21   << TIMER_TCSR_PRESCALE_Pos) |	// pre-scale = 21+1, clock = 1M
				    (0x01 << TIMER_TCSR_MODE_Pos)     | // period mode
				    (1    << TIMER_TCSR_CEN_Pos );      //count enable
	NVIC_SetPriority(TMR0_IRQn, 2);
	NVIC_EnableIRQ(TMR0_IRQn);
	SYS_LockReg();
}


u16	timer0_delay_10ms_count = 0;
u16 timer0_delay_1ms_count  = 0;
u16 timer0_delay_1s_count   = 0;
u8	timer0_delay_1s_already = FALSE;
u16  timer0_10ms_flag = 0;
u16  timer0_1s_flag = 0;
void TMR0_IRQHandler(void)
{
	if(timer0_delay_10ms_count)
		timer0_delay_10ms_count--;

	if(timer0_delay_1ms_count)
		timer0_delay_1ms_count--;

	if(timer0_delay_1s_count)
		timer0_delay_1s_count--;
	else
	{
		timer0_delay_1s_count   = TIMER0_DELAY_1S;
		timer0_delay_1s_already = TRUE; 
	}
	
	TIMER0->TISR = 1 << 0; 
}



