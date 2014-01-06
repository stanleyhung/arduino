/*
 * WavParse.cpp - Library for parsing header information from WAV files
 * Created by Stanley Hung, January 1, 2014.
 */

#include "Arduino.h"
#include "WavParse.h"

// The following fields map ASCII characters to little-endian decimal
#define RIFF 1179011410
#define WAVE 1163280727

WavParse::WavParse() {
	;
}

// This function ensures that a fileheader is correctly formatted.
int WavParse::checkFileHeader(File_Header *fh) {
	if (fh->h.chunkID != RIFF) {
		return 0;
	}
	//Ensure that the chunkSize is positive
	if (fh->h.chunkSize <= 0) {
		return 0;
	}
	if (fh->h.format != WAVE) {
		return 0;
	}
	return 1;
	
}
int WavParse::checkWaveHeader(Wave_Header *wh) {
	return 1;
}
int WavParse::checkWaveData(Wave_Data *wd) {
	return 1;
}



