#include <stdio.h>
#include <string.h>
#include <termios.h>                        // terminal interface
#include "getkey.h"
 
int GetKey(void)
{
        struct termios orig_term_attr;      // holds original state of terminal
        struct termios new_term_attr;       // holds new state of terminal
        int character;
 
        // Set terminal to raw mode, to access keyboard input
        tcgetattr(fileno(stdin), &orig_term_attr);         // fileno returns the file descriptor number of stdin
 
        memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));  // copy data from orig_term_attr to new_term_attr
        new_term_attr.c_lflag &= ~ICANON;                  // non-canonical input processing --> no new line required
        new_term_attr.c_cc[VTIME] = 0;                     // wait for 0*0.01 sec input, in non-canonical state
        new_term_attr.c_cc[VMIN] = 0;                      // VMIN is min number of bytes that must be available in input queue, in Non-Canonical state
 
        tcsetattr(fileno(stdin), TCSANOW, &new_term_attr); // set new attributes to stdin
 
        character=fgetc(stdin);                            // read from stdin and return EOF(-1), if no character is available
 
        // restore terminal to its original state
        tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);// restore original terminal attributes, TCSANOW: apply changes now
 
    return(character);
}

