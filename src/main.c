#include "game.h"
#include "map.h"
#include "linkedList.h"
#include <stdio.h> /*TEMP*/
#include <string.h>

int main(int argc, const char* argv[]) {
    FILE* map_file;
    Map* map;
    int player_move;
    LinkedList* game_ll = create_linked_list();
    int running = 1;
    
    /* Argument Check */
    if(argc != 2) {
        printf("Usage: ./treasure <map_file.txt>\n");
        return 1;
    }
    /* Ensure supplied file is a .txt file.*/
    if(!strstr(argv[1], ".txt")) {
        printf("Usage: ./treasure <map_file.txt>\n");
        return 1;
    }
    printf("Opening file: %s\n", argv[1]);

    map_file = fopen(argv[1], "r");
    if(map_file == NULL) {
        perror("fopen");
    }

    map = create_map(map_file);
    if(read_map(map_file, map) != 0) {
        printf("Error reading map.\n");
        fclose(map_file);
        free_map(map);
        return 1;
    }

    /* Insert initial state of the game*/
    insert_start(game_ll, copy_map(map));

    while(running == 1) {
        #ifdef DARK_MODE
            print_dark_map(map);
        #else
            print_map(map);
        #endif

        player_move = move_player(game_ll, &map);
        if(player_move == 1) {
            move_snake(map);
            map->turn_counter++;
        }
        running = game_over_check(map);
    }

    free_linked_list(game_ll, &free_map);
    fclose(map_file);
    free_map(map);
    return 0;
}