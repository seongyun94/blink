#include <Blink.h>

Blink link(D4);

void setup() {
  Serial.begin(115200);
  Serial.println("\nBlink Version 1.0 Kim Seongyun");
}

void loop() {
  blink.on(500);
  blink.off(300);
}
