// PeriodicTimer0AInts.c
// Runs on LM4F120/TM4C123
// Use Timer0A in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6
 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// oscilloscope or LED connected to PF3-1 for period measurement
// When using the color wheel, the blue LED on PF2 is on for four
// consecutive interrupts then off for four consecutive interrupts.
// Blue is off for: dark, red, yellow, green
// Blue is on for: light blue, blue, purple, white
// Therefore, the frequency of the pulse measured on PF2 is 1/8 of
// the frequency of the Timer0A interrupts.

#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "PLL.h"
#include "Time.h"
#include "DAC.h"
#include "Switch.h"
#include "Sound.h"
#include "SysTick.h"
#include "Switch.h"

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define LEDS      (*((volatile uint32_t *)0x40025038))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08

#define PEAK 			1
#define NEXT			0
#define BOTH			3
#define CH1				1
#define CH2				2
//CHANGE SPEED OF SONG, set faster/slower TEMPO
#define TEMPO  180


uint32_t harmFreq;
uint32_t meloFreq;
uint32_t harmDur;
uint32_t meloDur;
//uint32_t flag = 0;
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void PortF_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x20;				// activate port F
	while((SYSCTL_PRGPIO_R&0x0020) == 0){};// ready?
	GPIO_PORTF_DIR_R |= 0x0E;					// make PF3-1 output (PF3-1 built-in LEDs)
	GPIO_PORTF_AFSEL_R &= ~0x0E;			// disable alt funct on PF3-1
	GPIO_PORTF_DEN_R |= 0x0E;					// enable digital I/O on PF3-1
																		// configure PF3-1 as GPIO
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
	GPIO_PORTF_AMSEL_R = 0;						// disable analog functionality on PF
}


void decodeNote(Notes n){
	// prestage next pitch
	// prestage next inturrpts
}

void playSin(void){
	
}
void Change_Notes(void){	//systick handler
//	TIMER1_TAILR_R = harmFreq - 1;
 // TIMER0_TAILR_R = meloFreq - 1;
}
void Rest_Melo(void){ 	 //timer2 handler
	TIMER0_TAILR_R = 0xffffffff;

}
void Rest_Harm(void){ 	//timer3 handler
	TIMER1_TAILR_R = 0xffffffff;
}

//const Song testSong = {90, maryhadalamb};
bool Play_mode = false;
void Pause(void);



//bool Play_mode = false;
void Pause(void);
extern Song HotLine;
	
//debug codes
int main(void){ 
	int check = 0;

	int k = 0;
	int timeOne = 0;
	int timeTwo = 0;
	int f=0;
	volatile uint32_t tmptime=0;
	int32_t times;
	int32_t channelSelect = 0;
	uint32_t tick = (60000000000/(TEMPO*24))/20;
	uint16_t done;
	Notes nextNote[3];
	Notes lastNote[3];
	// Initializations

	DisableInterrupts();
  PLL_Init(Bus50MHz);								// bus clock at 50 MHz
	PortF_Init();
  LEDS = 0;													// turn all LEDs off
	DAC_Init(0);
	Buttons_Init();

	//SysTick_Init2(0xffffffff);
	Song_PlayInit(HotLine);
	//SysTick_Init();
	//Timer0A_Init(&Song_PlayHandler, F20KHZ);	// initialize timer0A (20,000 Hz)
  //Timer0A_Init(&Song_PlayHandler, F16HZ);		// initialize timer0A (16 Hz)
	Timer0A_Init(&Melody_PlayHandler, 0xffffffff);		// initialize timer0A (16 Hz)
	Timer1_Init(&Harmony_PlayHandler, 0xffffffff);
	Timer2_Init(&Rest_Melo, 0xFFFFFFFF);
	Timer3_Init(&Rest_Harm, 0xFFFFFFFF);
  EnableInterrupts();
	
	//Song_PlayInit(testSong);
	//Pause();
	//check = Button_Pressed();
		
		
		//these checks only run once on startup? They aren't in the while loop?
		
		
		//Play
		if (check==0x01){
			Play_mode = true;
			NVIC_ST_CTRL_R = 0x07;
			TIMER0_CTL_R = 0x00000001;
			NVIC_ST_RELOAD_R = 500;
		}
		
		//Pause
		if (check==0x02){
			Play_mode = false;
			NVIC_ST_CTRL_R = 0;
			TIMER0_CTL_R = 0x00000000;
		}
		
		//Rewind
		if (check==0x04){
			//pause
			Play_mode = false;
			NVIC_ST_CTRL_R = 0;
			TIMER0_CTL_R = 0x00000000;
			//startover
			Song_PlayInit(HotLine);
		}			
	//Song init
	//nextNote[0] = getNote(NEXT);

	//TIMER0_TAILR_R = nextNote[0].pitch - 1;
	//TIMER0_TAILR_R = D5;
	//TIMER1_TAILR_R = nextNote[1].pitch - 1;
	//TIMER2_TAILR_R = (nextNote[0].duration)*tick - 1;
	//TIMER3_TAILR_R = (nextNote[1].duration)*tick - 1;
	//NVIC_ST_RELOAD_R = nextNote[2].timetill*tick - 1;
	
	//TIMER0_CTL_R = 0x00000001;
	//TIMER1_CTL_R = 0x00000001;
	//TIMER2_CTL_R = 0x00000001;
	//TIMER3_CTL_R = 0x00000001;
	//lastNote[1] = nextNote[0];
		
	// SONG PLAY LOOP	
  while(k<86){
		k++;
		nextNote[0] = getNote(NEXT);
		tmptime = (nextNote[0].timetill)*tick; 
		NVIC_ST_RELOAD_R = 6*tick;			//set systick timer to 1/16 note duration
		//NVIC_ST_RELOAD_R = (nextNote[0].timetill)*tick; // set timer for next event
		//TIMER2_TAILR_R = (nextNote[0].timetill)*tick; // set timer for next event
		NVIC_ST_CURRENT_R = 0; 					//enable systicktimer
		NVIC_ST_CTRL_R = 0x07;
		// Channel Select
		times = (nextNote[0].timetill)/6;
		nextNote[1] = getNote(PEAK);
		if (nextNote[1].timetill == 0){		// if both, harmony and melody will need to be updated. 
			nextNote[1] = getNote(NEXT);		// if both, melody is in nextNote[0] => CH1, harmony in nextNote[1] => CH2
			channelSelect = BOTH;
			harmFreq = nextNote[1].pitch;
		}
		if (nextNote[0].channel == 1){		// if not both then pick either mel or harm based on channel. 
				meloFreq = nextNote[0].pitch;
				channelSelect = CH1;
		}else if(nextNote[0].channel == 2){
				harmFreq = nextNote[0].pitch;
				channelSelect = CH2;
		}
		// check length of notes(testing, code can be deleted later)
		/*
		if(lastNote[channelSelect].duration == nextNote[0].timetill){
			//disable rests
			//TIMER2_CTL_R = 0x00000000;
			//TIMER3_CTL_R = 0x00000000;
		} else if(lastNote[channelSelect].duration < nextNote[0].timetill){
			//keep rests enabled
		}
		lastNote[channelSelect] = nextNote[0];
		lastNote[2] = nextNote[1];
		*/

		//wait for flag for next event/note to be played
		LEDS ^= RED;
		while(times){
			times--;								// times = number of 16th notes to wait, when times ==0, it is time to execute next note
			while(!f){							// triggers flag every 16th note
					f = getFlag();
			}
			f=0;
		}
		NVIC_ST_CTRL_R = 0x00;		//disable systick
		
		LEDS ^= RED;
		//Execute Event
		if (channelSelect == CH1){
				TIMER0_TAILR_R = nextNote[0].pitch;
				TIMER2_TAILR_R = (nextNote[0].duration)*tick - 10000;	//set rest
				//TIMER2_CTL_R = 0x00000001;
		}else if (channelSelect == CH2){
				TIMER1_TAILR_R = nextNote[0].pitch;
				TIMER3_TAILR_R = (nextNote[0].duration)*tick - 10000;	//set rest
				//TIMER3_CTL_R = 0x00000001;
		}else if (channelSelect == BOTH){
				TIMER0_TAILR_R = nextNote[0].pitch;
				TIMER1_TAILR_R = nextNote[1].pitch;
				TIMER2_TAILR_R = (nextNote[0].duration)*tick - 10000;	//set rest
				TIMER3_TAILR_R = (nextNote[1].duration)*tick - 10000;	//set rest
				//TIMER2_CTL_R = 0x00000001;
				//TIMER3_CTL_R = 0x00000001;
		}
		/*MORE TEST CODE THAT CAN BE DELETED LATER*/
		//	TIMER2_TAILR_R = (nextNote[0].duration)*tick - 1;	//set rest
		//	TIMER3_TAILR_R = (nextNote[1].duration)*tick - 1;	//set rest
		//	TIMER2_CTL_R = 0x00000001;
		//	TIMER3_CTL_R = 0x00000001;
		//	NVIC_ST_RELOAD_R = nextNote[2].timetill*tick - 1;	//ummmm
		
	
		//	LEDS ^= RED;
		//	for(int i = 0; i < 1000000; i += 1);
  }
	//END OF SONG PLAY LOOP
	while(1){
		LEDS ^= RED;
		for(int i = 0; i < 1000000; i += 1);	
	}
}
