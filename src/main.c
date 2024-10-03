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
    
    
    /* Argument Check */
    if(argc != 2) {
        printf("Usage: ./treasure <map_file.txt>");
        return 1;
    }
    /* Ensure supplied file is a .txt file.*/
    if(!strstr(argv[1], ".txt")) {
        printf("Usage: ./treasure <map_file.txt>");
        return 1;
    }
    printf("Opening file: %s\n", argv[1]);

    map_file = fopen(argv[1], "r");
    if(map_file == NULL) {
        perror("fopen");
    }

    map = create_map(map_file);
    if(read_map(map_file, map) != 0) {
        printf("Error reading map");
        return 1;
    }

    /* Insert initial state of the game*/
    insert_start(game_ll, copy_map(map));

    while(1) {
        print_map(map);
        player_move = move_player(game_ll, &map);
        if(player_move == 1) {
            move_snake(map);
        }
    }
    return 0;
}