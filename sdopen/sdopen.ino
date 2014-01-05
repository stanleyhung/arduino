#include <SD.h>

void setup() {
  char* fileName = "low.wav";
  Serial.println("testing SD Card...");
  if (!SD.begin()) {
    Serial.println("ERROR - SD Card could not be opened");
    return;
  }
  Serial.begin(9600);
  Serial.println(fileName);
  if (SD.exists(fileName)) {
    Serial.println("exists in SD Card");
  } else {
    Serial.println("does not exist in SD Card");
  }
}

void loop () {
}
