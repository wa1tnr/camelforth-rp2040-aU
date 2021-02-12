#include "rp2040_pico.h"

void escLSQ0(void) {
    putchar('\033'); // esc
    putchar('[');
    putchar('0');
}

void error_null_from_getchar(void) {
    escLSQ0();
    putchar(';');
    putchar('1');
    putchar(';');
    putchar('3');
    putchar('2');
    putchar(';');
    putchar('4');
    putchar('0');
    putchar('m');

    putchar('\n');
    putchar('\r');
    putchar(' ');
    putchar(' ');
    putchar('E');
    putchar('r');
    putchar('r');
    putchar('o');
    putchar('r');
    putchar(' ');
    putchar(' ');
    escLSQ0(); putchar('m');
}

// unsigned int getKey(void) {     // hardware-independent wrapper
uint8_t getKey(void) {     // hardware-independent wrapper
    // uint8_t ch_read = (uint32_t) 'c';
    uint8_t ch_read = (uint8_t) 'c';
    ch_read = getchar();
    if (ch_read == '\0') {
        error_null_from_getchar();
        error_null_from_getchar();
        ch_read = getchar();
        if (ch_read == '\0') {
            putchar(' '); putchar('2'); putchar('2'); putchar(':'); putchar(' ');
            error_null_from_getchar();
            ch_read = getchar();
            if (ch_read == '\0') {
                putchar(' '); putchar('3'); putchar('3'); putchar(':'); putchar(' ');
                error_null_from_getchar();
                while(1); // three strikes
            }
        }
    }
    // error_null_from_getchar(); // testing only
    // uncomment for local echo, maybe:
    // putchar(ch_read);
    return ch_read;
}
void queryKey(void) {
    // TODO wa1tnr
}
