#include "potentiometer.cpp"
#include <usbmidi.h>
/*Define Potentiometers here, as many as you have. 
  These objects will be used later to control multiplexing.*/
Potentiometer c1;
Potentiometer c2;
Potentiometer c3;

//Change numPots to your number of potentiometers
const int numPots=2;
Potentiometer pots[numPots];

void setup() {
/*Define pin type here. Your arduino may have a different
  pin configuration but as a general practice pins should
  be set to output.*/
  

/*Set pins here
  Pins should be set with one pin per voltage/ground on your 
  potentiometer. This is generally the two outer pins--with 
  the middle pin being signal--on 3 pin potentiometers.
  Potentiometer.cpp contains the class being used for these,
  and additional pins would need to be added for 4+ pin
  potentiometers.
  c1.pin1 = 7;
  c1.pin2 = 6;
  
  Reader should correspond to the analog pin connected to
  the signal pin of the potentiometer. 
  Typically A0-A<number of analog pins -1>
  c1.reader = A2;
  
  Value is the actual value read by the potentiometer, 
  default 0
  c1.value = 0;
  
  Channel is the midi channel to attempt to use. 
  1-16 in practice, but some midi devices may support more
  Logically this is not as important if being use by modern 
  software, as many things have an "all channels" option
  c1.channel = 0;
  
  Control is the cc number to send. Different midi devices treat 
  these cc numbers differently. As per the midicc standard
  at least 1-63 support values of 0-127 which the potentiometer
  class will attempt to send, so use those unless you have 
  more potentiometers. As this program is designed primarily for 
  vcvrack which allows any cc number to be read, any cc number 
  that supports the full 1-127 should work. 
  Values above 31(LSB values) SHOULD be handled by the 
  potentiometer class, but some manufacturers treat these as 
  special and may support values of larger sizes which this 
  program does NOT support without modification.
  (e.g. 128x128 with 7 bit msb and lsb aka 14 bit midicc)  
  Devices that treat these values as bank selects etc. are 
  also not supported (This mean almost no hardware midi devices
  are supported).
  c1.contol = 0;*/

  c1.pin1 = 4;
  c1.pin2 = 5;
  c1.reader = 14;
  c1.value = 0;
  c1.channel = 0;
  c1.control = 0;

  
  c2.pin1 = 6;
  c2.pin2 = 7;
  c2.reader = 14;
  c2.value = 0;
  c2.channel = 0;
  c2.control = 0;

  c3.pin1 = 3;
  c3.pin2 = 11;
  c3.reader = 14;
  c3.value = 0;
  c3.channel = 0;
  c3.control = 0;

//Add all potentiometers declared above here
  Potentiometer init[numPots] = {c1,c2};
  for (int i = 0; i < numPots; i++)
  {
    pots[i] = init[i];
  }
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; i < numPots; i++)
  {
    pots[i].read();
    pots[i].print();
    if((i+1) < numPots)
    {
      Serial.print(" | ");
    }
  }
  Serial.println("");

  USBMIDI.poll();
  while (USBMIDI.available()) {
    u8 message = USBMIDI.read();
  }
  // Flush the output.
  USBMIDI.flush();
  
}
