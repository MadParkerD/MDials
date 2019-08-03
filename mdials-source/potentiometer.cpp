#include "Arduino.h"
#include <MIDI.h>
struct MySettings : public midi::DefaultSettings
{
    static const long BaudRate = 115200;
};

class Potentiometer
{
  public:

    int pin1;

    int pin2;

    int value;
  
    uint8_t channel;

    uint8_t control;

    uint8_t reader;
    
   /*
   * This function brings the potentiometer into a readable state
   */
    void up()
    {
    pinMode(pin1,OUTPUT);
    pinMode(pin2,OUTPUT);
    delay(1);
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,LOW);
    delay(1);
    }

  /* 
   *  This function brings the potentiometer out of readable state
   */
    void down()
    {
      digitalWrite(pin1,LOW);
      digitalWrite(pin2,LOW);
      delay(1);
      pinMode(pin1,INPUT);
      pinMode(pin2,INPUT);
      delay(1);

    }


  /*
   * This function reads the potentiometer
   * Uses the "char" passed in when creating the potentiometer
   * for reading, this is generally A0-Ax depending on the
   * number of analog pins on your arduino.
   */
    int read()
    {
      up();
      value = analogRead(reader);
      down();
      delay(5);
      return value;
    }

  /*
   *To avoid saturating the interface this function checks a 
   *value to see if it is changed. No real point in sending values 
   *if they are not changed because this is using midiCC 
   *and a send does not correspond to a played note but rather a 
   *change in a continous value.
   */
    bool changed(int newValue)
    {
      if (newValue/8 != value/8)
      {
        return true;
      }
      return false;
    }

  /*
   * Send midi control change
   * Value/8 here is implicitly cast to uint8_t
   * This is fine because the maximum read for
   * analog pins is 1023 and 1023/8 < 255
   * The write calls themselves are substantially sumilar to 
   * the midictrl example provided by usbmidi on their github:
   * https://github.com/BlokasLabs/USBMIDI/blob/master/examples/midictrl/midictrl.ino
   */
    bool send(midi::MidiInterface<HardwareSerial,MySettings>& MIDI)
    {
      if(changed(read()))
      {
        uint8_t val = value/8;
        MIDI.sendControlChange(control,value,channel);
      }
    
    }

  /*
   * Print the value that would be sent via midiCC
   * Mostly useful for debug
   */
    void print()
    {
      
      //Serial.print(pin1);
      //Serial.print(" | ");
      //Serial.print(pin2);
      //Serial.print(" | ");
      //Serial.print(value);
    }
};
