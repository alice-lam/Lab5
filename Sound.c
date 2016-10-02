//Sound.c
//Alice Lam and Kinan Hernandez

#include "DAC.h"
#include "Sound.h"

const unsigned short Wave[64] = {
	2048,2224,2399,2571,2737,2897,3048,3190,3321,3439,3545,3635,3711,3770,3813,3839,3848,3839,3813,3770,
	3711,3635,3545,3439,3321,3190,3048,2897,2737,2571,2399,2224,2048,1872,1697,1525,1359,1199,1048,906,775,
	657,551,461,385,326,283,257,248,257,283,326,385,461,551,657,775,906,1048,1199,1359,1525,1697,1872
};

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