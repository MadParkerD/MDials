#include "potentiometer.cpp"
#include <MIDI.h>

#if defined(__AVR_ATmega2560__)
/* My ATmega1280 board did not work with this software, not sure why.
 * If you absolutely must use said board then replace
 * with #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
 * AT YOUR OWN RISK! I DO NOT SUPPORT THIS SO DO NOT DO IT.
 * To reiterate: ABSOLUTELY NO WARRANTY (see LICENCE distributed with this code)
 */
int maxPins = 52;
#endif
#if defined(__AVR_ATmega168__)
// Similarly I have to way of testing if __AVR_ATmega328P__ or __AVR_ATmega644P__ would work here
// To reiterate: ABSOLUTELY NO WARRANTY (see LICENCE distributed with this code)
int maxPins = 12;
#endif 

struct MySettings : public midi::DefaultSettings
{
  /* Change this value to 115200 to get compatability with hairless-midi 
   * and other software midi solutions if you dont want to risk DFU 
   flashing your arduino*/
    static const long BaudRate = 31250;
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial,Serial,MIDI,MySettings);


//Change numPots to your number of potentiometers
const int numPots = 35;
/*
 * Potentiometers should be defined here if not using
 * the dynamic definition included in this file. e.g.
 * Potentiometer potentiometer1;
 * 
 * Potentiometer * pots[numPots];
 */
 
//Comment below line out if static definition is used
Potentiometer * pots;


void setup() {
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
  Variables are typically A0-A<number of analog pins -1>
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
  c1.contol = 0;

  I provide a default setup here that should work if everything
  is configured as defined in the installation section of the wiki
  hosted as part of this project on github*/
  pots = new Potentiometer[numPots];
  for (int i = 0; i < numPots; i++)
  {
    pots[i].pin1 = ((i*2)%maxPins + 2);
    pots[i].pin2 = ((i*2)%maxPins + 3);  
  /*This is i*2 since we use two digital pins per potentiometer
    +2/3 on the end since D0 and D1 are reserved for talking to 
    the ATmega16_2/ATmegs8_2 chip and/or doing regular usb serial
    if done without DFU flashing. Maxpins should be set by the block
    at the head of this file, and will allow looping through pins
    if multiple readers are used*/

    pots[i].control = (i%64); //0-63 
  /*
   * As mentioned vcvrack supports anything that sends values of 0-127
   * since the data is sent raw this should allow for basically any number 
   * as control but some software converters freak out when you send 
   * items with lengths that do not match the midi standard. 
   * Since this is also compatible with hairless-midi 
   * which relies on loopback devices which may be included in that list 
   * of software limit the control numbers to 0-63. I am not sure how the HIDUINO
   * firmware handles this, but since this is being sent as a raw packet it should 
   * be relatively graceful. It did seem to work when more than 32 potentiometers 
   * were hooked up, which may mean that it doesn't try to do any data conversion.
   * If you know your software will support non-standard packets this could probably
   * be changed to pots[i].control = i; or i%<desired control number max>
   */
    pots[i].channel = (i/64)%16 + 1; //1-16 
  /*
   * This is an attempt to maximise the number of potentiometers possible
   * Since we have 16 channels use them all after the 64th potentiometer and allow more total potentiometers 
   * Not sure you could even saturate one channel with control changes, but who knows.
   * If you run into one channel being saturated, try swapping to:
   * pots[i].control = (i/16)%64; //0-63
   * pots[i].channel = (i%16) + 1; //1-16 
   * This will prioritize channels above control numbers, and 
   * evenly distribute potentiometers across channels instead of 
   * doing control 0-63 on channel 1 and then starting over on channel 2
   */
    int times = i/(maxPins/2); //How many loops of pins have been performed
    #if defined(__AVR_ATmega2560__)
    times = times % 16; //Attempt to fail in a way that does not cause microcontroller problems
    pots[i].reader = (97 - times);//Set to an analog pin starting at A0
    #endif
    #if defined(__AVR_ATmega168__)
    times = times % 6; //Attempt to fail in a way that does not cause microcontroller problems
    pots[i].reader = (14 + times);//Set to an analog pin starting at A0
    #endif 
  /*
   * This block should allow up to maxpins/2 * analog pins number of potentiometers
   * This is possible because two digital pins are needed per potentiometer, and 
   * digital pins can be re-used once per analog input when multiplexing.
   */
    pots[i].value = 0; //Just initialize this
  }
  
  MIDI.begin(1);
  //Also change to Serial.begin(115200); here if using hairless-midi or similar
  Serial.begin(31250);
}

// The loop routine runs over and over again forever:
void loop() {

  for (int i = 0; i < numPots; i++)
  {
    if (pots[i].changed())
    {
      //I had originally intended to use something else, but the standard arduino library works here
      //This sends a raw control change with whatever you give it, even if those values are not 
      //technically compliant with MIDI standards.
      MIDI.send(0xB0,pots[i].control,pots[i].value,pots[i].channel);
    }
  }

  MIDI.read();
}
