#include <SD.h>
#include <WavParse.h>

File myFile;
char* fileName = "low.wav";
volatile int j;
int ledPin = 7;
int resetButton = 9;
volatile byte b[1];

void setup() {
  
  //reset functionality: if reset button is pressed
  pinMode(resetButton, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  for (int i = 5; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
  if (digitalRead(resetButton) == HIGH) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    for (int i = 5; i < 10; i++) {
      digitalWrite(i, HIGH);
    }
    return;
  }
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  //Serial.begin(9600);
  //open SD Card
  if (!SD.begin(4)) {
    //Serial.println("ERROR - SD Card could not be opened");
    return;
  }
  //Serial.print(fileName);
  //Serial.print("\t");
  if (SD.exists(fileName)) {
    //Serial.println("exists in SD Card");
  } 
  else {
    //Serial.println("does not exist in SD Card");
  }
  //Open + Parse File Header Information
  myFile = SD.open(fileName);
  if (!myFile) {
    //Serial.println("Error - Could not open file");
    return;
  }
  //Serial.println("successfully opened file");
  WavParse parser(&myFile);
  //Serial.println("attempted to parse file");
  myFile.close();
  if (parser.success) {
    /*
    Serial.println("successfully parsed file");
    Serial.println(parser.sampleRate);
    Serial.println(parser.bitsPerSample);
    Serial.println(parser.dataOffset);
    */
  } else {
    //Serial.println("ERROR - File could not be parsed");
    return;
  }
  j = 0;

  cli(); //disable interrupts

  //set timer1 interrupts at 6kHz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624; //2666 = (16*10^6) / (6000*1) - 1
  //turn on CTC mode
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); //set CS10 bit for 1 prescaler
  //enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); //enable interrupts

}

//Timer1 interrupts at 6kHz
ISR(TIMER1_COMPA_vect) {
  if (j) {
    digitalWrite(ledPin, HIGH);
    j = 0;
  } 
  else {
    digitalWrite(ledPin, LOW);
    j = 1;
  }
}

void loop () {
}

