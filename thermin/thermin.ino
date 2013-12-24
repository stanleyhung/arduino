int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
const int speakerPin = 8;
const int ledPin = 1;
const int switchPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  while (millis() < 5000) {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  
  digitalWrite(ledPin, LOW);
}

void loop () {
  int switchState = digitalRead(switchPin);
  int curTime = millis();
  while (millis() < curTime + 1000) {
    if (switchState == HIGH) {
      sensorValue = analogRead(A0);
      int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 2000);
      tone(speakerPin, pitch, 20);
      delay(10);
    }
  }
}
