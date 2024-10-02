#include<stdio.h>
#include<termios.h>
#include "input.h"

void disableBuffer(void) {
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void enableBuffer(void) {
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

char get_input(void) {
    char button;
    
    scanf(" %c", &button);
    
    return button;
}
