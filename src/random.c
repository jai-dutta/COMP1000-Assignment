#include "random.h"
#include <stdlib.h>

/*
 * Random
 * This file handles providing random directions for movement of NPCS in the game.
 *      Author: Jai Dutta
 *      Student ID: 22073372
 *      Unit: COMP1000 - Unix and C Programming
 */

/* Generates a random direction from 8 choices and returns a two element array representing it. */
int* gen_direction(void) {
    int* direction = (int *)malloc(sizeof(int) * 2);
    int random = rand() % 8;
    switch(random) {
        case 0:
            direction[0] = -1;
            direction[1] = 0;
            break;
        case 1:
            direction[0] = 1;
            direction[1] = 0;
            break;
        case 2:
            direction[0] = 0;
            direction[1] = -1;
            break;
        case 3:
            direction[0] = 0;
            direction[1] = 1;
            break;
        case 4:
            direction[0] = -1;
            direction[1] = -1;
            break;
        case 5:
            direction[0] = -1;
            direction[1] = 1;
            break;
        case 6:
            direction[0] = 1;
            direction[1] = -1;
            break;
        case 7:
            direction[0] = 1;
            direction[1] = 1;
            break;
    }
    return direction;
}
