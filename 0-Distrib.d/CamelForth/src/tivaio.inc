/****h* camelforth/tivaio.c
 * NAME
 *  tivaio.c
 * DESCRIPTION
 *  Terminal I/O, MCU initialization, and main entry point for 
 *  CamelForth in C, for the TM4C1294XL Tiva-C Launchpad.
 * SYNOPSIS
 *  Provides the functions
 *      void putch(char c)      write one character to terminal
 *      char getch(void)        await/read one character from keyboard
 *      int getquery(void)      return true if keyboard char available
 *      void initTermios(void)  configure terminal for Forth
 *      void resetTermios(void) reset terminal configuration, if req'd
 *      int main(void)          main entry point for Tiva-C
 * AUTHOR
 *  Brad Rodriguez
 ******
 * LICENSE TERMS
 *  CamelForth in C 
 *  copyright (c) 2016,2017 Bradford J. Rodriguez.
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 *  Commercial inquiries should be directed to the author at 
 *  115 First St., #105, Collingwood, Ontario L9Y 4W3 Canada
 *  or via email to bj@camelforth.com
 */

#include <stdint.h>
#include <stdbool.h>
#define NULL 0

/* TivaWare functions */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "drivers/pinout.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

/* Use SYSCTL_XTAL_25MHZ for TM4C129 Launchpad. */
#define SYSCTL_XTAL_MHZ SYSCTL_XTAL_25MHZ


/****f* main/ConfigureUART
 * NAME
 *  ConfigureUART
 * SYNOPSIS
 *  void ConfigureUART(uint32_t clockfreq)
 * DESCRIPTION
 *  Configure UART and its pins, for 115200 baud using main system clock.
 * NOTES
 *  Based on a function provided by Texas Instruments;
 *  modified to accept clockfreq as a parameter.
 ******
 */

void ConfigureUART(uint32_t clockfreq)
{
    // Enable the GPIO Peripheral used by the UART.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Enable UART0.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure GPIO Pins for UART mode.
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Initialize the UART for terminal I/O at 115.2 Kbaud
    UARTStdioConfig(0, 115200, clockfreq);
}

/*
 * Terminal I/O functions
 */

#define printf UARTprintf
#define getch UARTgetc

void putch(char c) {
    UARTwrite(&c, 1);        
}

int getquery(void) {
    return(UARTCharsAvail(UART0_BASE) != 0);
}

/****f* main/main
 * NAME
 *  main
 * SYNOPSIS
 *  int main(void)
 * DESCRIPTION
 *  Main program, entered after an MCU reset.
 ******
 */

uint32_t g_ui32SysClock;        /* global variable */

void interpreter(void);         /* forward reference */

int main(void)
{
    // ----- THE FOLLOWING IS ADAPATED FROM TI INITIALIZATION CODE -----

    // Set the clocking to run from the crystal at 120MHz.
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);   

    // Initialize Launchpad-specific I/O
    // Enable the GPIO port that is used for the on-board LEDs.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    // Enable the GPIO pins for the LEDs (PN0 & PN1).
    // initially PN0 off, PN1 on
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ROM_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_1);
    
    // Initialize UART0 for terminal I/O
    ConfigureUART(g_ui32SysClock);  // this enables UART0 and GPIOA.
    
    // ------------- END OF ADAPTED TI INITIALIZATION CODE -------------

    while (1) {     /* loop in case interpreter() ever terminates */
        UARTprintf("\nCamelForth in C - Tiva-C testing\n");
        interpreter();
    }
}
