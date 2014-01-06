#include <SD.h>

File myFile;
char* fileName = "low.wav";

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("ERROR - SD Card could not be opened");
    return;
  }
  Serial.print(fileName);
  if (SD.exists(fileName)) {
    Serial.println("exists in SD Card");
  } else {
    Serial.println("does not exist in SD Card");
  }
}

void loop () {
}
