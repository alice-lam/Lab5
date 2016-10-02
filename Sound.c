//Sound.c
//Alice Lam and Kinan Hernandez

#include "DAC.h"
#include "Sound.h"
#include <math.h>

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

uint32_t noteIndex = 0;
uint32_t beatIndex = 0;
Song currentSong;

void Song_PlayInit(Song song) {
	currentSong = song;
	noteIndex = 0;
	beatIndex = 0;
}
Note* Song_CurrentNote() {
	return &currentSong.notes[noteIndex];
}

void Song_PlayHandler(void){
	Note currentNote = *Song_CurrentNote();
	beatIndex += 1;
	if(beatIndex >= currentNote.duration * 2) {
		noteIndex += 1;
		beatIndex = 0;
	}
}
uint16_t Instrument_CurrentVoltage(uint32_t Index) {
	return Wave[Index % 64];
}

int Song_EnvelopeScale(int currentMill, int totalMill){ //returns scale*1000
	if(currentMill < totalMill/5){
		double scale = 8.0/totalMill;
		int arg = scale * (currentMill -90);
		double value = sin(arg);
		double result = (1.1+0.8*value)*1000;
		if(result>=1.0)
			return 1000;
		return result;
	}
	else{
		int fourFifths = totalMill*4/5;
		int oneFifth = totalMill - fourFifths;
		double c = fourFifths/1.897;
		double x = (oneFifth-currentMill)/c;
		double value = exp(x);
		int ret = value*1000;
		return ret;
	}
}

Note maryhadalamb[] = {
	
	{E0, Quarter},
	{D0, Quarter},
	{C0, Quarter},
	{D0, Quarter},
	{E0, Quarter},
	{E0, Quarter},
	{E0, Half},
	{D0, Quarter},
	{D0, Quarter},
	{D0, Half},
	{E0, Quarter},
	{G0, Quarter},
	{G0, Half}
	
};

Notes HotLine[38] = {
{D5,	EI,		0,		1}, 
{D5,	EI,		EI,		1},
{A3,	DHA,	0,		2},
{D5,	EI,		EI,		1},
{F5,	SI,		EI,		1},
{E5,	SI,		SI,		1},
{D5,	SI,		SI,		1},
{C5,	SQ,		SI,		1},
{D5,	EI,		90,		1},
{A3,	EI,		0,		2},
{A4,	DEI,	EI,		1},
{A3,	QU,		0,		2},
{G4,	SI,		DEI,	1},
{G4,	EI,		DEI,	1},
{BF3,	QU,		0,		2},
{G4,	DEI,	EI,		1},
{F4,	SI,		DEI,	1},
{A3,	HA,		78,		2},
{BF3,	DHA,	HA,		2},
{D5,	EI,		168,	1},
{A3,	EI,		0,		2},
{D5,	EI,		EI,		1},
{D4,	EI,		0,		2},
{D5,	EI,		EI,		1},
{D4,	EI,		0,		2},
{F5,	SI,		EI,		1},
{E5,	SI,		SI,		1},
{D4,	QU,		0,		2},
{D5,	SI,		SI,		1},
{C5,	SI,		SI,		1},
{E5,	QU,		SI,		1},
{BF4,	DHA,	0,		2},
{C5,	QU,		QU,		1},
{F4,	EI,		HA,		2},
{F4,	EI,		EI,		2},
{F4,	EI,		QU,		2},
{F4,	EI,		QU,		2},
{0,		0,		0,		0}
};
