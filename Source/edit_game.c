#include "edit_game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char BLOCKS[7][4][4] = {
    {
        {' ', ' ', ' ', ' '},
        {'@', '@', '@', '@'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    {
                {' ', ' ', ' ', ' '},
                {' ', '@', '@', ' '},
                {' ', '@', '@', ' '},
                {' ', ' ', ' ', ' '}
    },
    {
                {' ', '@', ' ', ' '},
                {'@', '@', '@', ' '},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '}
    },
    {
                {' ', ' ', ' ', ' '},
                {' ', '@', '@', ' '},
                {'@', '@', ' ', ' '},
                {' ', ' ', ' ', ' '}
    },
    {
                {' ', ' ', ' ', ' '},
                {' ', '@', '@', ' '},
                {' ', ' ', '@', '@'},
                {' ', ' ', ' ', ' '}
    },
    {
                {'@', ' ', ' ', ' '},
                {'@', '@', '@', ' '},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '}
    },
    {
                {' ', ' ', '@', ' '},
                {'@', '@', '@', ' '},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '}
    }
};

extern const int MAX_ROWS;
extern const int MAX_COLS;

void wipe_board(gameboard* gamestate) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            gamestate->board[i][j] = ' ';
        }
    }
}

/**
 * @brief Function used to initialize game state allocating memory in the heap for the game board and setting score and game over flag
 * @return gameboard
 */
gameboard* initialize_state() {
    gameboard* gamestate = malloc(sizeof(gameboard));
    if (gamestate == NULL) {
        printf("malloc failed\n");
        Sleep(1000);
        exit(-1);
    }
    gamestate->board = calloc(MAX_ROWS, sizeof(char*));
    for (int i = 0; i < MAX_ROWS; i++) {
        gamestate->board[i] = calloc(MAX_COLS, sizeof(char));
        if (gamestate->board[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(gamestate->board[j]);
            }
            free(gamestate->board);
            printf("malloc failed\n");
            Sleep(1000);
            exit(-1);
        }
    }
    wipe_board(gamestate);
    gamestate->gameover = false;
    gamestate->score = 0;
    return gamestate;
}
/**
 *@details Function used to shuffle the pieces in the global variable 'BLOCKS' to iterate through them as to not repeat the same one twice and to be fair.
 *@brief Function used to shuffle the pieces for usage
 *@return void
 */

void swap(char board[7][4][4], int i, int j) {
    char temp[4][4];
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            temp[r][c] = board[j][r][c];
        }
    }
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            board[j][r][c] = board[i][r][c];
        }
    }
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            board[i][r][c] = temp[r][c];
        }
    }
}

void shuffle(char blocks[7][4][4]) {
    int f = 0;
    int j = 0;
    for (int i = 0; i < 7; i++) {
        while (f == j) {
            f = rand() % 6;
            j = rand() % 6;
        }
        swap(blocks, rand()%7, rand()%7);
        f = rand() % 6;
        j = rand() % 6;
    }
}


/**
 * @details Function starts by seeding with the current time then uses modulo operator to get a random number from 0 to 4 which is then saved in the canvas pointer passed as a param
 * @return None
 * @brief function to get random int between from 0-4
 * @param canvas
 */
void get_rotation(canvas* canvas) {
    srand(time(NULL));
    canvas->rotation = rand()%4;
}

/**
 * @details Function used to allocate memory in the heap for canvas then allocate memory for the piece inside the canvas it also handles malloc error if it occurs
 * @param
 * @brief Function used to set up the canvas in the heap.
 * @return canvas*
 */
canvas* setup_canvas() {
    canvas* canvas = malloc(sizeof(canvas));
    if (canvas == NULL) {
        printf("malloc failed\n");
        Sleep(1000);
        exit(-1);
    }
    canvas->piece = calloc(4, sizeof(char*));
    if (canvas->piece == NULL) {
        printf("malloc failed\n");
        free(canvas);
        Sleep(1000);
        exit(-1);
    }
    for (int i = 0; i < 4; i++) {
        canvas->piece[i] = calloc(4, sizeof(char));
        if (canvas->piece[i] == NULL) {
            printf("malloc failed\n");
            for (int j = 0; j < i; j++) {
                free(canvas->piece[j]);
            }
            free(canvas->piece);
            free(canvas);
            Sleep(1);
            exit(-1);
        }
    }
    get_block(canvas);
    return canvas;
}


/**
 * @return
 * @brief Function that shuffles the board if needed and gets a pseudo random piece from the global variable BLOCKS
 * @param data
 */
void get_block(canvas* data) {
    if (data->iteration == -1) {
        shuffle(BLOCKS);
        data->iteration++;
        get_block(data);
    }
    else if (data->iteration > 7) {
        data->iteration = -1;
        get_block(data);
    }
    else if (data->iteration < 0) {
        data->iteration = -1;
        get_block(data);
    }
    else {
       for (int i =0; i < 4; i++){
            for (int j = 0; j < 4; j++) {
                data->piece[i][j] = BLOCKS[data->iteration][i][j];
            }
       }
        rotate(data);
        data->iteration++;
    }
}

/**
 * @brief Function that rotates the piece inside the canvas by 90 degree each iteration
 * @param canvas
 */
void rotate(canvas* canvas) {
    get_rotation(canvas);
    char** piece = calloc(4, sizeof(char*));
    if (piece == NULL) {
        printf("malloc failed\n");
        Sleep(1000);
        exit(-1);
    }

    for (int i = 0; i < 4; i++) {
        piece[i] = calloc(4, sizeof(char));
        if (piece[i] == NULL) {
            printf("malloc failed\n");
            for (int j = 0; j < i; j++) {
                free(piece[j]);
            }
        }
    }

    if (canvas -> rotation == 1) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                piece[j][3-i] = canvas->piece[i][j];
            }
        }
    }else if (canvas -> rotation == 2) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                piece[3-j][i] = canvas->piece[i][j];
            }
        }
    }else if (canvas -> rotation == 3) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                piece[3-j][3-i] = canvas->piece[i][j];
            }
        }
    }else {
        for (int i = 0; i < 4; i++) {
            free(piece[i]);
        }
        free(piece);
        return;
    }

    for(int j = 0; j < 4; j++){
        free(canvas->piece[j]);
    }
    free(canvas->piece);
    canvas->piece = piece;

}

/**
 * @brief function that uses other helper functions to get a random block from the global variable BLOCKS
 * @param canvas
 */
void block(canvas* canvas) {
    get_block(canvas);
    get_rotation(canvas);
    rotate(canvas);
}