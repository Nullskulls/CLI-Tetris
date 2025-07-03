

#ifndef EDIT_GAME_H
#define EDIT_GAME_H
#include <stdbool.h>
#include <windows.h>
const int MAX_COLS = 10;
const int MAX_ROWS = 20;

// Tetrominoes in order: I, O, T, S, Z, J, L
const int BLOCKS[7][4][4] = {
    // I Piece
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // O Piece
    {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // T Piece
    {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // S Piece
    {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // Z Piece
    {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // J Piece
    {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // L Piece
    {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    }
};


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
void shuffle(int *array, size_t n);
gameboard initialize_state();



#endif //EDIT_GAME_H
