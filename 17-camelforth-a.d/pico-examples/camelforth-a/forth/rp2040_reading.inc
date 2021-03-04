// rp2040_reading.inc

// read keyboard store in RAM leave address where it was stored but no count

#define READING_SIZE 2048

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
    for (int i = (READING_SIZE - 4) ; i > 0 ; i--) { // marker BBFB


    do {
        count++;
        //           0x1FFFF  every 3 seconds or so

    //  if (count == 0x3FFFF) { // every 20 seconds or so
        if (count == 0x3F) { // squibb
            // printf("."); // suppress this except for testing
            count = 0;
            if (flip == -1) {
           /*   gpio_put(LED_PIN, 1); */
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
    // return ch_read;
    ch_test = ch_read;
    if (
        (   // contiguous range of chars permitted
            (ch_test > 0x1F) && (ch_test < 0x7F) // space ' ' through tilde '~' 0x76 is 'v'
        ) ||
        (   // list of the out-of-sequence chars permitted
            (ch_test == '\010') || // backspace 0x08
            (ch_test == '\t') ||   // tab       0x09
            (ch_test == '\n')      // newline   0x0A
        )
/*
        (ch_read == ' ') || (ch_read == '0') || (ch_read == '1') || (ch_read == '2') ||
        .
        .
        (ch_read == 'v') || (ch_read == 'w') || (ch_read == 'x') || (ch_read == 'y') ||
        .
        .
        (ch_read == '\n') ||
        (ch_read == '?')
*/
       ) { // marker CCEC
        buffer[bufpos++] = ch_read;

        // emit keystroke somehow
        putch((char) ch_read); // may be OUT OF BAND - no thought put into this
    } // marker CCEC
    
    } // marker BBFB
}

// END.
