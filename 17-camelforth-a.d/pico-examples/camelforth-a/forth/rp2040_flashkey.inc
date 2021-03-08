// Sun Mar  7 16:57:29 UTC 2021
#include "rp2040_pico.h"
#include "pico/stdlib.h"
#define FL_KEY_BASE 0x10040000 // same as example code SDK

// uint32_t getFlKey_counter = 0;

uint8_t acquire_flash_char() {
    char *rom;
    int p = ((int) 0x10040000 + (int) getFlKey_counter) ;
    rom = (char *) p;
    // printf("spot a: ");
    // printf("            %4X: ", p); // start address
    char char_read = *rom;
    // printf("spot b: ");
    // printf("%02X",  (char_read & 0xff));
    int qq = 0;
    // slow player piano // for (volatile uint32_t i = 0x1FFFFF; i>0; i--) {
    for (volatile uint32_t i = 0x1FF; i>0; i--) {
        qq++;
        // statement
    }
    qq = 0xA5;
    // printf("spot c: ");
    // printf(" %8X ", qq); // trick compiler into thinking qq is useful
    return (uint8_t) (char_read & 0xff);
}

uint8_t getFlKey(void) {     // hardware-independent wrapper
    uint8_t ch_read;
    ch_read = acquire_flash_char();
    getFlKey_counter++;
    return ch_read;
}

// END.
