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
void game_over(void) {
    exit(1);
    /* TO DO*/
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
        else if ((*map)->data[player_x][player_y] == SNAKE) {
            game_over();
        }
        else if ((*map)->data[player_x][player_y] == LANTERN) {
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
    int* direction = gen_direction();
    int snake_x = map->snake_cell[0];
    int snake_y = map->snake_cell[1];
    snake_x += direction[0];
    snake_y += direction[1];


    /* Movement checks */
    /* TO DO: CHECK IF HUMAN CLOSE TO SNEK */
    if(0 <= snake_x && snake_x < map->rows && 0 <= snake_y && snake_y < map->cols) {
        if(map->data[snake_x][snake_y] == EMPTY) {
            map->data[snake_x][snake_y] = map->data[map->snake_cell[0]][map->snake_cell[1]];
            map->data[map->snake_cell[0]][map->snake_cell[1]] = EMPTY;
            map->snake_cell[0] = snake_x;
            map->snake_cell[1] = snake_y;
        }
    }
}
