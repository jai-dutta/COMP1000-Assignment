#include "game.h"
#include "input.h"
#include "map.h"
#include "linkedList.h"
#include "random.h"
#include <stdbool.h>

Controls process_input() {
    Controls control;
    disableBuffer();
    control = get_input();
    enableBuffer();
    return control;
}

void undo_turn(LinkedList* ll, Map* map) {
    Map* prevMap = (Map*) remove_start(ll);
    printf("%d ", prevMap->player_cell[0]);
    *map = prevMap;
}
void game_over() {
    exit(1);
    /* TO DO*/
}

void pickup_lantern(Map* map) {
    map->lantern_move_counter = 6;
}

bool carrying_lantern(Map* map) {
    if(0 < map->lantern_move_counter) {
        map->lantern_move_counter = map->lantern_move_counter - 1;
        map->lantern_cell[0] = map->player_cell[0];
        map->lantern_cell[1] = map->player_cell[1];
        map->data[map->lantern_cell[0]][map->lantern_cell[1]] = map->data[map->player_cell[0]][map->player_cell[1]];
        return true;
    } else {
        return false;
    }
}
/* Returns 1 if player moved */
bool move_player(LinkedList* ll, Map* map) {
    Controls direction = process_input();
    int player_x = map->player_cell[0];
    int player_y = map->player_cell[1];

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
                break;
    }
    /* Movement checks */
    if(0 <= player_x && player_x < map->rows && 0 <= player_y && player_y < map->cols) {
        if(map->data[player_x][player_y] == EMPTY) {
            carrying_lantern(map);
            map->data[player_x][player_y] = map->data[map->player_cell[0]][map->player_cell[1]];
            map->data[map->player_cell[0]][map->player_cell[1]] = EMPTY;
            map->player_cell[0] = player_x;
            map->player_cell[1] = player_y;
            return true;
        }
        else if (map->data[player_x][player_y] == SNAKE) {
            game_over();
        }
        else if(map->data[player_x][player_y] == LANTERN) {
            map->data[player_x][player_y] = map->data[map->player_cell[0]][map->player_cell[1]];
            map->data[map->player_cell[0]][map->player_cell[1]] = EMPTY;
            map->player_cell[0] = player_x;
            map->player_cell[1] = player_y;
            return true;
        }
        else {
            return false;
        }
    }
    return false;
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