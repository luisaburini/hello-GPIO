#define PATH_LED_VALUE        "/sys/class/gpio/gpio53/value"
#define PATH_LED_DIRECTION    "/sys/class/gpio/gpio53/direction"
#include <fcntl.h>                   // for open(), close(), lseek()
#include <sys/stat.h>                // for open()
#include <stdio.h>                   // standard I/O header file
#include <sys/types.h>               // for open()
#include <unistd.h>                  // for write(), open(), read(), usleep()
#include <termios.h>                        // terminal interface
#include <string.h>
#include <stdio.h>                  // standard I/O header file
int GetKey(void);

int main(int argc, char **argv)
{
	char key = -1;					// no keys pressed
    unsigned char led = '0';     // low(0) for Output, ASCII(48d), DEC(0d), HEX(0x30)
    int retVal;                  // for debugging purpose
    int fdLedValue;              // holds file descriptor for the value file
    int fdLedDirection;          // holds file descriptor for direction file
    char outputString[] = "out"; // string which sets GPIO direction to OUTPUT

    //  Configure GPIO direction as Output
    fdLedDirection = open(PATH_LED_DIRECTION, O_RDWR);     // open file PATH_LED_DIRECTION in read/write mode
    														// parameter: open(filepath, read-write permissions),
                                                                   // returns: file descriptor or -1 if an error occurred.


    retVal = write(fdLedDirection, &outputString[0], sizeof(outputString));   // write into file to configure GPIO as output
                                                                   // parameter: write(file_Descriptor, data_buffer, no_of_bytes),
                                                                   // returns: No. of bytes written or -1 if an error occurred.

    retVal = close(fdLedDirection);                        // close file with file descriptor
                                                                   // parameter: open(filepath, read-write permissions),
                                                                   // returns: 0 on success or -1 if an error occurred.

    fdLedValue = open(PATH_LED_VALUE, O_RDWR);             // Open file PATH_LED_VALUE in read/write mode
                                                                   // parameter: open(filepath, read-write permissions),
                                                                   // returns: file descriptor or -1 if an error occurred.
    do {
        led = (led == '1') ? '0' : '1' ;                   // Toggle led value, ASCII: '1' <----> '0'

        retVal = write(fdLedValue, &led, 1);               // write into file to update LED value - Low('0') or High ('1')
        usleep(500000);                                    // create a delay of 500 milliseconds

        key = GetKey();                                    // get user input from keyboard
    } while(key != 'q');

    retVal = close(fdLedValue);                            // close file with file descriptor
    printf("\nExiting.... \n");
    return(0);
}

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


