#include "rp2040_pico.h"
// #include "hardware/watchdog.h"

void escLSQ0(void) {
    putchar('\033'); // esc
    putchar('[');
    putchar('0');
}

void error_null_from_getchar(void) {
    escLSQ0(); putchar(';');
    putchar('1'); putchar(';');
    putchar('3'); putchar('2'); putchar(';');
    putchar('4'); putchar('0'); putchar('m');

    putchar('\n'); putchar('\r');
    putchar(' '); putchar(' ');
    putchar('E'); putchar('r'); putchar('r'); putchar('o'); putchar('r');
    putchar(' '); putchar(' ');
    escLSQ0(); putchar('m');
}

void error_no_more_run(void) {
    // watchdog_enable(100, 0);
    escLSQ0(); putchar(';');
    putchar('1'); putchar(';');
    putchar('3'); putchar('1'); putchar(';');
    putchar('4'); putchar('0'); putchar('m');

    putchar('\n'); putchar('\r');
    putchar(' '); putchar(' ');
    putchar('A'); putchar('B'); putchar('E'); putchar('N'); putchar('D');
    putchar(' '); putchar(' ');
    escLSQ0(); putchar('m');
}

// possibly a good capture - showed all 'FF' in the 'less' $PAGER linux

// <FF><FF><FF> like that


#define if_chread_bad_chars() \
    if ( \
        ( ch_read == '\0' ) || \
        ( ch_read == 0xff ) \
       )

// unsigned int getKey(void) {     // hardware-independent wrapper
uint8_t getKey(void) {     // hardware-independent wrapper
    // uint8_t ch_read = (uint32_t) 'c';
    uint8_t ch_read = (uint8_t) 'c';
    ch_read = getchar();

    if_chread_bad_chars() {
        error_null_from_getchar();
        error_null_from_getchar();
        ch_read = getchar();
        if_chread_bad_chars() {
            putchar(' '); putchar('2'); putchar('2'); putchar(':'); putchar(' ');
            error_null_from_getchar();
            ch_read = getchar();
            if_chread_bad_chars() {
                putchar(' '); putchar('3'); putchar('3'); putchar(':'); putchar(' ');
                error_null_from_getchar();
                run = 0; // can this work?
                error_no_more_run();

                // some good chars may arrive in the stream of 0xff bad chars
                do {
                    ch_read = getchar();
                } while (( ch_read == '\0' ) || ( ch_read == 0xff ));

                // expected: an escape to a good instance of keyboard read,
                    //  from the 'do .. while' loop.

                run = 1; // not sure manipulation of 'run' does anything useful here

                // ch_read = '\040' ; // harmless space char
                // return ch_read; // questionable return path
                // while(1); // three strikes
            }
        }
    }
    // uncomment for local echo, maybe:
    // putchar(ch_read);
    return ch_read;
}
void queryKey(void) {
    // TODO wa1tnr
}
