#include "gpio.h"
#include "stm8.h"

#define OFFSET_CR2 4

extern void (*isr_callbacks[4])(void);
extern void gpioSetBit(uint8_t port_offset, uint8_t pin, uint8_t set);

void attachInterrupt(uint8_t pin, void (*callback)(void), uint8_t type) {
  uint8_t port = pin >> 4;
  isr_callbacks[port] = callback;
  // Enable external interrupts and set the type (RISING | FALLING).
  port <<= 1;
  type = (type & 3) << port;
  uint8_t mask = 3 << port;
  uint8_t exti_value = (EXTI_CR1 & ~mask) | type;
  // EXTI can only be written while interrupts are disabled.
  __asm__("push cc");  // save interrupt state
  disableInterrupts();
  EXTI_CR1 = exti_value;
  __asm__("pop cc");  // restore interrupt state

  gpioSetBit(OFFSET_CR2, pin, 1);
}

void detachInterrupt(uint8_t pin) { gpioSetBit(OFFSET_CR2, pin, 0); }