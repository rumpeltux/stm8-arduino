#include <stdint.h>

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
uint8_t digitalRead(uint8_t pin);

// WARNING: there can always only be one callback function per port!
// The sensitivity (type) is also per port.
extern void attachInterrupt(uint8_t pin, void (*callback)(), uint8_t type);
extern void detachInterrupt(uint8_t pin);

#define RISING 1
#define FALLING 2

#define digitalPinToInterrupt(x) (x)

#define GPIO_DDR               0x01
#define GPIO_INPUT             (GPIO_DDR & 0x00)
#define GPIO_OUTPUT            (GPIO_DDR & 0x01)
#define GPIO_CR1               0x02
#define GPIO_FLOATING          (GPIO_CR1 & 0x00)
#define GPIO_PULLUP            (GPIO_CR1 & 0x02)
#define GPIO_OPENDRAIN         (GPIO_CR1 & 0x00)
#define GPIO_PUSHPULL          (GPIO_CR1 & 0x02)

#define INPUT_FLOATING (GPIO_INPUT | GPIO_FLOATING)
#define INPUT_PULLUP (GPIO_INPUT | GPIO_PULLUP)
#define INPUT INPUT_FLOATING
#define OUTPUT (GPIO_OUTPUT | GPIO_PUSHPULL)

// STM8S PINs
#define A0 0x00
#define A1 0x01
#define A2 0x02
#define A3 0x03
#define A4 0x04
#define A5 0x05
#define A6 0x06
#define A7 0x07
#define B0 0x10
#define B1 0x11
#define B2 0x12
#define B3 0x13
#define B4 0x14
#define B5 0x15
#define B6 0x16
#define B7 0x17
#define C0 0x20
#define C1 0x21
#define C2 0x22
#define C3 0x23
#define C4 0x24
#define C5 0x25
#define C6 0x26
#define C7 0x27
#define D0 0x30
#define D1 0x31
#define D2 0x32
#define D3 0x33
#define D4 0x34
#define D5 0x35
#define D6 0x36
#define D7 0x37

#define DEVBOARD_LED B5
#define DEVBOARD_LED_ON LOW
#define DEVBOARD_LED_OFF HIGH
