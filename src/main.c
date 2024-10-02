#include "game.h"
#include "map.h"
#include <stdio.h> /*TEMP*/
#include <string.h>

int main(int argc, const char* argv[]) {
    Map* map;
    FILE* map_file;
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
    printf("Trying to open file: %s\n", argv[1]);
    map_file = fopen(argv[1], "r");
    if(map_file == NULL) {
        perror("fopen");
    }

    map = create_map(map_file);
    if(read_map(map_file, map) != 0) {
        printf("Error reading map");
        return 1;
    }
    print_map(map);
    return 0;
}
