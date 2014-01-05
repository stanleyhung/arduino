#include <SD.h>

File myFile;

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
  char* fileName = "low.wav";
  if (!myFile) {
    Serial.println("Opening file...");
    myFile = SD.open(fileName, FILE_READ); 
  }
  if (!myFile.available() > 0) {
    Serial.println("Done reading, closing file...");
    myFile.close();
    return;
  }
  char data = myFile.read();
  Serial.println(data);
}
