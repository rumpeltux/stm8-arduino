#include <stdio.h>

#include "Arduino.h"
#include "stm8.h"

uint8_t counter;

void setup(void) {
  SERIAL_INIT(9600);
  puts("STM8S-Arduino demo started");
  pinMode(DEVBOARD_LED, OUTPUT);
}

void loop(void) {
  digitalWrite(DEVBOARD_LED,
               counter % 2 == 0 ? DEVBOARD_LED_ON : DEVBOARD_LED_OFF);
  counter++;
  delay(1000);
}
