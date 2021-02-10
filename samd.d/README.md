# CamelForth-SAMD51-SAMD21
 
# NEWS
Wed Feb 10 03:53:02 UTC 2021

Ported to RP2040 Raspberry Pi Pico target.

SAMD21 and SAMD51 legacy notes, follow (reposted Feb 2021).

 - - -

Wed Jan  1 03:02:25 UTC 2020

Working: ItsyBitsyM4 variant - no real changes from
support already available for NeoTrellis M4.

CamelForth

  Please use ALL CAPS when addressing CamelForth.

http://camelforth.com/news.php

CamelForth in C!
Misc: Brad R @ Friday 15 December 2017 - 14:38:49

# Status

CamelForth is now running on ATSAMD51J19A SAMD51
via the USB port - fully interactively.  No USART
connection is used in the branch(es) supporting
this configuration.

Initial target for USB was SAMD21; current efforts
are directed at SAMD51 (Metro M4 Express).  The
SAMD21 USB version hasn't been properly introduced
to the public (look in sandboxx repo here for a
preview).


The remainder of this document (see below) has not
been updated recently, except the last few lines
(date/time stamp and such).  Information therein
may not be as reliable (applies elsewhere in another
branch or repository; there are several).

# OLD NEWS

CamelForth is now running on ATSAMD21G18A SAMD21

Adafruit Feather M0 Express.

CamelForth is running well on ATSAMD51J19A SAMD51

Adafruit Metro M4 Express.

This repository is a rebuild of all sources, such that as
few changes as practical were made to CamelForth source
code files.

# Build Environment

This is an Atmel Start based project for Atmel ATSAMD51J19A,
and now, also for ATSAMD21G18A, and runs on the Adafruit
Metro M4 Express and Feather M0 Express target boards (with
plans for additional boards).

Pinmuxing is for these two specific boards.

A recent (08 September 2018) generation of source Atmel Start
project pack (*atzip) was created to ensure compatibility with
the Atmel Start online configuration tool, for SAMD51.

SAMD21 .atzip is a bit older, and has similar scope (see 'saw-saw'
here, for example, and ainsuMtxd21-exp repositories).

The program leverages the USART on the SAMD51 (and now, SAMD21;
will refrain from tandem-mentioning of both, in what follows;
the port to SAMD21 took an afternoon and required almost no
changes -- see the edit history in git or on github for
details).

The reference environment is a host PC, running Debian
GNU/Linux 9.5, which talks to the Adafruit SAMD51 target via
Silabs CP2104.  The CP2104 is an USB to UART gateway chip.

The Adafruit PiUART is the reference implementation for CP2104.

It takes three wires to interconnect to CP2104 (TX, RX and ground).

Host system may be any host that can talk to the PiUART on an USB
port.  This requires a driver from Silicon Laboratories (Silabs)
and is already included in Linux (it's an older chip, so support
should be available on many platforms).

Firmware upload is accomplished leveraging the Arduino IDE's
implementation of BOSSAC.  There is a recent BOSSAC in the
Arduino IDE that will upload to the SAMD51 target.  The included
project's Makefile (which begins as an Atmel Start Makefile)
has direct support for an 'install' target.

Firmware is uploaded on the usual target USB port - CP2104 is
only for the project itself (during runtime).  During development,
it is usual to run two USB cables; one for CP2104 and the other
directly to the target (to accomplish firmware upload using the
bossac tool).

Building and installing consists of:

   make clean; make; make install

at the command line.  There is also a 'make checkout' target
in the makefile, to assist git users who need that function
(to clean up residual files built during 'make').

There are color escape sequences included in the Makefile.  At
the time this writing, no mechanism is offered, to suppress them.
An xterm supports them fully; any shell environment that already
shows texts in different colors (gcc arm uses them, also) will
likely be compatible with their use, here.

It should be no problem to connect the target board to any serial
terminal that uses 3.3v logic levels, directly to the Metro M4
Express TX and RX pins, and talk that way.  The PiUART is a
convenience, only (it allows the host PC to leverage its USB port
to talk to the Metro M4's USART at 3.3v logic levels).

This firmware is built on Debian Linux 9.5 (Linux kernel 4.9.0-7-amd64).
Many other environments should also function correctly; the build
environment centers on Atmel Start generated projects and their
requirements (visit http://start.atmel.com/ for more information).

Toolchain is the usual ARM gcc - same exact build environment as
Adafruit's CircuitPython.

For CircuitPython's build environment (and instructions):

    SEE: https://learn.adafruit.com/building-circuitpython/manual-setup

For the ARM gcc toolchain (including GDB):

    SEE: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads

The Makefile in this project is a modification of Atmel Start's
version, with which it is fundamentally compatible; except for the
way the Adafruit bootloader is handled:

UNTESTED EDITS:

show where the .ld file lives and what's different about it, so that
it loads the Atmel Start code correctly in the SAMD51's memory map:

  $ cat ../this_Repository/gcc/Makefile | egrep bootl
-T"../gcc/gcc/samd51j19a_flash_with_bootloader.ld" \

 $ cat ../this_Repository/gcc/gcc/samd51j19a_flash_with_bootloader.ld | sed 46q | tail -12

/* Memory Spaces Definitions */
MEMORY
{
  rom      (rx)  : ORIGIN = 0x00004000, LENGTH = 0x00080000-0x4000
  ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00030000
  bkupram  (rwx) : ORIGIN = 0x47000000, LENGTH = 0x00002000
  qspi     (rwx) : ORIGIN = 0x04000000, LENGTH = 0x01000000
}

/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : DEFINED(__stack_size__) ? __stack_size__ : 0xC000;

# Flashing the Firmware

This is done using bossac, from the command line.

A Makefile target called 'install' runs a shell script on 
the host Linux PC that launches bossac (reuses the existing
Arduino IDE bossac, which already works fine with SAMD51).

 $ ./scripts/_bossac_local.sh ./AtmelStart.bin (is what's in the Makefile)

 $ cat ../this_Repository/gcc/scripts/_bossac_local.sh  (excerpt):

Call with one argument - the path/file.bin (not .uf2) to upload using bossac

if ! [ $1 ]; then
   echo no args.  Exiting; fi
   ~/.arduino15/packages/arduino/tools/bossac/1.8.0-48-gb176eee/bossac \
    -i -d --port=/dev/ttyACM0 -U -i --offset=0x4000 -e -w -v ${1} -R  # .bin not .elf

The  --offset is specific to Adafruit SAMD51 boards (to skip
over the bootloader).

Bossac may be in more than one version in the Arduino IDE
sub-tree; 1.8.0-48 was present and was used, here.

Fri Sep 21 13:25:34 UTC 2018

On branch camelforth_tada_test_b

 $ cat ./README.md | sed 186q | md5sum

684bf648442fd2bba3c872f23d4c815d
