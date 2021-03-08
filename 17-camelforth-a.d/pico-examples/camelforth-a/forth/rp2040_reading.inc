// rp2040_reading.inc

// Thu Mar  4 18:07:47 UTC 2021

// read keyboard store in ram 1023 bytes plus a terminating NULL '\0' for 1024 byte buffer

// #define READING_SIZE 1024
#define READING_SIZE 4096

char buffer[READING_SIZE];

CODE(reading) {
    uint32_t location = (uint32_t) &buffer[0];
    int bufpos = 0;
    uint8_t ch_read, ch_test;
    --psp; psp[0] = (uint32_t) location; // push location
    int count=0;
    int flip, flop;
    const uint LED_PIN = 25;
    flip=-1;
    for (int i = (READING_SIZE - 1) ; i > 0 ; i--) { // marker BBFB


    do {
        count++;

        if (count == 0x3F) { // squibb
            count = 0;
            if (flip == -1) {
                sleep_ms(1);
                gpio_put(LED_PIN, 0);
            }
            int flop = flip;
            if (flop == -1) flip =  0;
            if (flop ==  0) flip = -1;
        }
        ch_read = getchar_timeout_us(18); // 4 tries per 87 uSec char window at 115200 bps
    } while ((ch_read == '\0') || (ch_read == 0xff));
    ch_test = ch_read;
    if (
        (   // contiguous range of chars permitted
            (ch_test > 0x1F) && (ch_test < 0x7F) // space ' ' through tilde '~' 0x76 is 'v'
        ) ||
        (   // list of the out-of-sequence chars permitted
            (ch_test == '\010') || // backspace 0x08
            (ch_test == '\033') || // escape    0x1B // escape: beneficially premature EOF marker
            (ch_test == '\t') ||   // tab       0x09
            (ch_test == '\n')      // newline   0x0A
        )
       ) { // marker CCEC
        if (ch_read == '\033') {
            buffer[bufpos++] = '\0'; // mark eof
            printf(" ESC! ");
            return; // does this do harm?
        }
        buffer[bufpos++] = ch_read;
        putch((char) ch_read); // may be OUT OF BAND - no thought put into this
    } // marker CCEC
    
    } // marker BBFB
    buffer[bufpos] = '\0'; // mark eof
    putch('f'); putch('f'); putch(' ');

    putch('O'); putch('K'); putch(' ');
}

// END.
