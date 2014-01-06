/*
 * WavParse.cpp - Library for parsing header information from WAV files
 * Created by Stanley Hung, January 1, 2014.
 */

#include "Arduino.h"
#include "WavParse.h"

WavParse::WavParse() {
	;
}

int WavParse::checkFileHeader(File_Header *fh) {
	return 1;
}
int WavParse::checkWaveHeader(Wave_Header *wh) {
	return 1;
}
int WavParse::checkWaveData(Wave_Data *wd) {
	return 1;
}



