#include "rp2040_pico.h"

uint8_t getKey(void) {     // hardware-independent wrapper
    uint8_t ch_read;
    do {
        ch_read = getchar_timeout_us(1000);
    } while ((ch_read == '\0') || (ch_read == 0xff));
    return ch_read;
}

void queryKey(void) {
    // TODO wa1tnr
}
