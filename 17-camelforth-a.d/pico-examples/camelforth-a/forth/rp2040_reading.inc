// rp2040_reading.inc

// read keyboard store in RAM leave address where it was stored but no count

#define READING_BYTES_COUNT 2044

char buffer[2048];

CODE(reading) {
    uint32_t location = (uint32_t) &buffer[0];
    int bufpos = 0;
    uint8_t ch_read;
    --psp; psp[0] = (uint32_t) location; // push location
    int count=0;
    int flip, flop;
    const uint LED_PIN = 25;
    flip=-1;
    for (int i = READING_BYTES_COUNT ; i > 0 ; i--) { // marker BBFB 


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
    if (
        (ch_read == ' ') || (ch_read == '0') || (ch_read == '1') || (ch_read == '2') ||
        (ch_read == '3') || (ch_read == '4') || (ch_read == '5') || (ch_read == '6') ||
        (ch_read == '7') || (ch_read == '8') || (ch_read == '9') || (ch_read == 'a') ||
        (ch_read == 'b') || (ch_read == 'c') || (ch_read == 'd') || (ch_read == 'e') ||
        (ch_read == 'f') || (ch_read == 'g') || (ch_read == 'h') || (ch_read == 'i') ||
        (ch_read == 'j') || (ch_read == 'k') || (ch_read == 'l') || (ch_read == 'm') ||
        (ch_read == 'n') || (ch_read == 'o') || (ch_read == 'p') || (ch_read == 'q') ||
        (ch_read == 'r') || (ch_read == 's') || (ch_read == 't') || (ch_read == 'u') ||
        (ch_read == 'v') || (ch_read == 'w') || (ch_read == 'x') ||
        (ch_read == 'y') ||
        (ch_read == 'z') ||
        (ch_read == 'I') ||
        (ch_read == '.') ||
        (ch_read == ',') ||
        (ch_read == ':') ||
        (ch_read == ';') ||
        (ch_read == '"') ||
        (ch_read == ')') ||
        (ch_read == '(') ||
        (ch_read == '\n') ||
        (ch_read == '?')
       ) { // marker CCEC
        buffer[bufpos++] = ch_read;
        // emit keystroke somehow
        putch((char) ch_read); // may be OUT OF BAND - no thought put into this
    } // marker CCEC
    
    } // marker BBFB
}

// END.
