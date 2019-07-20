#include "potentiometer.cpp"
#include <usbmidi.h>
/*Define Potentiometers here, as many as you have. 
  These objects will be used later to control multiplexing.*/
Potentiometer c1;
Potentiometer c2;
Potentiometer c3;

/*Ints to be used later for storing potentiometers last read 
  values*/
int p1 = 0;
int p2 = 0;
int p3 = 0;


void setup() {
/*Define pin type here. Your arduino may have a different
  pin configuration but as a general practice pins should
  be set to output.*/
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

/*Set pins here
  Pins should be set with one pin per voltage/ground on your 
  potentiometer. This is generally the two outer pins--with 
  the middle pin being signal--on 3 pin potentiometers.
  Potentiometer.cpp contains the class being used for these,
  and additional pins would need to be added for 4+ pin
  potentiometers.*/
  c1.pin1 = 7;
  c1.pin2 = 6;
  c1.reader = A2;
  c1.value = 0;

  c2.pin1 = 9;
  c2.pin2 = 8;
  c2.reader = A1;
  c2.value = 0;

  c3.pin1 = 10;
  c3.pin2 = 11;
  c3.reader = A0;
  c3.value = 0;
}

void serial_print(int sv1, int sv2, int sv3)
{
    Serial.print("P1: ");Serial.print(sv3/8);Serial.print(" | ");
    Serial.print("P2: ");Serial.print(sv2/8);Serial.print(" | ");
    Serial.print("P3: ");Serial.println(sv1/8);
}

// the loop routine runs over and over again forever:
void loop() {
  /*Read the input on analog pin 0, setting one pin to high 
    and one to ground*/
  int sv1 = c1.read();
  int sv2 = c2.read();
  int sv3 = c3.read();
  USBMIDI.poll();
  while (USBMIDI.available()) {
    u8 message = USBMIDI.read();
  }

  for (int i=0; i<ANALOG_PINS; ++i) {
    int value = readCC(analogPins[i]);

    // Send CC only if th has changed.
    if (ccValues[i] != value) {
      sendCC(0, i, value);
      ccValues[i] = value;
    }
  }

  for (int i=0; i<BUTTON_PIN_COUNT; ++i) {
    int down = isButtonDown(buttonPins[i]);

    if (down != buttonDown[i]) {
      sendNote(0, 64 + i, down ? 127 : 0);
      buttonDown[i] = down;
    }
  }

  // Flush the output.
  USBMIDI.flush();
}
  
  // print out the value of the potentiometers potentially.
  if(p1 != sv1 || p2 != sv2 || p3 != sv3){
   // Send values only when changes occur. 
   // In practice this is every time
    serial_print(sv1, sv2, sv3);
  //Send relevant control changes over midiusb. 
  //Divide values by eight to get range of 0-127
   // MIDI.sendControlChange(16,sv3/8,1);
   // MIDI.sendControlChange(17,sv2/8,1);
   // MIDI.sendControlChange(18,sv1/8,1);
    p1 = sv1;
    p2 = sv2;
    p2 = sv3; 
  }
}
