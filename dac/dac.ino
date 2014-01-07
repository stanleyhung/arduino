#include <SD.h>
#include <WavParse.h>

File myFile;
char* fileName = "low.wav";
volatile int j;
int ledPin = 7;
int resetButton = 9;
volatile byte data;

//DEBUG is defined if ports 0 and 1 are not to be used as outputs
//#define DEBUG

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
  
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  //open SD Card
  if (!SD.begin(4)) {
    #ifdef DEBUG
    Serial.println("ERROR - SD Card could not be opened");
    #endif
    signalError();
    return;
  }
  #ifdef DEBUG
  Serial.print(fileName);
  Serial.print("\t");
  #endif
  if (SD.exists(fileName)) {
    #ifdef DEBUG
    Serial.println("exists in SD Card");
    #endif
  } 
  else {
    #ifdef DEBUG
    Serial.println("does not exist in SD Card");
    #endif
    signalError();
    return;
  }
  //Open + Parse File Header Information
  myFile = SD.open(fileName);
  if (!myFile) {
    #ifdef DEBUG
    Serial.println("Error - Could not open file");
    #endif
    signalError();
    return;
  }
  #ifdef DEBUG
  Serial.println("successfully opened file");
  #endif
  WavParse parser(&myFile);
  #ifdef DEBUG
  Serial.println("attempted to parse file");
  #endif
  if (parser.success) {
    #ifdef DEBUG
    Serial.println("successfully parsed file");
    Serial.println(parser.sampleRate);
    Serial.println(parser.bitsPerSample);
    Serial.println(parser.dataOffset);
    #endif
  } else {
    #ifdef DEBUG
    Serial.println("ERROR - File could not be parsed");
    #endif
    signalError();
    return;
  }
  j = 0;
  
  if (!myFile) {
    signalError();
    return;
  }

  #ifndef DEBUG
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  #endif
  signalSuccess();
  
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
  #ifndef DEBUG
  data = myFile.read();
  //output most-significant bit of data
  PORTB = (PORTB & B111100) | (data >> 7);
  //output the other bits of data
  PORTD = (PORTD & B00010000) | ( (data & B0000111) | ( (data << 1) & B11100000));
  #else
  if (j) {
    digitalWrite(ledPin, HIGH);
    j = 0;
  } 
  else {
    digitalWrite(ledPin, LOW);
    j = 1;
  }
  #endif
}

void signalError() {
 digitalWrite(3, HIGH);
 delay(1000);
 digitalWrite(5, HIGH);
 delay(1000);
 digitalWrite(7, HIGH);
}

void signalSuccess() {
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(7, HIGH);
  delay(1000); 
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
}

void loop () {
}

