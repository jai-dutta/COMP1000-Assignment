#ifndef GAME_H
#define GAME_H
#include "input.h"
#include "map.h"
Controls process_input();
void game_over();
void move_player(Map* map);


#endif
