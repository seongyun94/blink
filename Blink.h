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
    void on(int delay);
    void off(int delay);
   private:
    int _pin;
};

#endif
