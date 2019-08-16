#include "Arduino.h"

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
   * Uses the value passed in when creating the potentiometer
   * for reading, this is generally A0-Ax depending on the
   * number of analog pins on your arduino. On an uno values of 
   * 14-19 correspond to A0-A5 and can be used instead. 
   * On a mega values of 82-97 correspond to A15-A0 with
   * 97 being A0 and 82 being A15
   */
    int read()
    {
      up();
      value = analogRead(reader)/8;
      down();
      delay(5);
      return value;
    }

  /*
   *To avoid saturating the interface this function checks a 
   *value to see if it is changed. No real point in sending values 
   *if they are not changed because this is using midiCC ONLY
   *and a send does not correspond to a played note but rather a 
   *change in a continous value.
   */
    bool changed()
    {
      uint8_t old = value;
      if (old != read())
      {
        return true;
      }
      return false;
    }
    
  /*
   * Print the values of the potentiometers, need to enable serial in main for this to work. 
   * Does NOT work with HIDUINO firmware and can mess things up if enabled while 
   * firmware is installed. Uncomment AT OWN RISK
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
