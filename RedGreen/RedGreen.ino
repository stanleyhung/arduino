void setup() {
  pinMode(1, OUTPUT); //green LED
  pinMode(2, OUTPUT); //red LED
  pinMode(9, INPUT);
}

void loop() {
  /* If the switch is on, turn on the green LED.
   * Else, turn on the red LED
   */
  int switchState = digitalRead(9);
  if (switchState == LOW) {
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
  }
}
