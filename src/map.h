#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    EMPTY = 0,
    WALL = 1,
    LANTERN = 2,
    PLAYER = 3,
    SNAKE = 4,
    TREASURE = 5
} MapObject;

typedef struct {
    int rows, cols;
    int **data;
} Map;

/* Forward Declarations */
Map* create_map(FILE* map_file);
int read_map(FILE* map_file, Map* map);
void print_map(Map* map);

#endif