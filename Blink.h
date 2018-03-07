#include <Arduino.h>

class Blink
{
  public:
    blink(int pin);
    void on(int delay);
    void off(int delay);
   private:
    int _pin;
}
