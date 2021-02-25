// flash.inc - first instance of this file 25 Feb 11:49z
// No TYPOS are expected to be present.

//  ok HEX 100 400 * DECIMAL . 262144

//  ok HEX 100 400 * 10000000 + . 10040000

// straight out of the SDK manual

// designed to be an inline include of forth.c

// - - - - - - - - - - - - - - - - - - - - - - - - -
//   special NOTE:
// - - - - - - - - - - - - - - - - - - - - - - - - -
//   The old version of the program stays in flash,
//   when no_flash is used wrt current binary.
// - - - - - - - - - - - - - - - - - - - - - - - - -

// So, after compiling a ram-only program
// and uploading the corresponding UF2,
// and you need to cycle power for any reason,
// the target still boots from the older
// (or 'resident') version.

// Rpi Pico RP2040 SDK:
// #include <stdio.h> // found already in forth.c
#include "pico/stdio.h"
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
// We're going to erase and reprogram a region 256k from the start of flash.
// Once done, we can access this at XIP_BASE + 256k.
#define FLASH_TARGET_OFFSET (256 * 1024)

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
}

void flash_write_test(void) {
    stdio_init_all();
    uint8_t random_data[FLASH_PAGE_SIZE];
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i)
        random_data[i] = rand() >> 16;

    printf("Generated random data:\n");
    print_buf(random_data, FLASH_PAGE_SIZE);

    // Note that a whole number of sectors must be erased at a time.
    printf("\nErasing target region...\n");
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    printf("Done. Read back target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    printf("\nProgramming target region...\n");
    flash_range_program(FLASH_TARGET_OFFSET, random_data, FLASH_PAGE_SIZE);
    printf("Done. Read back target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    bool mismatch = false;
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
        if (random_data[i] != flash_target_contents[i])
            mismatch = true;
    }
    if (mismatch)
        printf("Programming failed!\n");
    else
        printf("Programming successful!\n");

        printf("%s", "\n\n            XIP_BASE: ");
        printf("%8X",   (uint32_t) XIP_BASE);

        printf("%s", "\n\n FLASH_TARGET_OFFSET: ");
        printf("%8X", (uint32_t) FLASH_TARGET_OFFSET);

        uint32_t start_address = (uint32_t) XIP_BASE + (uint32_t) FLASH_TARGET_OFFSET ;

        printf("%s", "\n\n       start_address: ");
        printf("%8X", start_address);

        printf("%s", "\n\n");
}

// END.
