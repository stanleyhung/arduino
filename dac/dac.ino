#include <SD.h>
#include <WavParse.h>

File myFile;
char* fileName = "low.wav";
int i;
int ledPin = 7;
volatile byte b[1];

void setup() {

  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(ledPin, OUTPUT);
  //open SD Card
  if (!SD.begin(4)) {
    Serial.println("ERROR - SD Card could not be opened");
    return;
  }
  Serial.print(fileName);
  Serial.print("\t");
  if (SD.exists(fileName)) {
    Serial.println("exists in SD Card");
  } 
  else {
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
  if (parser.success) {
    Serial.println("successfully parsed file");
    Serial.println(parser.sampleRate);
    Serial.println(parser.bitsPerSample);
    Serial.println(parser.dataOffset);
  } else {
    Serial.println("ERROR - File could not be parsed");
  }
  myFile.seek(parser.dataOffset);
  i = 0;

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
  if (i) {
    digitalWrite(ledPin, HIGH);
    i = 0;
  } 
  else {
    digitalWrite(ledPin, LOW);
    i = 1;
  }
}

void loop () {
}

