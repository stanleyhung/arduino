/*
 * WavParse.h - Library for parsing header information from WAV files
 * Created by Stanley Hung, January 1, 2014.
 */
#ifndef WavParse_h
#define WavParse_h

#include "Arduino.h"

class WavParse {
public:
	WavParse();
	typedef union File_Header {
	  typedef struct Header {
	    unsigned long chunkID;
	    unsigned long chunkSize;
	    unsigned long format;
	  } Header;
	  Header h;
	  byte b[12];
	} File_Header;

	typedef union Wave_Header {
	  typedef struct Header {
	    unsigned long subchunkID;
	    unsigned long subchunksize;
	  } Header;
	  Header h;
	  byte b[8];
	} Wave_Header;

	typedef union Wave_Data {
	  typedef struct Data {
	    unsigned short audioFormat;
	    unsigned short numChannels;
	    unsigned long sampleRate;
	    unsigned long byteRate;
	    unsigned short blockAlign;
	    unsigned short bitsPerSample;
	    byte unused[8];
	  } Data;
	  Data d;
	  byte b[24];
	} Wave_Data;
	int checkFileHeader(*File_Header fh);
	int checkWaveHeader(*Wave_Header wh);
	int checkWaveData(*Wave_Data wd);

}

#endif