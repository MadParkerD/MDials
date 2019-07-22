#include "Arduino.h"
#include <usbmidi.h>
class Potentiometer
{
  public:

  int pin1;

  int pin2;

  int value;
  
  uint8_t channel;

  uint8_t control;

  uint8_t reader;

  void up()
  {
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,LOW);
    delay(2);
  }
  
  void down()
  {
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
    delay(2);
  }

  int read()
  {
    up();
    value = analogRead(reader);
    down();
    delay(5);
    return value;
  }

  bool changed(int newValue)
  {
    if (newValue/8 != value/8)
    {
      return true;
    }
    return false;
  }

  bool send()
  {
    if(changed(read()))
    {
        USBMIDI.write(0xB0 | (channel & 0xf));
        USBMIDI.write(control & 0x7f);
        USBMIDI.write(value & 0x7f);
    }
    
  }

  void print()
  {
    Serial.print(value/8);
  }
};
