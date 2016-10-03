// Song.h
// Runs on TM4C123
#ifndef Sound_H
#define Sound_H 1

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

#define WH 			96	// Whole
#define	QHE			84 	// Q + H + E
#define DHA			72	// Dotted Half Q + H
#define HA 			48 	// Half 
#define DQU			36	// dotted quarter
#define TQ			32 	// Triplet Quarter, 	
#define SQ    	30  // Sixteenth tied to quarter
#define QU 			24 	// Quarter 	
#define DEI			18	// Dotted Eigth (Eight + Sixteenth)
#define EI 			12 	// Eighth,  	
#define TE			8  	// Triplet Eighth 		
#define SI 			6		// Sixteenth 
#define SE			4		// Sextuplet		
#define TH 			3		// Thirty-Second


//#define EF7  628   // 1244.5 Hz
#define D7   333   // 1174.7 Hz
#define DF7  352   // 1108.7 Hz
#define C7   373   // 2093 Hz
#define B6   395   // 1975.5 Hz
#define BF6  419   // 1864.7 Hz
#define A6   444   // 1760 Hz
#define AF6  470   // 1661.2 Hz
#define G6   498   // 1568 Hz
#define GF6  528   // 1480 Hz
#define F6   559   // 1396.9 Hz
#define E6   593   // 1318.5 Hz
#define EF6  628   // 1244.5 Hz
#define D6   665   // 1174.7 Hz
#define DF6  705   // 1108.7 Hz
#define C6    747   // 1046.5 Hz
#define B5    791   // 987.8 Hz
#define BF5   838   // 932.3 Hz
#define A5   888   // 880 Hz
#define AF5   941   // 830.6 Hz
#define G5    997   // 784 Hz
#define GF5  1056   // 740 Hz
#define F5   1119   // 698.5 Hz
#define E5   1185   // 659.3 Hz
#define EF5  1256   // 622.3 Hz
#define D5   1330   // 587.3 Hz
#define DF5  1409   // 554.4 Hz
#define C5  1493   // 523.3 Hz
#define B4  1582   // 493.9 Hz
#define BF4 1676   // 466.2 Hz
#define A4  1776   // 440 Hz
#define AF4 1881   // 415.3 Hz
#define G4  1993   // 392 Hz
#define GF4 2112   // 370 Hz
#define F4  2237   // 349.2 Hz
#define E4  2370   // 329.6 Hz
#define EF4 2511   // 311.1 Hz
#define D4  2660   // 293.7 Hz
#define DF4 2819   // 277.2 Hz
#define C4  2986   // 261.6 Hz
#define B3  3164   // 246.9 Hz
#define BF3 3352   // 233.1 Hz
#define A3  3551   // 220 Hz
#define AF3 3762   // 207.7 Hz
#define G3  3986   // 196 Hz
#define GF3 4223   // 185 Hz
#define F3  4474   // 174.6 Hz
#define E3  4740   // 164.8 Hz
#define EF3 5022   // 155.6 Hz
#define D3  5321   // 146.8 Hz
#define DF3 5637   // 138.6 Hz
#define C3  5972   // 130.8 Hz



#define C0	262
#define D0	294
#define E0	330
#define F0	349
#define G0	392
#define A0	440
#define B0	494
#define C1	523

typedef struct {
	uint16_t pitch;    //frequency for note
	uint16_t duration; //number of beats for note
	//instrument
} Note;

typedef struct {
	uint16_t pitch;    			// frequency for note
	uint16_t duration;	  	// number of beats for note
	uint16_t timetill;      // number of beats until execution
	uint16_t channel;				// 1 or 2
} Notes;

typedef struct {
	uint16_t tempo;    //beats per minute
	Notes* notes;       //all of the notes in the song
} Song;

void Song_PlayInit(Song song);
//void Song_PlayHandler(void);
void Melody_PlayHandler(void);
void Harmony_PlayHandler(void);
int32_t getWave(void);
Notes getNote(int32_t);

int Song_EnvelopeScale(int currentMill, int totalMill);

extern Note maryhadalamb[];

#endif

