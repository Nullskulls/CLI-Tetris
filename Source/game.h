#ifndef GAME_H
#define GAME_H
#include "edit_game.h"
#include <stdio.h>
#include <conio.h>
#include "draw.h"
#include "edit_game.h"
#include "threading.h"
extern const int MAX_ROWS;
extern const int MAX_COLS;

void move_pieces(int direction, gameboard* gamestate);
bool is_valid_move(int direction, gameboard* gamestate);
bool is_free_right(gameboard* gamestate);
bool is_free_left(gameboard* gamestate);
int get_input_blocking(void);
void hide_cursor(void);
int get_input();
void drop_pieces(gameboard* gamestate);
bool is_droppable(gameboard* gamestate);
void place_block(const canvas* canvas, gameboard* gamestate);
bool is_valid(const canvas* canvas, gameboard* gamestate);
void* drop(gameboard* gamestate);
void rotate_piece(gameboard* gamestate, int direction);

#endif //GAME_H
