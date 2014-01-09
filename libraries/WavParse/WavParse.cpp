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
	reason = "default reason";
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
	(*file).seek(0);
}

// This function ensures that a fileheader is correctly formatted.
int WavParse::checkFileHeader(File_Header *fh) {
	if (fh->data.chunkID != RIFF) {
		reason = "File header: NO RIFF HEADER";
		return 0;
	}
	//Ensure that the chunkSize is positive
	if (fh->data.chunkSize <= 0) {
		reason = "File header: chunkSize is not positive";
		return 0;
	}
	if (fh->data.format != WAVE) {
		reason = "File header: format is not WAVE";
		return 0;
	}
	return 1;
}

// This function ensures that a waveheader is correctly formatted.
int WavParse::checkWaveHeader(Wave_Header *wh) {
	if (wh->data.subChunkID != FMT) {
		reason = "Wave header: format is not correct; not fmt";
		return 0;
	}
	//the size of the chunk must be at least 16 bytes since PCM is 16
	if (wh->data.subChunkSize < PCM_SIZE) {
		reason = "Wave header: format is not PCM";
		return 0;
	}
	return 1;
}

// This function ensures that the wavedata contains data that can be parsed correctly.
int WavParse::checkWaveData(Wave_Data *wd) {
	if (wd->data.audioFormat != UNCOMPRESSED_AUDIO_FORMAT) {
		reason = "Wave data: audioFormat incorrect";
		return 0;
	}
	if (wd->data.numChannels < 1 || wd->data.numChannels > 8) {
		reason = "Wave data: numChannels unsupported";
		return 0;
	}
	if (wd->data.sampleRate < 0) {
		reason = "Wave data: sampleRate is negative: ";
		return 0;
	}
	if (wd->data.byteRate < 0 ) {
		reason = "Wave data: byteRate is negative: ";
		return 0;
	}
	if (wd->data.bitsPerSample % 8 != 0) {
		reason = "Wave data: bitsPerSample is not divisible by 8: ";
		return 0;
	}
	return 1;
}

// This function checks the integrity of the sound data
int WavParse::checkData(Data *d) {
	if (d->data.data != DATA) {
		reason = "data: did not being with proper data header";
		return 0;
	}
	if (d->data.size <= 0) {
		reason = "data: size is not positive";
		return 0;
	}
	return 1;
}



