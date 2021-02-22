// rp2040_runtime.inc

// runtime_init();  // does this work anything like COLD does in CamelForth?

// https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/pico_runtime/runtime.c

// try implement:

// https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/pico_runtime/runtime.c#L160
// #if PICO_ENTER_USB_BOOT_ON_EXIT

#include "pico/runtime.h"
extern void runtime_init(void);
CODE(runtime_init) {  /*  --  */
    runtime_init();
}
