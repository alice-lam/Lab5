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
void Switch_Init(void);

/**
 * Return whether or not the request button is pressed.
 */
bool Switch_Pressed(Button buttonToCheck);