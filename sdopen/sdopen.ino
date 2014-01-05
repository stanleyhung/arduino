#include <SD.h>

void setup() {
  Serial.begin(9600);
  char* fileName = "low.wav";
  Serial.println("testing SD Card...");
  if (!SD.begin()) {
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
