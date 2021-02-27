// Mon Feb  8 18:39:16 UTC 2021
// wa1tnr
// camelforth

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdio.h"     // rp2040_flash_ops.inc
#include <stdlib.h>         // rp2040_flash_ops.inc
#include "pico/stdlib.h"
#include "hardware/flash.h" // rp2040_flash_ops.inc

// #define FLASH_TARGET_OFFSET_B (256 * 1024)
#define FLASH_TARGET_OFFSET_B (0x1E0000)

// super kludge to do this here this way 27 Feb 2021:
const uint8_t *flash_target_contents_b = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET_B);


/// \tag::hello_uart[]

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1
extern void interpreter(void);
extern void crufty_printer(void);
extern int _pico_LED(void);

int main(void) {
    sleep_ms(1800);
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    stdio_init_all();

    // uart_putc_raw(UART_ID, 'A');

    sleep_ms(800);
    for (int i=3;i>0;i--) _pico_LED();
    uart_puts(UART_ID, "\r\n\r\n   camelforth-rp2040-aU r0.1.4-pre-alpha\r\n\r\n");
    printf(            "\r\n\r\n   camelforth-rp2040-aU r0.1.4-pre-alpha\r\n\r\n");

    uart_puts(UART_ID, "        +erase +flwrite +reflash +dump +blink +UART +USB\r\n");
    printf(            "        +erase +flwrite +reflash +dump +blink +UART +USB\r\n");

    crufty_printer(); // examine ram with this nonsense function
    stdio_init_all(); // flash doesn't alway initialize esp no_flash builds
    // uint8_t random_data[FLASH_PAGE_SIZE];
    // for (int i = 0; i < FLASH_PAGE_SIZE; ++i) random_data[i] = rand() >> 16;
    flash_range_erase(FLASH_TARGET_OFFSET_B, FLASH_SECTOR_SIZE);
    printf("flash_range_erase is required (and completed).\n");

    // the SDK does not provide a work-around - flash must be written to, on every no_flash boot!
    // otherwise, cannot read from flash.  flwrite word alternate path to what was done, here.

    // flash_range_program(FLASH_TARGET_OFFSET_B, random_data, FLASH_PAGE_SIZE);
/*
    bool mismatch = false;
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
        if (random_data[i] != flash_target_contents_b[i])
            mismatch = true;
    }

    if (mismatch)
        // printf("flash test failed!\n");
        printf("xnx");
    else
        // printf("flash test successful!\n");
        printf(".");
*/


/*
        printf("%s", "\n\n            XIP_BASE: ");
        printf("%8X",   (uint32_t) XIP_BASE);

        printf("%s", "\n\n FLASH_TARGET_OFFSET_B: ");
        printf("%8X", (uint32_t) FLASH_TARGET_OFFSET_B);


*/
        uint32_t start_address = (uint32_t) XIP_BASE + (uint32_t) FLASH_TARGET_OFFSET_B ;
        printf("%s", "\n\n       start_address: ");
        printf("%8X", start_address);

        printf("%s", "\n");

    while(1) {
        // _pico_LED(); // test using GPIO hardware to blink Pi Pico onboard LED
        interpreter(); // camelforth
    }
}

/// \end::hello_uart[]
