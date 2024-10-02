#include "game.h"
#include <stdio.h> /*TEMP*/
#include <string.h>

int main(int argc, const char* argv[]) {

    /* argument checks */

    /* Argument Check */
    if(argc != 2) {
        printf("Usage: ./treasure <map_file.txt>");
        return 1;
    }
    /* Ensure supplied file is a .txt file.*/
    if(!strstr(argv[1], ".txt")) {
        printf("Usage: ./treasure <map_file.txt>");
        return 1;
    }

    return 0;
}
