#include <SD.h>

File myFile;
char* fileName = "low.wav";

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
  File_Header* myHeader = (File_Header*) malloc(sizeof(File_Header));
  if (!myFile) {
    Serial.println("Error - Could not open file");
    return;
  }
  Serial.println("successfully opened file");
  for (int i = 0; i < sizeof(File_Header); i++) {
    myHeader->payLoad.b[i] = myFile.read();
  }
  Wave_Header* myWav = (Wave_Header*) malloc(sizeof(Wave_Header));
  for (int i = 0; i < sizeof(Wave_Header); i++) {
    myWav->payLoad.b[i] = myFile.read();
  }
  Wave_Data* myWavData = (Wave_Data*) malloc(myWav->payLoad.h.subchunksize);
  for (int i = 0; i < myWav->payLoad.h.subchunksize; i++) {
    myWavData->payLoad.b[i] = myFile.read();
  }
  Serial.print("chunkID is: ");
  Serial.println(myHeader->payLoad.h.chunkID);
  Serial.print("chunksize is: ");
  Serial.println(myHeader->payLoad.h.chunkSize);
  Serial.print("format is: ");
  Serial.println(myHeader->payLoad.h.format);
  Serial.print("subchunkid is: ");
  Serial.println(myWav->payLoad.h.subchunkID);
  Serial.print("subchunksize is: ");
  Serial.println(myWav->payLoad.h.subchunksize);
  Serial.print("numChannels is: ");
  Serial.println(myWavData->payLoad.d.numChannels);
  Serial.print("sampleRate is: ");
  Serial.println(myWavData->payLoad.d.sampleRate);
  Serial.print("byteRate is: ");
  Serial.println(myWavData->payLoad.d.byteRate);
  myFile.close();
}

void loop () {
}
