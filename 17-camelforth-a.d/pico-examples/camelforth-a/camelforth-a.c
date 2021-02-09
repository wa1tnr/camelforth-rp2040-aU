// Mon Feb  8 18:39:16 UTC 2021
// wa1tnr
// camelforth

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

/// \tag::hello_uart[]

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1
extern void interpreter(void);
extern int _pico_LED(void);

/*

char ch;

void _USB_read_tnr(void) {
    ch = getchar();

    // backspace primitives
    // also Ctrl J and Ctrl K are useful.
    if (ch == '\010') {
        uart_putc(UART_ID, '\010'); putchar('\010');
        return ;
    }

    uart_putc(UART_ID, ch); putchar(ch);

    // printf("%c", ch);
    // uart_putc(UART_ID, ch);
    // putchar() on /dev/ttyACM0 - USB
    // putchar('X');
}
*/

/*
void tryme() {
    ch = 'Q';
    _USB_read_tnr();
}
*/

/*
void looper() {

    tryme();
}
*/

int main() {
    sleep_ms(1800);
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    stdio_init_all();

    // uart_putc_raw(UART_ID, 'A');

    // uart_putc(UART_ID, 'B');
    sleep_ms(800);
    uart_puts(UART_ID, "\r\n\r\n   camelforth-rp2040-aU r0.1.2-pre-alpha\r\n\r\n");

    uart_puts(UART_ID, "    9 Feb good production build. +dump +blink +UART +USB\r\n");

    while(1) {
        // _pico_LED(); // test using GPIO hardware to blink Pi Pico onboard LED
        interpreter(); // camelforth
        // looper(); // called once and ran once ask asked ;)
    }
}

/// \end::hello_uart[]
