#include "MIDIUSB.h"

int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;
int p5 = 0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  MIDI.begin(4);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  int sv1 = analogRead(A2);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  delay(1);
  digitalWrite(9,HIGH);
  digitalWrite(8,LOW);
  int sv2 = analogRead(A1);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(1);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  int sv3 = analogRead(A0);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  // print out the value you read:
  if(p1 != sv1 || p2 != sv2 || p3 != sv3){
   // Serial.print("P1: ");Serial.print(sv3/8);Serial.print(" | ");
   // Serial.print("P2: ");Serial.print(sv2/8);Serial.print(" | ");
   // Serial.print("P3: ");Serial.println(sv1/8);

    MIDI.sendControlChange(16,sv3/8,1);
    MIDI.sendControlChange(17,sv2/8,1);
    MIDI.sendControlChange(18,sv1/8,1);
    p1 = sv1;
    p2 = sv2;
    p2 = sv3; 
  }
  MIDI.read();
  
  delay(1);        // delay in between reads for stability
}
