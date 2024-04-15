#include "SPI.h"

#include <stdio.h>

#include "stm8.h"

void spi_begin(void) {
  // SPI port setup: MISO is pullup in, MOSI & SCK are push-pull out
  PC_DDR |= PIN5 | PIN6;  // clock and MOSI
  PC_CR1 |= PIN5 | PIN6 | PIN7;

  // SPI registers: First reset everything
  // SPI_CR1 LSBFIRST=0 (MSB is transmitted first)
  // SPI_CR1 CPOL=0 (Clock Phase, The first clock transition is the first data
  // capture edge) SPI_CR1 CPHA=0 (Clock Polarity, SCK to 0 when idle) CR1 bit 2
  // MSTR = 1, Master configuration. Baud Rate Control: 0x2 = fmaster / 8 (2MHz)
  // Baud Rate Control: 0x7 = fmaster / 256 (62,500 baud)
  SPI_CR1 = SPI_CR1_BR(0x7) | SPI_CR1_MSTR;
  // bit 1 SSM=1 Software slave management, enabled
  // bit 0 SSI=1 Internal slave select, Master mode
  SPI_CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
}

void spi_end(void) {
  SPI_CR1 &= ~SPI_CR1_SPE;  // Disable SPI
}

uint8_t spi_transfer(uint8_t data) {
  // MSTR = 1, Master device.
  // SPE, SPI Enable, Peripheral enabled
  SPI_CR1 |= SPI_CR1_SPE;
  while ((SPI_SR & SPI_SR_TXE) == 0)
    ;  // TX buffer not yet empty
  SPI_DR = data;
  while ((SPI_SR & SPI_SR_RxNE) == 0)
    ;  // No byte yet received.
  uint8_t val = SPI_DR;
  return val;
}
