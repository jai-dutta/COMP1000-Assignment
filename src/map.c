#include "map.h"
#include <string.h>
Map* create_map(FILE* map_file) {
    int rows, cols;
    int i, j;
    Map* map;



    map = (Map *)malloc(sizeof(Map));
    if(map == NULL) {
        printf("Error allocating memory for map\n");
        return NULL;
    }
    map->player_cell = (int *)malloc(sizeof(int) * 2);
    if(map->player_cell == NULL) {
        printf("Error allocating memory for player position!");
        return NULL;
    }
    map->snake_cell = (int *)malloc(sizeof(int) * 2);
    if(map->snake_cell == NULL) {
        printf("Error allocating memory for snake position!");
        return NULL;
    }
    map->lantern_cell = (int *)malloc(sizeof(int) * 2);
    if(map->lantern_cell == NULL) {
        printf("Error allocating memory for lantern position!");
        return NULL;
    }

    /* Read rows/cols and perform a check to see if they were succesfully read. */
    if(fscanf(map_file, "%d %d", &rows, &cols) != 2) {
        printf("Error reading map file rows and columns.\n");
        free(map);
        return NULL;
    }

    map->rows = rows;
    map->cols = cols;
    map->data = (int**)malloc(rows * sizeof(int*));
    for(i = 0; i < rows; ++i) {
        map->data[i] = (int*)malloc(cols * sizeof(int));

        if(map->data[i] == NULL) {
            for (j = 0; j < i; ++j) {
                free(map->data[j]);
            }
            free(map->data);
            free(map);
            map = NULL;
            return NULL;
        }
    }
    return map;
}

/* Returns 0 for success, or non zero for failure.*/
/* NOTE TO SELF: ENSURE YOU CHECK! */
int read_map(FILE* map_file, Map* map) {
    int i, j;
    int successful_scan;

    /* Rewind FILE pointer to the start of the file */
    rewind(map_file);
    /* Skip the row, column and wall counts */
    for(i=0; i<3;i++) {
        int ignored; /* READ IN WALL COUNT HERE IF NEEDED LATER */
        fscanf(map_file, "%d", &ignored);
    }
    /* Read in the map */
    for(i=0; i<map->rows; i++) {
        for(j=0; j<map->cols; j++) {

            /* Read integer value and handle reading errors.*/
            successful_scan = fscanf(map_file, "%d", &map->data[i][j]);
            if (successful_scan != 1) {
                /* Check for errors and set errno accordingly */
                if (ferror(map_file)) {
                    perror("Error reading in map!");
                } else if (feof(map_file)) {
                    fprintf(stderr, "Unexpected end of file while reading map! Please ensure rows/column counts are correct.\n");
                } else {
                    fprintf(stderr, "Unknown error reading in map!\n");
                }
                /* Free memory and return */
                for (j = 0; j < i; ++j) {
                    free(map->data[j]);
                }
                free(map->data);
                free(map);
                return 1;
            }

            /* Find spawn locations of objects */
            if(map->data[i][j] == PLAYER) {
                map->player_cell[0] = i;
                map->player_cell[1] = j;
            }
            if(map->data[i][j] == SNAKE) {
                map->snake_cell[0] = i;
                map->snake_cell[1] = j;
            }
            if(map->data[i][j] == LANTERN) {
                map->lantern_cell[0] = i;
                map->lantern_cell[1] = j;
            }

        }

    }
    return 0;
}

void print_dark_map(Map* map) {
    int i, j;

    /* Clear screen */
    system("clear");

    /* +2 as the border goes around the edge of the playable map. */
    for(i=0; i < map->cols + 2; i++) {
        printf("*");
    }
    printf("\n");

    for(i = 0; i < map->rows; i++) {
        printf("*");
        for(j=0; j < map->cols; j++) {
            switch(map->data[i][j]) {
                case EMPTY:
                        printf(" ");
                        break;
                case WALL:
                        printf("O");
                        break;
                case LANTERN:
                        printf("@");
                        break;
                case PLAYER:
                        printf("P");
                        break;
                case SNAKE:
                        printf("~");
                        break;
                case TREASURE:
                        printf("$");
                        break;
            }
        }
        printf("*\n");
    }
    /* +2 as the border goes around the edge of the playable map. */
    for(i = 0; i < map->cols + 2; i++) {
        printf("*");
    }
    printf("\n");

    /* Print control menu */
    printf("* Press W to go up\n");
    printf("* Press S to go down\n");
    printf("* Press A to go left\n");
    printf("* Press D to go right\n");
    printf("* Press U to go back\n");

}

void print_map(Map* map) {
    int i, j;

    /* Clear screen */
    system("clear");

    /* +2 as the border goes around the edge of the playable map. */
    for(i=0; i < map->cols + 2; i++) {
        printf("*");
    }
    printf("\n");

    for(i = 0; i < map->rows; i++) {
        printf("*");
        for(j=0; j < map->cols; j++) {
            switch(map->data[i][j]) {
                case EMPTY:
                        printf(" ");
                        break;
                case WALL:
                        printf("O");
                        break;
                case LANTERN:
                        printf("@");
                        break;
                case PLAYER:
                        printf("P");
                        break;
                case SNAKE:
                        printf("~");
                        break;
                case TREASURE:
                        printf("$");
                        break;
            }
        }
        printf("*\n");
    }
    /* +2 as the border goes around the edge of the playable map. */
    for(i = 0; i < map->cols + 2; i++) {
        printf("*");
    }
    printf("\n");

    /* Print control menu */
    printf("* Press W to go up\n");
    printf("* Press S to go down\n");
    printf("* Press A to go left\n");
    printf("* Press D to go right\n");
    printf("* Press U to go back\n");

}

Map* copy_map(Map* original) {
    int i, j;
    Map* copy = (Map*)malloc(sizeof(Map));
    if(copy == NULL) {
        printf("Error allocating memory for map\n");
        return NULL;
    }
    

    copy->player_cell = (int *)malloc(sizeof(int) * 2);
    if(copy->player_cell == NULL) {
        printf("Error allocating memory for player position!");
        return NULL;
    }
    copy->snake_cell = (int *)malloc(sizeof(int) * 2);
    if(copy->snake_cell == NULL) {
        printf("Error allocating memory for snake position!");
        return NULL;
    }
    copy->lantern_cell = (int *)malloc(sizeof(int) * 2);
    if(copy->lantern_cell == NULL) {
        printf("Error allocating memory for lantern position!");
        return NULL;
    }


    copy->rows = original->rows;
    copy->cols = original->cols;
    copy->lantern_found = original->lantern_found;
    copy->player_cell[0] = original->player_cell[0];
    copy->player_cell[1] = original->player_cell[1];
    copy->snake_cell[0] = original->snake_cell[0];
    copy->snake_cell[1] = original->snake_cell[1];        
    copy->lantern_cell[0] = original->lantern_cell[0];
    copy->lantern_cell[1] = original->lantern_cell[1];

    
    copy->data = (int**)malloc(copy->rows * sizeof(int*));
    for (i = 0; i < copy->rows; i++) {
        copy->data[i] = (int*)malloc(copy->cols * sizeof(int));
        for(j = 0; j<copy->cols; j++) {
            copy->data[i][j] = original->data[i][j];
        }
    }
    return copy;
}

void free_map(Map* map) {
    int i;
    for (i = 0; i < map->rows; i++) {
        free(map->data[i]);
    }
    free(map->player_cell);
    free(map->lantern_cell);
    free(map->snake_cell);
    free(map->data);
    free(map);
}
