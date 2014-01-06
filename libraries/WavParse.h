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
	typedef struct File_Header {
	  union {
	    typedef struct Header {
	      unsigned long chunkID;
	      unsigned long chunkSize;
	      unsigned long format;
	    } Header;
	    Header h;
	    byte b[12];
	  } payLoad;
	} File_Header;

	typedef struct Wave_Header {
	  union {
	    typedef struct Header {
	      unsigned long subchunkID;
	      unsigned long subchunksize;
	    } Header;
	    Header h;
	    byte b[8];
	  } payLoad;
	} Wave_Header;

	typedef struct Wave_Data {
	  union {
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
	  } payLoad;
	} Wave_Data;

}

#endif