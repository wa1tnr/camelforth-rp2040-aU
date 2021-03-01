// flash.inc
// Sat Feb 27 23:45:07 UTC 2021

// designed to be an inline include of forth.c

// Rpi Pico RP2040 SDK:
#include "pico/stdio.h"
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"

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

CODE(erase) { // ( offset -- address bool ) // address only valid if bool returned as true
    bool debug = -0;
    stdio_init_all();
    if (debug) printf("\nErasing target sector...\n");

    if (debug) printf("\nv.000\n");

    uint32_t tos = (uint32_t) psp[0]; psp++; // pop
    uint32_t tos_cpy;
    tos_cpy = tos;
    if (tos_cpy > 0x1FFFFF) {
        // reject overrange flash addresses
        if (tos_cpy > 0x101FFFFF) {
            if (debug) printf("ERROR .. flash address too large\n");
            --psp; psp[0] = tos_cpy; // push rejected address
            --psp; psp[0] = 0; // push failure to write flag
            return;
        }

        // reject overrange flash offsets
        if (tos_cpy < 0x10000000) {
            if (debug) printf("ERROR .. flash offset too large\n");
            --psp; psp[0] = tos_cpy;
            --psp; psp[0] = 0;
            return;
        }
    }

    uint32_t offset = tos & 0x1FF000;
    tos = offset + 0x10000000;
    --psp; psp[0] = tos;
    if (debug) {
        printf("DEBUG: offset: %6X with", offset);
        printf(" %d %s", FLASH_SECTOR_SIZE, "bytes erased at ");
        printf("%8X\n", tos);
    }
    flash_range_erase(offset, FLASH_SECTOR_SIZE);
    --psp; psp[0] = -1;
    if (debug) printf("Done. Exiting the 'erase' word.\n");
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
