
/* This resistor ladder separates an analog input into 5 notes */
int notes[] = {262, 294, 330, 349};
const int speakerPin = 8;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int keyVal = analogRead(A0);
  float voltage = keyVal/1024.0*5.0;
  if (voltage > 0.00) {
    Serial.println(voltage);
  }
  
  if (voltage >= 0.02 && voltage <= 0.1) {
    tone(speakerPin, notes[0]);
  } else if (voltage > 2.0 && voltage < 3.0) {
    tone(speakerPin, notes[1]);
  } else if (voltage >= 4.0 && voltage <= 4.9) {
    tone(speakerPin, notes[2]);
  } else if (voltage >= 4.91) {
    tone(speakerPin, notes[3]);
  } else {
    noTone(speakerPin);
  }
}
