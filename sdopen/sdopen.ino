#include <SD.h>

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  char* fileName = "low.wav";
  Serial.println("testing SD Card...");
  if (!SD.begin(4)) {
    Serial.println("ERROR - SD Card could not be opened");
    return;
  }
  Serial.println(fileName);
  if (SD.exists(fileName)) {
    Serial.println("exists in SD Card");
  } else {
    Serial.println("does not exist in SD Card");
  }
}

void loop () {
}
