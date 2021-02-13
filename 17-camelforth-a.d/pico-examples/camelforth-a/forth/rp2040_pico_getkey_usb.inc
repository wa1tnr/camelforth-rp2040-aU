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

void error_no_more_run(void) {
    // quit(); // does this exist?
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


// unsigned int getKey(void) {     // hardware-independent wrapper
uint8_t getKey(void) {     // hardware-independent wrapper
    // uint8_t ch_read = (uint32_t) 'c';
    uint8_t ch_read = (uint8_t) 'c';
    ch_read = getchar();

    if_chread_bad_chars() {

/*
    if (
        ( ch_read == '\0' )   ||
        ( ch_read == 0xef )   ||
        ( ch_read == 0xbf )   ||
        ( ch_read == 0xbd )
       ) {
*/

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
                error_no_more_run();
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
