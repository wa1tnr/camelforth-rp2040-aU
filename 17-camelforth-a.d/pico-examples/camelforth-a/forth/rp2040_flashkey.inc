// Sun Mar  7 16:57:29 UTC 2021
#include "rp2040_pico.h"
#include "pico/stdlib.h"
#define FL_KEY_BASE 0x10040000 // same as example code SDK

// uint32_t getFlKey_counter = 0;

uint8_t getFlKey(void) {     // hardware-independent wrapper
    uint8_t ch_read;
    int count=0;
    // uint32_t getFlKey_counter = 0;
    int flip, flop;
    const uint LED_PIN = 25;
    flip=-1;
    do {
        count++;
        //           0x1FFFF  every 3 seconds or so

        if (count == 0x3FFFF) { // every 20 seconds or so
            // printf("."); // suppress this except for testing
            count = 0;
            if (flip == -1) {
                gpio_put(LED_PIN, 1);
                sleep_ms(1);
                gpio_put(LED_PIN, 0);
            }
         // if (flip ==  0) { gpio_put(LED_PIN, 0); }
            int flop = flip;
            if (flop == -1) flip =  0;
            if (flop ==  0) flip = -1;
        }
        ch_read = getchar_timeout_us(18); // 4 tries per 87 uSec char window at 115200 bps
    } while ((ch_read == '\0') || (ch_read == 0xff));
    getFlKey_counter++;
    return ch_read;
}

// END.
