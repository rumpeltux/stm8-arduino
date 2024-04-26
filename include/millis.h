#include <stdint.h>

// Returns the number of milliseconds since first calling this function.
// Wraps to 0 after 65.5s (limitation of the timer & data type).
// TODO: work around this by counting the TIM1 overflow interrupt
uint16_t millis(void);