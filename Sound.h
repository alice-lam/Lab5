// Song.h
// Runs on TM4C123
#ifndef MUSIC_H
#define MUSIC_H 1

#include <stdint.h>

// if desired interrupt frequency is f, Timer0A_Init parameter is busfrequency/f
#define F16HZ (80000000/16)
#define F20KHZ (80000000/20000)
#define F64HZ	(80000000/64)
#define ENVELOPE_SCALE 100000

#define Whole 16
#define Half 8
#define Quarter 4
#define Eighth 2
#define Sixteenth 1

#define C
#define D
#define E
#define F
#define G
#define A
#define B

typedef struct {
	uint16_t pitch;    //frequency for note
	uint16_t duration; //number of beats for note
	//instrument
} Note;

typedef struct {
	uint16_t tempo;    //beats per minute
	Note *notes;       //all of the notes in the song
} Song;

void Song_PlayInit(int song);
void Song_PlayHandler(void);

#endif