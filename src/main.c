#include "game.h"
#include "map.h"
#include "linkedList.h"
#include <stdio.h>
#include <string.h>

/*
 * Main Function
 *      Author: Jai Dutta
 *      Student ID: 22073372
 *      Unit: COMP1000 - Unix and C Programming
 */



int main(int argc, const char* argv[]) {
    /* Declare variables */
    FILE* map_file;
    Map* map;
    int player_move;
    /* Declare and initialise linked list */
    LinkedList* game_ll = create_linked_list();
    /* Declare running variable - while 1, the game loop executes. Changes to 0 on a game over condition */
    int running = 1;
    
    /* Check argument count. */
    if(argc != 2) {
        printf("Usage: ./treasure <map_file.txt>\n");
        return 1;
    }
    /* Ensure supplied file is a .txt file.*/
    if(!strstr(argv[1], ".txt")) {
        printf("Usage: ./treasure <map_file.txt>\n");
        return 1;
    }
    /* Print a message letting the user know which file is being opened as the map file. */
    printf("Opening file: %s\n", argv[1]);

    /* Initialise map_file as a FILE* pointer to the supplied map txt file */
    map_file = fopen(argv[1], "r");
    if(map_file == NULL) {
        perror("fopen");
    }
    /* Call the create_map function to read in file contents and initialise the map struct and 2D array of map data
     * This function returns 0 if the map was created successfully, and non-zero for failure.
     */
    map = create_map(map_file);
    if(read_map(map_file, map) != 0) {
        printf("Error reading map.\n");
        fclose(map_file);
        free_map(map);
        return 1;
    }

    /* Insert initial state of the game into the linked list for undo functionality
     * The following inserts happen in game.c
     */
    insert_start(game_ll, copy_map(map));

    /* MAIN GAME LOOP */
    while(running == 1) {
        /* Print either the dark mode map or the normal map based on the compile conditions (-d DARK_MODE). To use dark mode, run "make dark" */
        #ifdef DARK_MODE
            print_dark_map(map);
        #else
            print_map(map);
        #endif
        /* Call function to process input and move player within the map */
        player_move = move_player(game_ll, &map);
        /* If the player moved successfully, call the snake movement function and increment the turn counter.
         * An unsuccessful move would be attempting to move into a wall, etc.
         */
        if(player_move == 1) {
            move_snake(map);
            map->turn_counter++;
        }
        /* Run the game over checks at the end of each iteration.
         * Checks if the snake has eaten the player, or the player has reached the treasure.
         * This function will return 0 for non-game-over condition, or 1 for game-over condition.
         */
        running = game_over_check(map);
    }

    /* End of program housekeeping */
    free_linked_list(game_ll, &free_map);
    fclose(map_file);
    free_map(map);
    return 0;
}