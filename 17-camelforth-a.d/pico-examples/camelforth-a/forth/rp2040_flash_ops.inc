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

/*
void erase_sector(void) {
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
}
*/

#define FL_LIMIT_2MB        0x1E8000

CODE(erase) {                    /* adr n -- */
    stdio_init_all();
    printf("\nErasing target sector...\n");

    uint32_t j = (uint32_t) psp[0]; // psp++; // pop?

    if (j < 0x10000000) { printf("ERROR in flash ops: TOS too small\n"); return; }
    if (j > (0x10000000 + FL_LIMIT_2MB)) { printf("ERROR in flash ops: TOS too large\n"); return; }

    uint32_t k = j - 0x10000000; // remove XIP_BASE to get just the offset

// #WARNING switched to && from &

             j = k && 0x1FF000; // align to 4096 byte boundaries

             if (j > FL_LIMIT_2MB) { printf("Unexpected error.\n"); return; }

             k = j;

    if (k < 0) { printf("ERROR in flash ops: less than zero from XIP_BASE\n"); return; }

    if (k < FL_LIMIT_2MB) { // 0x1FF000) {

        // printf("DEBUG: %8X", k); printf("%s", " was number input.\n");

        if (k > -1) { // 0 as a > test value here, is a C coding error
            flash_range_erase((uint32_t)k, FLASH_SECTOR_SIZE);
        } else {
            printf("Unexpected error .. exiting early.\n"); // seen this when k > 0 test performed
            return;
        }
        printf("Done. Exiting the 'erase' word.\n");
        return;
    } else {
        printf("Nothing done - input error.  k too large.\n");
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
