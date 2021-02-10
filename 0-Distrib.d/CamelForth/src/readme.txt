CAMELFORTH IN C - VERSION 0.1 - 12 DECEMBER 2017
================================================

This is an ALPHA TEST version of CamelForth/C, an ANSI Standard
Forth written in C.  This means that this code has had basic 
functional testing, but is still being tested and is subject to
change.  Report issues to bj@camelforth.com.

SYSTEM REQUIREMENTS
-------------------
The code has been successfully compiled for 32-bit Linux (x86 
processor), and a Texas Instruments Tiva-C TM4C1294XL 32-bit 
Launchpad board (ARM Cortex-M4F CPU).  The Hayes validation 
suite has been successfully run on the Linux build.

The code has NOT yet been tried on 16-bit or 64-bit processors.
Though I have tried to make the code portable to different cell
sizes, you can expect surprises.

FILES INCLUDED
--------------
ansitest.txt - Hayes test suite, configured for Linux use
forth.c -    source code for CamelForth/C
forth.h -    headers and configuration for CamelForth/C
linuxio.c -  I/O functions and main() for Linux build
tivaio.inc - I/O functions and main() for Tiva-C build


BUILD INSTRUCTIONS - LINUX
--------------------------
CamelForth is compiled with gcc.
You much have the files forth.c, forth.h, and linuxio.c in your
project directory.

You must edit forth.h to select a LINUX build, thus:

  /* define only one of the following */
  #define LINUX               /* for development under Linux */
  // #define TIVA_C              /* for use with TI TM4C12x */

You can then build CamelForth/C with the Linux command

  gcc forth.c

which will produce an executable a.out file.  To run CamelForth,
type

  ./a.out

and to run the Hayes validation suite, redirect standard input
to come from the ansitest.txt file:

  ./a.out <ansitest.txt >ansitest.log


BUILD INSTRUCTIONS - TIVA-C
---------------------------
The "Tiva-C" option is configured for the TM4C1294XL Launchpad
development board.  CamelForth is compiled with TI's Code
Composer Studio IDE, which is included with the Launchpad kit.

Create a new project by copying the Launchpad "hello" example
to a new directory in your workspace.  This will ensure that all
the required library files for terminal I/O are linked in.
(If you've just acquired the Launchpad, it's a good idea to build
and run the "hello" demo, just to make sure that your hardware is
working and the software is correctly set up.)

Copy the new files forth.c, forth.h, and tivaio.inc to that new
project directory.

Note that tivaio.inc is a C language source file, but it is
#included from forth.c rather than compiled separately.  The .inc
extension prevents Code Composer Studio from compiling it
automatically.

You must edit forth.h to select a TIVA_C build, thus:

  /* define only one of the following */
  // #define LINUX              /* for development under Linux */
  #define TIVA_C             /* for use with TI TM4C12x */

You can then use the Build function in Code Composer Studio to
compile CamelForth/C, and the Debug function to download it to 
your Launchpad board and start it.  

In the compiler output you will see several warning messages of 
the form "arithmetic on pointer to void or function type".
Ignore these for now; they will be fixed in a subsequent release.
(The TI compiler is stricter than GCC.)

The Launchpad will appear as a USB serial device to your desktop 
computer (e.g. /dev/ttyACM0 on Linux).


FORTH MODEL
-----------
CamelForth/C is an indirect-threaded Forth, with separated
headers.  This is because of the limitations of the C compiler.

There are three basic structures in the C language source code: 
C functions, threads, and headers.  By convention, these are 
named Fxxx, Txxx, and Hxxx respectively in the source code.

1.  C language functions are the "machine code" of the Forth 
kernel.  The Code Field of a Forth word always contains a 
pointer to a C function of the form

  void Fxxxx (void * pfa)
  {
    ...
  }
  
where "xxxx" is the name of the function.  pfa, a pointer to 
a parameter field, is passed in as an argument.  Note that 
most Forth primitives (e.g., DUP) do not use the pfa.

2.  Forth threads always begin with a one- or two-cell 
Code Field, followed by data.  The first (or only) cell of
the Code Field points to a C language function.  In the case of 
a high-level Forth definition, that function will be Fenter, 
and the data will be a series of execution tokens (pointers to 
other Forth threads).  

The thread is defined as a "const" array of void pointers,
initialized with the Code Field and subsequent data.  
For example:

  const void * Ttwodup[] = { Fenter, Tover, Tover, Texit };

For words built with CREATE, the Code Field is two cells. 
See the discussion below of CREATE ... DOES>.

Note that even primitive functions have a thread.  For 
primitives, the thread is a Code Field (pointer to C function)
followed by no data.  For example,

  const void * Tdup[] = { Fdup }

3.  Forth headers are defined separately from the threads.
Each header is defined as a "const struct Header", initialized
with the desired data.  The Header struct is defined in forth.h:

  struct Header {
    void * link;            /* pointer to previous header */
    void * cfa;             /* pointer to high level def'n */
    unsigned char flags;    /* immed flag and others */
    char nfa[];             /* inline name string */
  };

Unfortunately the "link" fields must be specified manually. 
"link" is a pointer to the "nfa" field of the previous header
(creating a linked list of headers).  The "cfa" field points to 
the corresponding thread.  The "flags" are either 0 for most 
words, or IMMEDIATE for immediate words.  Finally, "nfa" is
a counted string -- one char of count, followed by n chars.
In this example, the previous header is "lit".    

  const struct Header Hdup =\
    { (char *)Hlit.nfa, Tdup, 0, "\003DUP" }

NOTE: gcc allows a variable-length string, with an initializer,
as the last element in a struct.  The Texas Instruments compiler
does NOT allow this.  So, if TIVA_C is selected, the "nfa" 
field will be allocated a fixed size of 13 chars in every header.
This is sufficient for the longest kernel name.  Words that are
added later with the Forth compiler are not subject to this 
limitation.

FORTH MODEL MACROS
------------------
To simplify writing the C code, and make the kernel more 
readable, several macros are #defined in forth.h.

To build a primitive C function:

  CODE(name) {
    ...
  }
  
To build the thread for a primitive C function:

  PRIMITIVE(name);
  
To build any other kind of thread:

  THREAD(name) = { Fxxx, data, data, data ... };
  
where the first initializer is the pointer to a C function.
The subsequent data might be pointers to Forth threads.
  
To build a header:

  HEADER(name, previousname, flags, namestring);


CREATE ... DOES>
----------------
Because the CamelForth/C kernel cannot build C language (or 
machine-language) functions, it uses a FIG-Forth style 
implementation of CREATE...DOES>.  This requires a two-cell
Code Field in each defined word.  The first cell is the code
pointer, to the function Fdobuilds.  The second cell is the
address of a headless thread that implements the DOES> action.

Here is an example:
  : KONSTANT CREATE , DOES> @ ;
  2 KONSTANT TWO
  
The defined word TWO is compiled as three cells (two-cell
code field and one cell of data):
  Ttwo: [Fdobuilds]  [Tkonstantdoes]  [ 2 ]

The word KONSTANT is a conventional Forth word which contains
a headerless Forth thread:
  Tkonstant:  [Fenter]  [Tcreate]  [Tcomma]  [Txdoes]
  Tkonstantdoes:  [Fenter]  [Tfetch]  [Texit]
      
(In this example, read Ttwo, Tkonstant, and Tkonstantdoes as 
labels, and [xxx] as cells compiled in memory.)

When TWO is executed, the function Fdobuilds puts the address
of pfa+CELL (the address of the value 2) on the parameter stack,
then executes the Forth word whose xt is stored at pfa (the 
thread Tkonstantdoes).  

In order to leave room for DOES> to install this, CREATE
always reserves a two-cell code field.  If CREATE is used
without DOES>, the second cell remains unused.  The phrase
   CREATE FOUR  4 ,
will compile
   Tfour: [Fdocreate]  [xxx]  [ 4 ]

When FOUR is executed, the function Fdocreate puts the address 
of pfa+CELL (the address of the value 4) on the parameter stack.
The cell [xxx] is not used.

The word >BODY is "smart."  If it sees a word whose Code Field
contains Fdocreate or Fdobuilds, it will return cfa+(2 cells) 
as the pfa of the word.  Otherwise, it will return cfa+CELL as
the pfa of the word.

--------------------------- LICENSE TERMS ------------------------------
CamelForth in C
(c) 2016,2017 Bradford J. Rodriguez.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Commercial inquiries should be directed to the author at 
115 First St., #105, Collingwood, Ontario L9Y 4W3 Canada
or via email to bj@camelforth.com
------------------------------------------------------------------------