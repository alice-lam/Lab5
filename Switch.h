// Switch.h
// Runs on TM4C123
// Switches Driver


#include <stdbool.h>

/** The different kinds of buttons we can press. */
typedef enum {
	Play,
	Stop,
	Rewind
} Button;

/**
 * Initialize the switches on the correct port, the pins, and the
 * interrupts necessary to handle button presses.
 */


void Buttons_Init(void);
void EdgeCounter_Init(void);
void Buttons_Input(void);
uint32_t Button_Pressed(void);
void DelayWait10ms(uint32_t n);
void GPIOPortE_Handler(void);
void Buttons_Handler(void); 

