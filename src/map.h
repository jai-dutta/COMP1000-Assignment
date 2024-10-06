#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int* player_cell;
    int* snake_cell;
    int* lantern_cell;
    int lantern_found;
    int turn_counter;
} Map;

/* Forward Declarations */
Map* create_map(FILE* map_file);
int read_map(FILE* map_file, Map* map);
void print_map(Map* map);
Map* copy_map(Map* original);
void free_map(void* map_ptr);
void print_dark_map(Map* map);
#endif
