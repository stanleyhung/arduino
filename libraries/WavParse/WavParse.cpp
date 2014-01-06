/*
 * WavParse.cpp - Library for parsing header information from WAV files
 * Created by Stanley Hung, January 1, 2014.
 */

#include "Arduino.h"
#include "SD.h"
#include "WavParse.h"

// The following fields map ASCII characters to little-endian decimal
#define RIFF 1179011410
#define WAVE 1163280727
#define FMT 544501094

//In the WAVE Header, a standard PCM file contains at least 16 bytes 
#define PCM_SIZE 16

WavParse::WavParse(File *file) {
	success = 0;
	_myFileHeader = (File_Header*) malloc(sizeof(File_Header));
	for (int i = 0; i < sizeof(File_Header); i++) {
		_myFileHeader->b[i] = (*file).read();
	}
	if (checkFileHeader(_myFileHeader) != 1) {
		return;
	}
	_myWaveHeader = (Wave_Header*) malloc(sizeof(Wave_Header));
	for (int i = 0; i < sizeof(Wave_Header); i++) {
		_myWaveHeader->b[i] = (*file).read();
	}
	if (checkWaveHeader(_myWaveHeader) != 1) {
		return;
	}
	_myWaveData = (Wave_Data*) malloc(sizeof(Wave_Data));
	for (int i = 0; i < sizeof(Wave_Data); i++) {
		_myWaveData->b[i] = (*file).read();
	}
	if (checkWaveData(_myWaveData) != 1) {
		return;
	}
	success = 1;
}

// This function ensures that a fileheader is correctly formatted.
int WavParse::checkFileHeader(File_Header *fh) {
	if (fh->data.chunkID != RIFF) {
		return 0;
	}
	//Ensure that the chunkSize is positive
	if (fh->data.chunkSize <= 0) {
		return 0;
	}
	if (fh->data.format != WAVE) {
		return 0;
	}
	return 1;
}

// This function ensures that a waveheader is correctly formatted.
int WavParse::checkWaveHeader(Wave_Header *wh) {
	if (wh->data.subChunkID != FMT) {
		return 0;
	}
	//the size of the chunk must be at least 16 bytes since PCM is 16
	if (wh->data.subChunkSize < PCM_SIZE) {
		return 0;
	}
	return 1;
}

// This function ensures that the wavedata contains data that can be parsed correctly.
int WavParse::checkWaveData(Wave_Data *wd) {
	if (wd->data.numChannels < 1 || wd->data.numChannels > 8) {
		return 0;
	}
	if (wd->data.sampleRate < 0) {
		return 0;
	}
	if (wd->data.byteRate < 0 ) {
		return 0;
	}
	if (wd->data.bitsPerSample % 8 != 0) {
		return 0;
	}
	return 1;
}



