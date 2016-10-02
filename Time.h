// Switch.h
// Sept. 14, 2016

#ifndef Switch_h

void Buttons_Init(void);
void EdgeCounter_Init(void);
void Buttons_Input(void);
uint32_t Button_Pressed(void);
void DelayWait10ms(uint32_t n);
void GPIOPortE_Handler(void);
void Buttons_Handler(void); 


#endif