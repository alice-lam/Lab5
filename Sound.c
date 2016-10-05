//Sound.c
//Alice Lam and Kinan Hernandez

#include "DAC.h"
#include "Sound.h"
#include "Time.h"
#include "..//inc//tm4c123gh6pm.h"
#include <math.h>

#include <stdio.h>
#include <stdint.h>

#define CURRENT	1
#define NEXT	0

const unsigned short Wave[64] = {
	2048,2224,2399,2571,2737,2897,3048,3190,3321,3439,3545,3635,3711,3770,3813,3839,3848,3839,3813,3770,
	3711,3635,3545,3439,3321,3190,3048,2897,2737,2571,2399,2224,2048,1872,1697,1525,1359,1199,1048,906,775,
	657,551,461,385,326,283,257,248,257,283,326,385,461,551,657,775,906,1048,1199,1359,1525,1697,1872
};
unsigned short SinTable[256] = {  // must be in RAM, can't DMA out of ROM
  2048,2097,2146,2195,2244,2293,2341,2390,2438,2486,2534,2581,2629,2675,2722,2768,
  2813,2858,2903,2947,2991,3034,3076,3118,3159,3200,3239,3278,3317,3354,3391,3427,
  3462,3496,3530,3562,3594,3625,3654,3683,3711,3738,3763,3788,3812,3834,3856,3876,
  3896,3914,3931,3947,3962,3976,3988,3999,4010,4019,4026,4033,4038,4043,4046,4047,
  4048,4047,4046,4043,4038,4033,4026,4019,4010,3999,3988,3976,3962,3947,3931,3914,
  3896,3876,3856,3834,3812,3788,3763,3738,3711,3683,3654,3625,3594,3562,3530,3496,
  3462,3427,3391,3354,3317,3278,3239,3200,3159,3118,3076,3034,2991,2947,2903,2858,
  2813,2768,2722,2675,2629,2581,2534,2486,2438,2390,2341,2293,2244,2195,2146,2097,
  2048,1999,1950,1901,1852,1803,1755,1706,1658,1610,1562,1515,1467,1421,1374,1328,
  1283,1238,1193,1149,1105,1062,1020,978,937,896,857,818,779,742,705,669,634,600,
  566,534,502,471,442,413,385,358,333,308,284,262,240,220,200,182,165,149,134,120,
  108,97,86,77,70,63,58,53,50,49,48,49,50,53,58,63,70,77,86,97,108,120,134,149,165,
  182,200,220,240,262,284,308,333,358,385,413,442,471,502,534,566,600,634,669,705,
  742,779,818,857,896,937,978,1020,1062,1105,1149,1193,1238,1283,1328,1374,1421,
  1467,1515,1562,1610,1658,1706,1755,1803,1852,1901,1950,1999};
  
 Notes HotLine[86] = {
{D6,	EI,		EI,		1}, 
{D6,	EI,		EI,		1},
{A4,	DHA,	0,		2},
{D6,	EI,		EI,		1},
{F6,	EI,		EI,		1},
{E6,	EI,		EI,		1},
{D6,	EI,		EI,		1},
{C6,	DQU,	EI,		1},
//2
{D6,	EI,		90,		1},

{A4,	EI,		0,		2},
{A5,	DEI,	EI,		1},
{A4,	QU,		0,		2},
{G5,	SI,		DEI,	1},
{G5,	EI,		DEI,	1},
{BF4,	QU,		0,		2},
{G5,	DEI,	EI,		1},
{F5,	SI,		DEI,	1},

//{C7,	HA,		78,		2}, //a4
//{BF4,	DHA,	HA,		2},

{D6,	EI,		168,	1},  //time till 168
{A4,	EI,		0,		2},
{D6,	EI,		EI,		1},
{D5,	EI,		0,		2},
{D6,	EI,		EI,		1},
{D5,	EI,		0,		2},
{F6,	EI,		EI,		1},
{E6,	EI,		EI,		1},
{D5,	QU,		0,		2},
{D6,	EI,		EI,		1},
{C6,	EI,		EI,		1},
{E6,	QU,		EI,		1},
{BF5,	DHA,	0,		2},
{C6,	QU,		QU,		1},
{F5,	EI,		HA,		2},
{F5,	EI,		EI,		2},
{F5,	EI,		QU,		2},
{F5,	EI,		QU,		2},
{1,		QU,		QU,		2},
{F6,	EI,		120,		1},
{E6,	EI,		EI,		1},
{D6,	EI,		EI,		1},
{C6,	EI,		EI,		1},

{E6,	HA,		EI,		1},
{C6,	HA,		HA,		1},
//
{A5,	QU,		HA,		1},
{F6,	EI,		HA,		1},
{E6,	EI,		EI,		1},
{D6,	EI,		EI,		1},
{C6,	EI,		EI,		1},
//p2
{E6,	QU,		EI,		1},
{C6,	QU,		QU,		1},

{F6,	EI,		120,		1},
{E6,	EI,		EI,		1},
{D6,	EI,		EI,		1},
{C6,	EI,		EI,		1},
{E6,	HA,		EI,		1},
{C6,	HA,		HA,		1},
//HLB
{A5,	QU,		HA,		1},
{F6,	EI,		DQU,	1},
{C7,	EI,		EI,		1},
{C7,	EI,		EI,		1},
{A6,	EI,		EI,		1},
{A6,	EI,		EI,		1},
//
{C7,	EI,		EI,		1},
{C7,	EI,		EI,		1},
{D7,	QU,		EI,		1},
//
{F6,	EI,		120,	1},
{A6,	EI,		EI,		1},
{G6,	EI,		EI,		1},
{F6,	EI,		EI,		1},
{G6,	EI,		EI,		1},
{G6,	EI,		EI,		1},
{A6,	QU,		EI,		1},
//
{C7,	EI,		120,		1},
{C7,	EI,		EI,		1},
{C7,	EI,		EI,		1},
{A6,	EI,		EI,		1},
{C7,	EI,		EI,		1},
{C7,	EI,		EI,		1},
{D7,	QU,		EI,		1},
//
{F6,	EI,		120,	1},
{A6,	EI,		EI,		1},
{G6,	EI,		EI,		1},
{F6,	EI,		EI,		1},
{G6,	EI,		EI,		1},
{G6,	EI,		EI,		1},
{A6,	QU,		EI,		1},

{A5,	QU,		HA,		1},
};

Song Hot = {
	150,
	86,
	HotLine
};

uint32_t harmIndex = 0;
uint32_t meloIndex = 0;	
int harmDuration = 0;
int meloDuration = 0;
int32_t noteIndex = 0;

int meloStart;
int melody;
int harmStart;
int harmony;

uint32_t tick;	//one of the 96 divisions

Song* currentSong;
	
void nextNoteHandler(){
	Notes next = getNote(CURRENT);					//get the next note to play in the song
	Notes future = getNote(NEXT);					//get the future note in the song and increment index
	if(next.duration==0){
		TIMER0_CTL_R=0x0;
		TIMER1_CTL_R=0x0;
		TIMER2_CTL_R=0x0;
		return;
	}
	
	harmIndex%=256;
	harmStart=harmIndex;
	meloIndex%=256;
	meloStart=meloIndex;
	
	// Channel Select
	if (future.timetill == 0){				// if both, harmony and melody will need to be updated. 
		int harmFreq = future.pitch;
		int melFreq = next.pitch;
		harmDuration = (future.duration)*tick*18/harmFreq;
		meloDuration = (next.duration)*tick*18/melFreq;	//clock cycles // *20 =ns
		TIMER0_TAILR_R = (80000000/256)/melFreq;
		TIMER1_TAILR_R = (80000000/256)/harmFreq;
		future = getNote(NEXT);
	}
	else if (next.channel == 1){		// if not both then pick either mel or harm based on channel. 
		int melFreq = next.pitch;
		TIMER0_TAILR_R = (80000000/256)/melFreq;
		meloDuration = (next.duration)*tick*18/melFreq;
	}else if(next.channel == 2){
		int harmFreq = next.pitch;
		TIMER1_TAILR_R = (80000000/256)/harmFreq;
		harmDuration = (next.duration)*tick*18/harmFreq;
	}
	TIMER2_TAILR_R = future.timetill*tick;			//set systick timer to 1/16 note duration
}
	
void Song_PlayInit() {
	currentSong = &Hot;
	tick = (60000000000/((*currentSong).tempo*24))/20;
	noteIndex = 0;			//current note in song
	harmIndex = 0;
	meloIndex = 0;	
	Timer2_Init(&nextNoteHandler,Hot.notes[0].timetill*tick);
}


int32_t getTable(int index){
	return SinTable[index%256];
}

void MHandler(void){
	int temp = (meloIndex-meloStart);
	
	if(temp<=meloDuration){
		meloIndex = meloIndex+1;
		melody = getTable(meloIndex);
	}
	else{
		melody=0;
	}
	
	//scale = Song_EnvelopeScale(temp,total,scale);
	//melody *= scale;
	//melody /=10000;
	DAC_Output((melody+harmony)/2);
	//DAC_Output((melody));
}

void HHandler(void){
	int temp = (harmIndex-harmStart);
	int total = harmDuration;
	
	if(temp<=total){
		harmIndex = harmIndex+1;
		harmony = getTable(harmIndex);
	}
	else{
		harmony=0;
	}
	//harmony = getHarm()*Song_EnvelopeScale(elapsed,harmDuration,1)/1000;
	
	//scale = Song_EnvelopeScale(temp,total,scale);
	//harmony *= scale;
	//harmony /=10000;
	DAC_Output((melody+harmony)/2);
	//DAC_Output((melody));
}

int envelopIndex;
int scale;
void Envelope(){
	envelopIndex=(envelopIndex+1)%80000;
	int envelope = SinTable[envelopIndex%256];
	scale = Song_EnvelopeScale(envelopIndex,80000,scale);
	envelope*=scale;
	envelope/=100;
	DAC_Output(envelope);
}

int Song_EnvelopeScale(int currentMill, int totalMill,int scale){ //returns scale*100 based on completion perecentage of Note
	return 100;
	/*if(currentMill < totalMill/5){
		scale+=100;
		if(scale>=10000)
			return 10000;
	}
	else{
		scale--;
		if(scale<=5000)
			return 5000;
	}
	return scale;*/
	/*if(currentMill < totalMill/5){
		double scale = 8.0/totalMill;
		int arg = scale * (currentMill - 90);
		double value = sin(arg);
		double result = (.4+value)*100;
		if(result>=100.0)
			return 100;
		return result;
	}
	else{
		int fourFifths = totalMill*4/5;
		int oneFifth = totalMill - fourFifths;
		double c = fourFifths/1.897;
		double x = (oneFifth-currentMill)/c;
		double value = exp(x);
		int ret = value*100;
		return ret;
	}*/
}

Notes getNote(int32_t peak){
	if (!peak){
		noteIndex++;
	}
	if(noteIndex<=(*currentSong).numNotes){
		return (*currentSong).notes[noteIndex];
	}
	Notes n = {1,	0,		HA,		1};
	return n;
}
