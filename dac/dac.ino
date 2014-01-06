#include <SD.h>

File myFile;
char* fileName = "low.wav";

typedef struct header_file {
  char chunkID[4];
  char chunkSize[4];
  char format[4];
} header;

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
  if (!myFile) {
    Serial.println("Error - Could not open file");
    return;
  }
  Serial.println("successfully opened file");
  myFile.close();
}

void loop () {
}
