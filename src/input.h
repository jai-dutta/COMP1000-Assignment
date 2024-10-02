#ifndef INPUT_H
#define INPUT_H

typedef enum {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd',
    UNDO = 'u'
} Controls;

// forward declarations
void disableBuffer();
void enableBuffer();
char get_input();

#endif