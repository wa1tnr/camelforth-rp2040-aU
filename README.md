# camelforth-rp2040-aU   UNSTABLE   0.1.4-pre-alpha   Tue Feb 16 15:34:07 UTC 2021

CamelForth in C, by Dr. Brad Rodriguez

UNSTABLE version

 new feature: no-error getKey()

     improved: rp2040_pico_getkey_usb.inc


Reasonably well debugged - functional Forth interpreter.

There was one bug where it crashes unexpectedly, after
a decently long runtime.  'getchar()' in the upstream
pico-sdk now has a bug report filed.

Port: rp2040, Raspberry Pi Pico target board, February, 2021.

older entries in this README.md, follows (from prior to 17 Feb Wed 16:29 UTC).


# PARENT was camelforth-rp2040-a    0.1.1-pre-alpha   Tue Feb 9 05:28:31 UTC 2021

commit 6cd03e97f38784f3f7fe8baf68416657af9469a7

    CamelForth in C by Brad Rodriguez

# About

CamelForth

A Forth in C by Dr Brad Rodriguez

Forth interpreter for the
RP2040 and Raspberry Pi Pico.

UNSTABLE version.  Look for changes and improvements here.

New feature: the blink word.  Use once per blink.

Requires pico-sdk and is modeled on pico-examples.

The /dev/ttyACM0 is the primary interface (USB).

(Reference host PC is Linux Debian amd64)

Using CP2104 USB-to-USART bridge, the secondary
interface (in Linux host PC) is /dev/ttyUSB0, but
that is arbitrary (you can bridge using other
methods and chips).

Connected to UART0 on the pico.

# Topics

# camelforth
# rp2040
# raspberry-pi-pico

# rpi-pico-pio

# forth
# c


## old branches:

BUILD ENVIRONMENT - bare bones text interpreter

no Forth functionality at all - not even base code.

Just keyboard echo loop.

END.
