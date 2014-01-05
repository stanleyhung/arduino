#include <SD.h>
int ledPin = 13;
const char* name = "high.wav";
char *fileName;

void setup() {
 SD.begin();
 pinMode(ledPin, OUTPUT);
 fileName = (char*) malloc(sizeof(name));
 strcpy(fileName, name);
}

/* This sketch tests to see if the fileName above exists inside the arduino's SD Card
 * by blinking an LED, assumed to be on pin ledPin
 */
void loop() {
  if (SD.exists(fileName)) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
}
