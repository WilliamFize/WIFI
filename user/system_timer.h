#ifndef __SYSTEM_TIMER_H__
#define __SYSTEM_TIMER_H__

#define TIMER0_DELAY_1MS	10
#define TIMER0_DELAY_10MS	100
#define TIMER0_DELAY_1S		10000

void SystemTimer0Init(void);


extern u16 timer0_delay_10ms_count;
extern u16 timer0_delay_1ms_count;
extern u16 timer0_delay_1s_count;
extern u8  timer0_delay_1s_already;
extern u16  timer0_10ms_flag;
extern u16  timer0_1s_flag;
#define TIMER0_DELAY_1S_RESET() {timer0_delay_1s_already = FALSE;timer0_delay_1s_count = TIMER0_DELAY_1S;}


#endif



