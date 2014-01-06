#include <SD.h>

File myFile;
char* fileName = "low.wav";

typedef struct header_file {
  union {
    unsigned long ul;
    byte b[4];
  } chunkID;
  union {
    unsigned long ul;
    byte b[4];
  } chunkSize;
  union {
    unsigned long ul;
    byte b[4];
  } format;
} Header;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
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
  myFile = SD.open(fileName);
  Header* myHeader = (Header*) malloc(sizeof(Header));
  if (!myFile) {
    Serial.println("Error - Could not open file");
    return;
  }
  Serial.println("successfully opened file");
  myFile.close();
}

void loop () {
}
