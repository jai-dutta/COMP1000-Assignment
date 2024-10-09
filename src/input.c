#include<stdio.h>
#include<termios.h>
#include "input.h"

/*
 * Input
 * This file handles terminal buffering and scanning user input for movement.
 *      Author: Jai Dutta
 *      Student ID: 22073372
 *      Unit: COMP1000 - Unix and C Programming
 */

/* Provided code */
void disableBuffer(void) {
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}
/* Provided code */
void enableBuffer(void) {
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

/* Get user input as a char and return it */
char get_input(void) {
    char button;
    
    scanf(" %c", &button);
    
    return button;
}
