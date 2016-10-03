// Switch.h
// Sept. 14, 2016

#ifndef Time_h



void Buttons_Init(void);
void EdgeCounter_Init(void);
void Buttons_Input(void);
uint32_t Button_Pressed(void);
void DelayWait10ms(uint32_t n);
void GPIOPortE_Handler(void);
void Buttons_Handler(void); 
void SysTick_Init2(uint32_t period);
void Timer3_Init(void(*task)(void), unsigned long period);
int32_t getFlag(void);
void Timer0A_Init(void(*task)(void), uint32_t period);
void Timer1_Init(void(*task)(void), uint32_t period);
void Timer2_Init(void(*task)(void), unsigned long period);
#endif
