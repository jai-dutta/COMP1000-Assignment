#include "game.h"
#include "input.h"
#include "map.h"
#include "linkedList.h"
#include "random.h"

Controls process_input() {
    Controls control;
    disableBuffer();
    control = get_input();
    enableBuffer();
    return control;
}

void game_over() {
    exit(1);
}

void move_player(Map* map) {
    printf("x: %d y: %d\n", map->player_cell[0], map->player_cell[1]);
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
    }
    /* Movement checks */
    if(0 <= player_x && player_x < map->rows && 0 <= player_y && player_y < map->cols) {
        if(map->data[player_x][player_y] == EMPTY) {
            map->data[player_x][player_y] = map->data[map->player_cell[0]][map->player_cell[1]];
            map->data[map->player_cell[0]][map->player_cell[1]] = EMPTY;
            map->player_cell[0] = player_x;
            map->player_cell[1] = player_y;
        }
        else if (map->data[player_x][player_y] == SNAKE) {
            game_over();
        }
    
    }
}