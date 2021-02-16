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

#define blocking_getchar() \
    do { \
        ch_read = getchar_timeout_us(1000); \
    } while ((ch_read == '\0') || (ch_read == 0xff))

bool abend_tripped = false;

// unsigned int getKey(void) {     // hardware-independent wrapper
uint8_t getKey(void) {     // hardware-independent wrapper
    uint8_t ch_read = (uint8_t) 'c';

    if ( ! abend_tripped ) {

        // ch_read = getchar();
        blocking_getchar();
        // do {
            // ch_read = getchar_timeout_us(1000);
        // } while ch_read == '\0';

        if_chread_bad_chars() {
            error_null_from_getchar();
            // ch_read = getchar();
            blocking_getchar();
            // ch_read = getchar_timeout_us(1000);
            if_chread_bad_chars() {
                putchar(' '); putchar('2'); putchar('2'); putchar(':');
                error_null_from_getchar();
                // ch_read = getchar();
                blocking_getchar();
                // ch_read = getchar_timeout_us(1000);
                if_chread_bad_chars() {
                    putchar(' '); putchar('3'); putchar('3'); putchar(':');
                    error_null_from_getchar();
                    // run = 0; // can this work?
                    error_no_more_run();
                    abend_tripped = true ;
                    do {
                        // ch_read = getchar(); // some good chars may arrive in the stream of 0xff bad chars
                        // ch_read = getchar_timeout_us(1000);
                        blocking_getchar();
                    } while (( ch_read == '\0' ) || ( ch_read == 0xff ));
                }
            }
        }
    }
    else { // alright already it's an abend don't keep announcing it
        do {
            // ch_read = getchar_timeout_us(1000);
            blocking_getchar();
        } while (( ch_read == '\0' ) || ( ch_read == 0xff ));
    }

    return ch_read;
}

// int getchar_timeout_us(uint32_t timeout_us)

void queryKey(void) {
    // TODO wa1tnr
}
