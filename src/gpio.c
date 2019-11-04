#include "gpio.h"

#include "stm8.h"

#define OFFSET_ODR 0
#define OFFSET_IDR 1
#define OFFSET_DDR 2
#define OFFSET_CR1 3
#define OFFSET_CR2 4
#define OFFSET_NEXT 5

extern void (*isr_callbacks[4])();

void setBit(uint8_t port_offset, uint8_t pin, uint8_t set) {
  volatile uint8_t *ptr = &PA_ODR + port_offset + OFFSET_NEXT * (pin >> 4);
  pin = 1 << (pin & 7);
  if (set) {
    *ptr |= pin;
  } else {
    *ptr &= ~pin;
  }
}

void pinMode(uint8_t pin, uint8_t mode) {
  setBit(OFFSET_DDR, pin, mode & GPIO_OUTPUT);
  setBit(OFFSET_CR1, pin, mode & GPIO_CR1);
}

void digitalWrite(uint8_t pin, uint8_t value) {
  setBit(OFFSET_ODR, pin, value);
}

void attachInterrupt(uint8_t pin, void (*callback)(), uint8_t type) {
  uint8_t port = pin >> 4;
  isr_callbacks[port] = callback;
  port <<= 1;
  type = (type & 3) << port;
  uint8_t mask = 3 << port;
  EXTI_CR1 = (EXTI_CR1 & ~mask) | type;
  setBit(OFFSET_CR2, pin, 1);
}

void detachInterrupt(uint8_t pin) { setBit(OFFSET_CR2, pin, 0); }