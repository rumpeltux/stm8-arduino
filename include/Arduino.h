#include <stdint.h>

#include "SPI.h"
#include "adc.h"
#include "delay.h"
#include "gpio.h"
#include "serial.h"

#define false 0
#define true 1
#define LOW 0
#define HIGH 1

#define B111 0x7
#define B1000 0x8

void handle_events();
void yield();

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) \
  (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
