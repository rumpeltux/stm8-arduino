#include <stdint.h>

void spi_begin(void);
void spi_end(void);
uint8_t spi_transfer(uint8_t data);
