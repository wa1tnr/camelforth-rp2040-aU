// rp2040_runtime.inc

// runtime_init();  // does this work anything like COLD does in CamelForth?

#include "pico/runtime.h"
extern void runtime_init(void);
CODE(runtime_init) {  /*  --  */
    runtime_init();
}
