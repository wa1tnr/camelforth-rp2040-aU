// rp2040_reflash.inc

// reflash();

#include "pico/bootrom.h"
extern void reflash(void);
CODE(reflash) {  /*  --  */
    reset_usb_boot(0, 0);
}
