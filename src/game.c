#include "game.h"
#include "input.h"
#include "map.h"
#include "linkedList.h"
#include "random.h"

Controls process_input(void) {
    Controls control;
    disableBuffer();
    control = get_input();
    enableBuffer();
    return control;
}

void undo_turn(LinkedList* ll, Map** map) {
    Map* prevMap = (Map*) remove_start(ll);
    if(prevMap != NULL) {
        free_map(*map);
        *map = prevMap;
    }
}
int game_over_check(Map* map) {
    if(map->player_cell[0] == map->snake_cell[0] && map->player_cell[1] == map->snake_cell[1]) {
        /* Print final map state */
        #ifdef DARK_MODE
                print_dark_map(map);
        #else
                print_map(map);
        #endif
        printf("Game Over! The snake ate you!\n");
        return 0;
    }
    if(map->treasure_found == 1) {
        #ifdef DARK_MODE
                print_dark_map(map);
        #else
                print_map(map);
        #endif
        printf("You win! Treasure has been found!\n");
        return 0;
    }

    /* returns 1 for non game over condition */
    return 1;
}

void find_treasure(Map* map) {
    map->treasure_found = 1;
}


void pickup_lantern(Map* map) {
    map->lantern_found = 1;
}

void carrying_lantern(Map* map) {
        map->lantern_cell[0] = map->player_cell[0];
        map->lantern_cell[1] = map->player_cell[1];
        map->data[map->lantern_cell[0]][map->lantern_cell[1]] = map->data[map->player_cell[0]][map->player_cell[1]];
}
/* Returns 1 if player moved */
int move_player(LinkedList* ll, Map** map) {
    Controls direction = process_input();

    /* This represents the possible NEW location of the player*/
    int player_x = (*map)->player_cell[0];
    int player_y = (*map)->player_cell[1];

    switch(direction) {
        case UP:
            player_x--;
            break;
        case DOWN:
            player_x++;
            break;
        case LEFT:
            player_y--;
            break;
        case RIGHT:
            player_y++;
            break;
        case UNDO:
            undo_turn(ll, map);
            return -1;
        default: return 0;
    }

    insert_start(ll, copy_map(*map));
    
    /* Movement checks */
    if (0 <= player_x && player_x < (*map)->rows && 0 <= player_y && player_y < (*map)->cols) {
        if ((*map)->data[player_x][player_y] == EMPTY) {
            (*map)->data[player_x][player_y] = (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]];
            (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]] = EMPTY;
            (*map)->player_cell[0] = player_x;
            (*map)->player_cell[1] = player_y;
            if ((*map)->lantern_found) {
                carrying_lantern(*map);
            }
            return 1;
        }
        if ((*map)->data[player_x][player_y] == TREASURE) {
            (*map)->data[player_x][player_y] = (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]];
            (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]] = EMPTY;
            (*map)->player_cell[0] = player_x;
            (*map)->player_cell[1] = player_y;
            find_treasure(*map);
            return 1;
        }
        if ((*map)->data[player_x][player_y] == LANTERN) {
            (*map)->data[player_x][player_y] = (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]];
            (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]] = EMPTY;
            (*map)->player_cell[0] = player_x;
            (*map)->player_cell[1] = player_y;
            pickup_lantern(*map);
            return 1;
        }
    }
    return 0;
}


void move_snake(Map* map) {
    int has_moved = 0;
    int* direction;
    int snake_x, snake_y, i, j;

    /* Check if player within a tile */
    snake_x = map->snake_cell[0];
    snake_y = map->snake_cell[1];
    for(i = snake_x - 1; i <= snake_x + 1; i++) {
        for(j = snake_y - 1; j <= snake_y + 1; j++) {
            if(i >= 0 && i < map->rows && j >= 0 && j < map->cols) {
                if(map->data[i][j] == PLAYER) {
                    map->data[i][j] = map->data[map->snake_cell[0]][map->snake_cell[1]];
                    map->data[map->snake_cell[0]][map->snake_cell[1]] = EMPTY;
                    map->snake_cell[0] = i;
                    map->snake_cell[1] = j;
                    has_moved = 1;
                }
            }
        }
    }

    /* Random Movement checks */
    while(has_moved == 0) {
        snake_x = map->snake_cell[0];
        snake_y = map->snake_cell[1];
        direction = gen_direction();
        snake_x += direction[0];
        snake_y += direction[1];
        free(direction);
        if(0 <= snake_x && snake_x < map->rows && 0 <= snake_y && snake_y < map->cols) {
            if(map->data[snake_x][snake_y] == EMPTY) {
                map->data[snake_x][snake_y] = map->data[map->snake_cell[0]][map->snake_cell[1]];
                map->data[map->snake_cell[0]][map->snake_cell[1]] = EMPTY;
                map->snake_cell[0] = snake_x;
                map->snake_cell[1] = snake_y;
                has_moved = 1;
            }
        }
    }
}

