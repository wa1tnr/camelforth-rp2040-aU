# camelforth-rp2040-aU   UNSTABLE   0.1.3-pre-alpha   Wed Feb 10 04:08:51 UTC 2021

UNSTABLE version - new feature: LED blinking.

CamelForth in C, by Dr. Brad Rodriguez

Reasonably well debugged - functional Forth interpreter.

There is one bug where it crashes unexpectedly, after
a decently long runtime.  maybe 'run' gets set by .. don't know.

Seems to print endless nulls '@' but have not captured to
log to verify that's what it is.

Port: rp2040, Raspberry Pi Pico target board, February, 2021.

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
