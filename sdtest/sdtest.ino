#include <SD.h>
int ledPin = 13;
const char* name = "high.wav";
char *fileName;

void setup() {
 SD.begin(4);
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);
 fileName = (char*) malloc(sizeof(name));
 strcpy(fileName, name);
}

/* This sketch tests to see if the fileName above exists inside the arduino's SD Card
 * by blinking an LED, assumed to be on pin ledPin
 */
void loop() {
  if (SD.exists(fileName)) {
    Serial.println("file exists in SD Card");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
  Serial.println("file does not exist in SD Card");
}
