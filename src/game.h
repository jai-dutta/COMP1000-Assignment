#ifndef GAME_H
#define GAME_H
#include "input.h"
#include "map.h"
#include "linkedList.h"

Controls process_input(void);
void game_over(void);
int move_player(LinkedList* ll, Map** map);
void pickup_lantern(Map* map);
void carrying_lantern(Map* map);
void move_snake(Map* map);
void undo_turn(LinkedList* ll, Map** map);

#endif
