#include <SD.h>
#include <WavParse.h>

File myFile;
char* fileName = "low.wav";
WavParse parser();

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  //open SD Card
  if (!SD.begin(4)) {
    Serial.println("ERROR - SD Card could not be opened");
    return;
  }
  Serial.print(fileName);
  Serial.print("\t");
  if (SD.exists(fileName)) {
    Serial.println("exists in SD Card");
  } else {
    Serial.println("does not exist in SD Card");
  }
  //Open + Parse File Header Information
  myFile = SD.open(fileName);
  if (!myFile) {
    Serial.println("Error - Could not open file");
    return;
  }
  Serial.println("successfully opened file");
  /*
  Serial.print("chunkID is: ");
  Serial.println(myHeader->h.chunkID);
  Serial.print("chunksize is: ");
  Serial.println(myHeader->h.chunkSize);
  Serial.print("format is: ");
  Serial.println(myHeader->h.format);
  Serial.print("subchunkid is: ");
  Serial.println(myWav->h.subchunkID);
  Serial.print("subchunksize is: ");
  Serial.println(myWav->h.subchunksize);
  Serial.print("numChannels is: ");
  Serial.println(myWavData->d.numChannels);
  Serial.print("sampleRate is: ");
  Serial.println(myWavData->d.sampleRate);
  Serial.print("byteRate is: ");
  Serial.println(myWavData->d.byteRate);
  */
  myFile.close();
}

void loop () {
}
