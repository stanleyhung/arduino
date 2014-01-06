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
  } data;
} File_Header;

typedef struct Wave_Header {
  union {
    typedef struct Header {
      unsigned long subchunkID;
      unsigned long subchunksize;
    } Header;
    Header h;
    byte b[8];
  } data;
} Wave_Header;

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
    myHeader->data.b[i] = myFile.read();
  }
  Serial.print("chunkID is: ");
  Serial.println(myHeader->data.h.chunkID, HEX);
  Serial.print("chunksize is: ");
  Serial.println(myHeader->data.h.chunkSize, HEX);
  Serial.print("format is: ");
  Serial.println(myHeader->data.h.format, HEX);
  myFile.close();
}

void loop () {
}
