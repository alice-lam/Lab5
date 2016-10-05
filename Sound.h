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


#define D7   2348   // 1174.7 Hz
#define DF7  2217   // 1108.7 Hz

#define C7   2093   // 2093 Hz
#define B6   1976   // 1975.5 Hz
#define BF6   1865   // 1864.7 Hz
#define A6   1760   // 1760 Hz
#define AF6   1661   // 1661.2 Hz
#define G6  1568   // 1568 Hz
#define GF6   1480   // 1480 Hz
#define F6  1397   // 1396.9 Hz
#define E6   1319   // 1318.5 Hz
#define EF6   1245   // 1244.5 Hz
#define D6  1175   // 1174.7 Hz
#define DF6   1109   // 1108.7 Hz
#define C6 1047   // 1046.5 Hz
#define B5   988   // 987.8 Hz
#define BF5   932   // 932.3 Hz
#define A5 880   // 880 Hz
#define AF5   831   // 830.6 Hz
#define G5  784   // 784 Hz
#define GF5   740   // 740 Hz
#define F5   699   // 698.5 Hz
#define E5   659   // 659.3 Hz
#define EF5   622   // 622.3 Hz
#define D5   587   // 587.3 Hz
#define DF5   554   // 554.4 Hz
#define C5   523   // 523.3 Hz
#define B4   494   // 493.9 Hz
#define BF4   466   // 466.2 Hz
#define A4   440   // 440 Hz
#define AF4   415   // 415.3 Hz
#define G4   392   // 392 Hz
#define GF4   370   // 370 Hz
#define F4   349   // 349.2 Hz
#define E4   330   // 329.6 Hz
#define EF4   311   // 311.1 Hz
#define D4   294   // 293.7 Hz
#define DF4   277   // 277.2 Hz
#define C4   262   // 261.6 Hz
#define B3   247   // 246.9 Hz
#define BF3   233   // 233.1 Hz
#define A3   220   // 220 Hz
#define AF3   208   // 207.7 Hz
#define G3   196   // 196 Hz
#define GF3   185   // 185 Hz
#define F3   175   // 174.6 Hz
#define E3   165   // 164.8 Hz
#define EF3   156   // 155.6 Hz
#define D3   147   // 146.8 Hz
#define DF3   139   // 138.6 Hz
#define C3   131   // 130.8 Hz



#define C0	262
#define D0	294
#define E0	330
#define F0	349
#define G0	392
#define A0	440
#define B0	494
#define C1	523

typedef struct {
	uint16_t pitch;    			// frequency for note
	uint16_t duration;	  	// number of beats for note
	uint16_t timetill;      // number of beats until execution
	uint16_t channel;				// 1 or 2
} Notes;

typedef struct {
	uint16_t tempo;    //beats per minute
	int numNotes;
	Notes* notes;       //all of the notes in the song
} Song;

void Song_PlayInit(void);
void nextNoteHandler(void);
void MHandler(void);
void HHandler(void);
Notes getNote(int32_t);
void setHarmDuration(int duration);
void setMeloDuration(int duration);
int Song_EnvelopeScale(int currentMill, int totalMill,int scale);
void Envelope(void);
#endif

