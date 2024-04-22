#include "gpio.h"

#include "stm8.h"

#define OFFSET_ODR 0
#define OFFSET_IDR 1
#define OFFSET_DDR 2
#define OFFSET_CR1 3

#define OFFSET_NEXT 5

void gpioSetBit(uint8_t port_offset, uint8_t pin, uint8_t set) {
  volatile uint8_t *ptr = &PA_ODR + port_offset + OFFSET_NEXT * (pin >> 4);
  pin = 1 << (pin & 7);
  if (set) {
    *ptr |= pin;
  } else {
    *ptr &= ~pin;
  }
}

void pinMode(uint8_t pin, uint8_t mode) {
  gpioSetBit(OFFSET_DDR, pin, mode & GPIO_OUTPUT);
  gpioSetBit(OFFSET_CR1, pin, mode & GPIO_CR1);
}

void digitalWrite(uint8_t pin, uint8_t value) {
  gpioSetBit(OFFSET_ODR, pin, value);
}

uint8_t digitalRead(uint8_t pin) {
  volatile uint8_t *ptr = &PA_ODR + OFFSET_IDR + OFFSET_NEXT * (pin >> 4);
  pin = 1 << (pin & 7);
  return *ptr & pin ? 1 : 0;
}
