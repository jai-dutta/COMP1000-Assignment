#include "random.h"
#include <stdlib.h>

int* gen_direction(void) {
    int* direction = (int *)malloc(sizeof(int) * 2);
    int random = rand() % 8;
    switch(random) {
        case 1:
            direction[0] = -1;
            direction[1] = 0;
            break;
        case 2:
            direction[0] = 1;
            direction[1] = 0;
            break;
        case 3:
            direction[0] = 0;
            direction[1] = -1;
            break;
        case 4:
            direction[0] = 0;
            direction[1] = 1;
            break;
        case 5:
            direction[0] = -1;
            direction[1] = -1;
            break;
        case 6:
            direction[0] = -1;
            direction[1] = 1;
            break;
        case 7:
            direction[0] = 1;
            direction[1] = -1;
            break;
        case 8:
            direction[0] = 1;
            direction[1] = 1;
            break;
    }
    return direction;
}
