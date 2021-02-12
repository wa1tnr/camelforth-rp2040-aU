#include "rp2040_pico.h"

void error_null_from_getchar(void) {
    putchar('\n');
    putchar('\r');
    putchar(' ');
    putchar(' ');
    putchar('E');
    putchar('R');
    putchar('r');
    putchar('o');
    putchar('o');
    putchar('r');
    putchar('r');
    putchar(' ');
    putchar(' ');
}

// unsigned int getKey(void) {     // hardware-independent wrapper
uint8_t getKey(void) {     // hardware-independent wrapper
    // uint8_t ch_read = (uint32_t) 'c';
    uint8_t ch_read = (uint8_t) 'c';
    ch_read = getchar();
    if (ch_read == '\0') { error_null_from_getchar(); }
    error_null_from_getchar(); // testing only
    // uncomment for local echo, maybe:
    // putchar(ch_read);
    return ch_read;
}
void queryKey(void) {
    // TODO wa1tnr
}
