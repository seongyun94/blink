#include "Arduino.h"
#include "Blink.h"

Blink::Blink(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Blink::on(int time)
{
  _time = time;
  digitalWrite(_pin, HIGH);
  delay(_time);
}

void Blink::off(int time)
{
  _time = time;
  digitalWrite(_pin, LOW);
  delay(_time);
}
