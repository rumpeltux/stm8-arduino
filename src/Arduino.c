#include "Arduino.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm8.h"

uint8_t arduino_pending_events = 0;
void (*isr_callbacks[4])() = {(void *)0, (void *)0, (void *)0, (void *)0};

void handle_events() {
  sim();
  if (!arduino_pending_events) return;
  // Current pending events will be handled in this loop.
  // Handling them may cause new events to be submitted.
  // Those will be handled in the next call of this function (which may be nested).
  uint8_t events = arduino_pending_events;
  arduino_pending_events = 0;
  for (uint8_t i = 0, mask = 1; i < 4; i++, mask <<= 1) {
    if ((events & mask) != 0 && isr_callbacks[i]) {
      // enable interrupts, allows recording new events for the event loop
      rim();
      isr_callbacks[i]();
      sim();
    }
  }
}

void yield() {
  handle_events();
  rim();
}
