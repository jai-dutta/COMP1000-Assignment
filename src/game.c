#include "game.h"
#include "input.h"
#include "map.h"
#include "linkedList.h"
#include "random.h"

/*
 * Game
 * This file handles game logic and movement.
 *      Author: Jai Dutta
 *      Student ID: 22073372
 *      Unit: COMP1000 - Unix and C Programming
 */



/* This function disables and re-enables the buffer and returns the input entered by the user as a CONTROLS enum (see input.h) */
Controls process_input(void) {
    Controls control;
    disableBuffer();
    control = get_input();
    enableBuffer();
    return control;
}

/* Function to restore the last saved Map state */
void undo_turn(LinkedList* ll, Map** map) {
    Map* prevMap = (Map*) remove_start(ll);
    if(prevMap != NULL) {
        /* Free current map */
        free_map(*map);
        /* Map point to prevMap */
        *map = prevMap;
    }
}
/* Checks if the player has collided with the snake, or if the treasure_found integer stored in Map struct is 1 (indicating treasure found) */
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

/* Gets called when user collides with treasure */
void find_treasure(Map* map) {
    map->treasure_found = 1;
}

/* Gets called when user collides with lantern */
void pickup_lantern(Map* map) {
    map->lantern_found = 1;
}

/* Runs if carrying_lantern int in Map struct is 1 (indicating user has found lantern) */
void carrying_lantern(Map* map) {
        map->lantern_cell[0] = map->player_cell[0];
        map->lantern_cell[1] = map->player_cell[1];
        map->data[map->lantern_cell[0]][map->lantern_cell[1]] = map->data[map->player_cell[0]][map->player_cell[1]];
}
/* Returns 1 if player moved */
int move_player(LinkedList* ll, Map** map) {
    /* Get the user input as a Controls enum */
    Controls direction = process_input();

    /* Initialise x and y variables as the current player location.*/
    int player_x = (*map)->player_cell[0];
    int player_y = (*map)->player_cell[1];

    /* Switch on the direction (user input) and change the new player x/y. player_x and player_y now represent a possible NEW location (the player hasnt moved yet) */
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

    /* Insert the current game state (Map struct) into the LinkedList */
    insert_start(ll, copy_map(*map));
    
    /* Movement checks */
    /* Check if the new location is within map boundaries */
    if (0 <= player_x && player_x < (*map)->rows && 0 <= player_y && player_y < (*map)->cols) {
        /*Check if the new location is an EMPTY tile */
        if ((*map)->data[player_x][player_y] == EMPTY) {

            /* Change the value of the NEW location to be PLAYER in the Map array */
            (*map)->data[player_x][player_y] = PLAYER;
            /* Change the value of the OLD location to be PLAYER in the Map array */
            (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]] = EMPTY;
            /* Update the Map struct to reflect the new player position */
            (*map)->player_cell[0] = player_x;
            (*map)->player_cell[1] = player_y;
            /* Call the carrying lantern if the lantern has been picked up. */
            if ((*map)->lantern_found) {
                carrying_lantern(*map);
            }
            return 1;
        }
        if ((*map)->data[player_x][player_y] == TREASURE) {
            (*map)->data[player_x][player_y] = PLAYER;
            (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]] = EMPTY;
            (*map)->player_cell[0] = player_x;
            (*map)->player_cell[1] = player_y;
            find_treasure(*map);
            return 1;
        }
        if ((*map)->data[player_x][player_y] == LANTERN) {
            (*map)->data[player_x][player_y] = PLAYER;
            (*map)->data[(*map)->player_cell[0]][(*map)->player_cell[1]] = EMPTY;
            (*map)->player_cell[0] = player_x;
            (*map)->player_cell[1] = player_y;
            pickup_lantern(*map);
            return 1;
        }
    }
    return 0;
}

/* Function for snake movement */
void move_snake(Map* map) {
    /*Initialise variables*/
    int has_moved = 0; /* has_moved is used to determine two things (1) If the snake moves toward the player, dont do a random move.
                                                                    (2) For the while loop end condition when attempting to find a possible random move. */
    int* direction;
    int snake_x, snake_y, i, j;

    /* Checks if a player is within 1 tile radius of the snake, if so, move toward them. */
    snake_x = map->snake_cell[0];
    snake_y = map->snake_cell[1];
    /* Perform a loop to check adjacent tiles to the snake position */
    for(i = snake_x - 1; i <= snake_x + 1; i++) {
        for(j = snake_y - 1; j <= snake_y + 1; j++) {
            /* Ensure the tiles checked are within Map boundaries */
            if(i >= 0 && i < map->rows && j >= 0 && j < map->cols) {
                /* If the player occupies one of these tiles, move to player.*/
                if(map->data[i][j] == PLAYER) {
                    map->data[i][j] = SNAKE;
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
        /* Reset snake_x and snake_y each iteration, or it will continually increase due to the += code block below. */
        snake_x = map->snake_cell[0];
        snake_y = map->snake_cell[1];
        /* Initialise direction as a random direction provided by gen_direction. (8 possible directions) */
        direction = gen_direction();
        snake_x += direction[0];
        snake_y += direction[1];
        free(direction);
        /*Check that snake movement is within map borders.*/
        if(0 <= snake_x && snake_x < map->rows && 0 <= snake_y && snake_y < map->cols) {
            /* This is the same movement logic as above. */
            if(map->data[snake_x][snake_y] == EMPTY) {
                map->data[snake_x][snake_y] = SNAKE;
                map->data[map->snake_cell[0]][map->snake_cell[1]] = EMPTY;
                map->snake_cell[0] = snake_x;
                map->snake_cell[1] = snake_y;
                has_moved = 1;
            }
        }
    }
}

