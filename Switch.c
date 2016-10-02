//Switch.c

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Switch.h"
#include "Time.h"
#include "boolean.h"
#define DELAY10MS 160000
bool debounce[4];
void EnableInterrupts(void);  // Enable interrupts
void DisableInterrupts(void); // Disable interrupts

void EnableButtonInterrupts(void) {
	NVIC_EN0_R = 1 << (INT_GPIOC - 16);
	NVIC_EN0_R = 1 << (INT_GPIOE - 16);
	NVIC_EN0_R = 1 << (INT_GPIOF - 16);
}

void DisableButtonInterrupts(void) {
	NVIC_DIS0_R = 1 << (INT_GPIOC - 16);
	NVIC_DIS0_R = 1 << (INT_GPIOE - 16);
	NVIC_DIS0_R = 1 << (INT_GPIOF - 16);
}

volatile unsigned char SW1, SW2, SW3, SW4;
volatile unsigned int SWITCH; 

void Buttons_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x10;        // 1) activate clock for Port E
	SW1 = 0;
	SW2 = 0;
	SW3 = 0;
	SW4 = 0;
                                    // 2) no need to unlock PE0-3
  GPIO_PORTE_DIR_R &= ~0x0F;        // 3) set direction to output
	GPIO_PORTE_DEN_R |= 0x0F;         // 4) enable digital port
	GPIO_PORTE_IS_R &= ~0x0F;
	GPIO_PORTE_IBE_R &= ~0x0F;    		//    PE0-3 is not both edges
	GPIO_PORTE_IEV_R &= ~0x0F;    		//    PE0-3 falling edge event
	GPIO_PORTE_ICR_R = 0x0F;     		  // (5) clear flag0-3
	GPIO_PORTE_IM_R |= 0x0F;      		// (6) arm interrupt on PE0-3
	NVIC_PRI0_R = (NVIC_PRI0_R&0x00FFFF)|0x00A00000; // (7) priority 5
  NVIC_EN0_R = 0x00000010;      		// (8) enable interrupt 4 in NVIC
  EnableInterrupts();           		// (9) Clears the I bit
	
}
void DelayWait10ms(uint32_t n){
  uint32_t volatile time;
  while(n){
    time = 727240*2/91;  // 10msec
    while(time){
      time--;
    }
    n--;
  }
}

void GPIOPortE_Handler(void){
	SWITCH = 0x00;
	if(GPIO_PORTE_RIS_R & 0x01){
			GPIO_PORTE_ICR_R = 0x01;
			SW1=1;
			SWITCH = 0x01;
			DelayWait10ms(1);
	}
	if(GPIO_PORTE_RIS_R & 0x02){
			GPIO_PORTE_ICR_R = 0x02;
			SW2=1;
			SWITCH = 0x02;
			DelayWait10ms(1);
		}
	if(GPIO_PORTE_RIS_R & 0x04){
			GPIO_PORTE_ICR_R = 0x04;
			SW3=1;
			SWITCH = 0x04;
			DelayWait10ms(1);
		}
	if(GPIO_PORTE_RIS_R & 0x08){
			GPIO_PORTE_ICR_R = 0x08;
			SW4=1;
			SWITCH = 0x08;
			DelayWait10ms(1);
		}
}

uint32_t Button_Pressed(void){
	int32_t SW;
	SW=SWITCH;
	SWITCH=0;
return SW;
}
    

void Buttons_Input(void) {
	int32_t data = GPIO_PORTE_DATA_R;
	
	if((data & 0x01) != 0)
		debounce[0] = (data & 0x01)*DELAY10MS;
	if((data & 0x02) != 0)
		debounce[1] = ((data & 0x2) >> 1)*DELAY10MS;
	if((data & 0x04) != 0)
		debounce[2] = ((data & 0x4) >> 2)*DELAY10MS;
	if((data & 0x08) != 0)
		debounce[3] = ((data & 0x8) >> 3)*DELAY10MS;
}

int32_t Buttons_Pressed(uint32_t button) {
	if(button == 0){ return 0;}
	if(button == 1){ return 1;}
	if(button == 2){ return 2;}
	if(button == 3){ return 3;}
	else return -1;
}

void Buttons_Handler(void) {
	Buttons_Input();
	for(uint32_t i = 0; i < 4; i += 1) {
		if(debounce[i] > 0) {
			debounce[i] -= 1;
			if(debounce[i] == 0) {
				Buttons_Pressed(i);
			}
		}
	}
}
