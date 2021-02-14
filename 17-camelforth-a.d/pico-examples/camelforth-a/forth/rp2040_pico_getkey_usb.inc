#include "rp2040_pico.h"
// #include "hardware/watchdog.h"

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

void error_no_more_run(void) {
    // watchdog_enable(100, 0);
    escLSQ0();
    putchar(';');
    putchar('1');
    putchar(';');
    putchar('3');
    putchar('1');
    putchar(';');
    putchar('4');
    putchar('0');
    putchar('m');

    putchar('\n');
    putchar('\r');
    putchar(' ');
    putchar(' ');
    putchar('A');
    putchar('B');
    putchar('E');
    putchar('N');
    putchar('D');
    putchar(' ');
    putchar(' ');
    escLSQ0(); putchar('m');
}

/*
 71 #define printf(format,integer) \
 72     length_print_string = 0; \
 73     print_string[0] = (uint32_t) "\0"; \
 74     sprintf(print_string, format, integer); \
 75     length_print_string = strlen(print_string); \
 76         chopped_acm_write(print_string)
*/

// possibly a good capture - showed all 'FF' in the 'less' $PAGER linux

// <FF><FF><FF> like that


#define if_chread_bad_chars() \
    if ( \
        ( ch_read == '\0' ) || \
        ( ch_read == 0xff ) \
       )
/*
        ( ch_read == 0xef )   || \
        ( ch_read == 0xbf )   || \
        ( ch_read == 0xfe )   || \
        ( ch_read == 0xff )   || \
        ( ch_read == 0xbd ) \
       )
*/

// extern tusb_init();

/* in finger quotes only: */
// i.e. not a race condition per se, possibly.
/*
void usb_race_reinit(void) {
    // extern bool tud_init (void);
    bool tud_is_init = false ;
    tud_is_init = tud_init();
    if (tud_init()) { run = 1; } // now really wild guessin
}
*/
    /* the idea: let the human re-init tusb under the compromised interpreter loop paradigm */

// unsigned int getKey(void) {     // hardware-independent wrapper
uint8_t getKey(void) {     // hardware-independent wrapper
    // uint8_t ch_read = (uint32_t) 'c';
    uint8_t ch_read = (uint8_t) 'c';
    ch_read = getchar();

    if_chread_bad_chars() {
        error_null_from_getchar();
        error_null_from_getchar();
        ch_read = getchar();
        // if (ch_read == '\0') {
        if_chread_bad_chars() {
            putchar(' '); putchar('2'); putchar('2'); putchar(':'); putchar(' ');
            error_null_from_getchar();
            ch_read = getchar();
            // if (ch_read == '\0') {
            if_chread_bad_chars() {
                putchar(' '); putchar('3'); putchar('3'); putchar(':'); putchar(' ');
                error_null_from_getchar();
                run = 0; // can this work?
                error_no_more_run(); // setups watchdog which isn't the case ordinarily
                // bool is_badchar = false;
                // is_badchar = true;

                // some good chars may arrive in the stream of 0xff bad chars
                do {
                    ch_read = getchar();
                    // while this loops past 100 ms the watchdog will expire
                } while (( ch_read == '\0' ) || ( ch_read == 0xff ));
                // watchdog_update(); // if the bad chars abate

                // expected: an escape to a good instance of keyboard read,
                    //  from the 'do .. while' loop.

                run = 1; // not sure manipulation of 'run' does anything useful here

                // usb_race_reinit();
                // ch_read = '\040' ; // harmless space char
                // return ch_read; // questionable return path
                // while(1); // three strikes
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
