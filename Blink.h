/* 
  Blink.h - Library for Blink code.
*/
#ifndef Blink_h
#define Blink_h

#include <Arduino.h>

class Blink
{
  public:
    Blink(int pin);
    void on(int time);
    void off(int time);
  private:
    int _pin;
    int _time;
};

#endif
