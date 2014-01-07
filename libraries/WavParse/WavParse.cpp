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
#define DATA 1635017060

//In the WAVE Header, a standard PCM file contains at least 16 bytes 
#define PCM_SIZE 16

//Uncompressed files will have this value
#define UNCOMPRESSED_AUDIO_FORMAT 1

WavParse::WavParse(File *file) {
	//reset file in case it was used by someone else
	(*file).seek(0);
	success = 0;
	for (int i = 0; i < sizeof(File_Header); i++) {
		_myFileHeader->b[i] = (*file).read();
	}
	if (checkFileHeader(_myFileHeader) != 1) {
		return;
	}
	for (int i = 0; i < sizeof(Wave_Header); i++) {
		_myWaveHeader->b[i] = (*file).read();
	}
	if (checkWaveHeader(_myWaveHeader) != 1) {
		return;
	}
	for (int i = 0; i < _myWaveHeader->data.subChunkSize; i++) {
		_myWaveData->b[i] = (*file).read();
	}
	if (checkWaveData(_myWaveData) != 1) {
		return;
	}
	for (int i = 0; i < sizeof(Data); i++) {
		_myData->b[i] = (*file).read();
	}
	if (checkData(_myData) != 1) {
		return;
	}
	success = 1;
	sampleRate = _myWaveData->data.sampleRate;
	bitsPerSample = _myWaveData->data.bitsPerSample;
	dataOffset = (*file).position();
	(*file).close();
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
	if (wd->data.audioFormat != UNCOMPRESSED_AUDIO_FORMAT) {
		return 0;
	}
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

// This function checks the integrity of the sound data
int WavParse::checkData(Data *d) {
	if (d->data.data != DATA) {
		return 0;
	}
	if (d->data.size <= 0) {
		return 0;
	}
	return 1;
}



