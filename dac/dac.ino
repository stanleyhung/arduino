#include <SD.h>
#include <WavParse.h>

File myFile;
char* fileName = "low.wav";

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
  if (!myFile) {
    Serial.println("Error - Could not open file");
    return;
  }
  Serial.println("successfully opened file");
  WavParse parser(&myFile);
  Serial.println("attempted to parse file");
  Serial.println(parser.success);
  myFile.close();
}

void loop () {
}
