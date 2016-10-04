// Switch.h
// Sept. 14, 2016

#ifndef Time_h

void SysTick_Init2(uint32_t period);
void Timer3_Init(void(*task)(void), unsigned long period);
void Timer0A_Init(void(*task)(void), uint32_t period);
int32_t getFlag(void);
void Timer1_Init(void(*task)(void), uint32_t period);
void Timer2_Init(void(*task)(void), unsigned long period);

#endif
