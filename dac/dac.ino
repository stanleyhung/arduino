#include <SD.h>

File myFile;
char* fileName = "low.wav";

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
    myHeader->b[i] = myFile.read();
  }
  Wave_Header* myWav = (Wave_Header*) malloc(sizeof(Wave_Header));
  for (int i = 0; i < sizeof(Wave_Header); i++) {
    myWav->b[i] = myFile.read();
  }
  Wave_Data* myWavData = (Wave_Data*) malloc(myWav->h.subchunksize);
  for (int i = 0; i < myWav->h.subchunksize; i++) {
    myWavData->b[i] = myFile.read();
  }
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
  myFile.close();
}

void loop () {
}
