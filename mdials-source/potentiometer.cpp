#include "Arduino.h"
#include <usbmidi.h>
class Potentiometer
{
  public:

  int pin1;

  int pin2;

  int value;

  uint8_t reader;

  void up()
  {
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,LOW);
  }
  
  void down()
  {
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
  }

  int read()
  {
    up();
    value = analogRead(reader);
    down();
    delay(1);
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
      sendCC
    }
    
  }
};
