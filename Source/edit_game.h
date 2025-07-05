

#ifndef EDIT_GAME_H
#define EDIT_GAME_H
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

extern char BLOCKS[7][4][4];


typedef struct {
    char** board;
    int score;
    bool gameover;
}gameboard;

typedef struct {
    char** piece;
    int iteration;
    int rotation;
}canvas;

void get_block(canvas* data);
canvas* setup_canvas();
void shuffle(char blocks[7][4][4]);
gameboard* initialize_state();
void rotate(canvas* canvas);



#endif //EDIT_GAME_H
