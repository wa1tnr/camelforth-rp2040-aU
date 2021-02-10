/****h* camelforth/linuxio.c
 * NAME
 *  linuxio.c
 * DESCRIPTION
 *  Linux terminal I/O for testing
 * SYNOPSIS
 *  Provides the functions
 *      void putch(char c)      write one character to terminal
 *      char getch(void)        await/read one character from keyboard
 *      int getquery(void)      return true if keyboard char available
 *      void initTermios(void)  configure terminal for Forth
 *      void resetTermios(void) reset terminal configuration, if req'd
 *      int main(int argc, char *argv[])   main entry point
 * USES
 *  Functions provided by stdio:
 *      void putchar(char c)    emit one character to display
 * NOTES
 *  Adapted from
 *  http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
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

#include <termios.h>
#include <poll.h>
#include <unistd.h>     /* for STDIN_FILENO */
#include <stdlib.h>     /* for exit() */
#include <stdio.h>

#define putch putchar   /* provided by stdio */

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(void) 
{
    tcgetattr(STDIN_FILENO, &old);  /* grab old terminal i/o settings */
    new = old;              /* make new settings same as old settings */
    new.c_lflag &= ~ICANON;         /* disable buffered i/o */
    new.c_lflag &= ~ECHO;           /* disable echo mode */
    tcsetattr(STDIN_FILENO, TCSANOW, &new); /* use new settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

/* Read 1 character without echo */
/* 
 * NOTES
 *  stdin must be set to raw (unbuffered) mode; see initTermios above.
 */

char getch(void) 
{
    int r;
    r = getchar();
    if (r == EOF) exit(1);  /* needed when redirecting stdin */
    else return r;
}


/* Check if char available on standard input */
/* 
 * NOTES
 *  stdin must be set to raw (unbuffered) mode; see initTermios above.
 */

int getquery(void) 
{
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    
    // poll with timeout = 0 will return event if pending;
    // poll returns 0 if no event, 1 if 1 event.
    return poll(fds, 1, 0);
}

/*
 * Main entry point for Linux
 */

void interpreter(void);     /* forward reference */

int main ( int argc, char *argv[] )
{
    initTermios();
    printf("\nCamelForth in C - Linux testing\n");
    interpreter();
    resetTermios();
}


