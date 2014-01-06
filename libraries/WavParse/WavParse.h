/*
 * WavParse.h - Library for parsing header information from WAV files
 * Created by Stanley Hung, January 1, 2014.
 */
#ifndef WavParse_h
#define WavParse_h

#include "Arduino.h"
#include "SD.h"

class WavParse {
public:
	WavParse(File *file);
	int success; //set to 1 if file headers have been successfully parsed
	unsigned long sampleRate;
	unsigned int bitsPerSample; 
private:
	typedef union File_Header {
	  typedef struct Header {
	    unsigned long chunkID;
	    unsigned long chunkSize;
	    unsigned long format;
	  } Header;
	  Header data;
	  byte b[12];
	} File_Header;

	typedef union Wave_Header {
	  typedef struct Header {
	    unsigned long subChunkID;
	    unsigned long subChunkSize;
	  } Header;
	  Header data;
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
	  Data data;
	  byte b[24];
	} Wave_Data;
	File_Header *_myFileHeader;
	Wave_Header *_myWaveHeader;
	Wave_Data *_myWaveData;
	int checkFileHeader(File_Header *fh);
	int checkWaveHeader(Wave_Header *wh);
	int checkWaveData(Wave_Data *wd);

};

#endif