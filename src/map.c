#include "map.h"

Map* create_map(FILE* map_file) {
    int rows, cols;
    int i, j;
    Map* map;

    map = (Map *)malloc(sizeof(Map));
    if(map == NULL) {
        printf("Error allocating memory for map\n");
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

        }
    }
    return 0;
}


void print_map(Map* map) {
    int i, j;

    /* Clear screen */
    system("cls");

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