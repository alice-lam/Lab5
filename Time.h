// Switch.h
// Sept. 14, 2016

#ifndef Time_h

void SysTick_Init2(uint32_t period);
void Timer3_Init(void(*task)(void), unsigned long period);		//Enveloping
void Timer0A_Init(void(*task)(void), uint32_t period);			//Melody
int32_t getFlag(void);
void Timer1_Init(void(*task)(void), uint32_t period);			//Harmony 1
void Timer2_Init(void(*task)(void), unsigned long period);		//next Note
void Timer4_Init(void(*task)(void), unsigned long period);		//Harmony 2
void Timer5_Init(void(*task)(void), unsigned long period);		//Harmony 3

#endif
