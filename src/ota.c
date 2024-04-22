#include "stm8.h"
#include <stdint.h>
#include <string.h>

uint8_t writeFlashStart(void) {
  if ((FLASH_CR2 & FLASH_CR2_PRG) != 0)
    return 2;
  if ((FLASH_NCR2 & FLASH_CR2_PRG) == 0)
    return 3;
  FLASH_CR2 |= FLASH_CR2_PRG;
  FLASH_NCR2 &= ~FLASH_CR2_PRG;
  return 0;
}

uint8_t writeFlashFinish(void) {
  // busy wait until the block is fully written
  while (FLASH_IAPSR & FLASH_IAPSR_EOP == 0)
    ;
  // flash failed, page is write-protected
  if ((FLASH_IAPSR & FLASH_IAPSR_WR_PG_DIS) != 0)
    return 4;
  return 0;
}
// Writes a 64 byte block to flash.
// dst must be 64 byte aligned.
// Flash must be unlocked (unlockFlash()).
// Returns 0 on success.
uint8_t writeFlash64(void *dst, uint8_t *data) {
  if ((uint8_t)dst & 0x3f != 0)
    return 1;
  uint8_t res = writeFlashStart();
  if (!res)
    return res;

  memcpy(dst, data, 64);

  return writeFlashFinish();
}

// unlocks the data area (eeprom, option bytes)
uint8_t unlockFlashData(void) {
  FLASH_DUKR = 0xAE;
  FLASH_DUKR = 0x56;
  return FLASH_IAPSR & FLASH_IAPSR_DUL;
}

// unlocks the main program area
uint8_t unlockFlashProg(void) {
  FLASH_PUKR = 0x56;
  FLASH_PUKR = 0xAE;
  return FLASH_IAPSR & FLASH_IAPSR_PUL;
}