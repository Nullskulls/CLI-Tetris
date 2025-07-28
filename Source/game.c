#include "game.h"

const int MAX_ROWS = 20;
const int MAX_COLS = 10;
int paused = 0;
bool is_valid(const canvas* canvas, gameboard* gamestate) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (canvas->piece[i][j] == 0) continue;
            if (gamestate->board[i][j+3] != 0) {
                gamestate->gameover = true;
                return false;
            }
        }
    }
    return true;
}

void place_block(const canvas* canvas, gameboard* gamestate) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (canvas->piece[i][j] == 0) continue;
            gamestate->board[i][j+3] = canvas->piece[i][j];
        }
    }
}

int get_input(){
    if (kbhit()) {
        char key = getch();
        switch (key) {
            case 'a': return 1;
            case 'd': return 2;
            case 'q': return 3;
            case 'e': return 4;
            case 27: {
            }
            default: return 0;
        }
    }
    return 0;
}

void hide_cursor(void) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}


int get_input_blocking(void) {
    printf("Enter direction (w/a/s/d or ESC to quit): ");
    char key = getchar();

    switch (key) {
        case 'a': return 1;
        case 'd': return 2;
        case 'q': return 3;
        case 'e': return 4;
        case 27:  return 5;
        default: return 0;
    }
}
bool is_free_left(gameboard* gamestate) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                if (gamestate->board[i][j-1] != ' ' && gamestate->board[i][j-1] != '@') return false;
            }
        }
    }
    return true;
}


bool is_free_right(gameboard* gamestate) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                if (gamestate->board[i][j+1] != ' ' && gamestate->board[i][j+1] != '@') return false;
            }
        }
    }
    return true;
}

bool is_valid_move(int direction, gameboard* gamestate) {
    if (direction == 1) {
        for (int i = 0; i < MAX_ROWS; i++) {
            if (gamestate->board[i][0] == '@') return false;
        }
        if (is_free_left(gamestate)) {
            return true;
        }
    }
    else if (direction == 2) {
        for (int i = 0; i < MAX_ROWS; i++) {
            if (gamestate->board[i][MAX_COLS-1] == '@') return false;
        }
        if (is_free_right(gamestate)) return true;
    }
    return false;
}

void move_pieces(int direction, gameboard* gamestate) {
     if (direction == 1 && is_valid_move(direction, gamestate)) {
         for (int i = 0; i < MAX_ROWS; i++) {
             for (int j = 0; j < MAX_COLS; j++) {
                 if (gamestate->board[i][j] == '@') {
                     gamestate->board[i][j] = ' ';
                     gamestate->board[i][j-1] = '@';
                 }
             }
         }
     }else if (direction == 2 && is_valid_move(direction, gamestate)){
            for (int i = MAX_ROWS-1; i > -1; i--) {
                for (int j = MAX_COLS-1; j > -1; j--) {
                    if (gamestate->board[i][j] == '@') {
                        gamestate->board[i][j] = ' ';
                        gamestate->board[i][j+1] = '@';
                }
            }
        }
    }
}

bool is_droppable(gameboard* gamestate) {
    for (int i = MAX_ROWS-1; i > -1; i--) {
        for (int j = MAX_COLS-1; j > -1; j--) {
            if (gamestate->board[i][j] == '@') {
                if (i >= 19) return false;
                if (!(gamestate->board[i+1][j] == ' ' || gamestate->board[i+1][j] == '@')) return false;
            }
        }
    }
    return true;
}

void drop_pieces(gameboard* gamestate) {
    if (is_droppable(gamestate)) {
        for (int i = MAX_ROWS-1; i > -1; i--) {
            for (int j = MAX_COLS-1; j > -1; j--) {
                if (gamestate->board[i][j] == '@') {
                    gamestate->board[i][j] = ' ';
                    gamestate->board[i+1][j] = '@';
                }
            }
        }
    }else {
        for (int i = MAX_ROWS-1; i > -1; i--) {
            for (int j = MAX_COLS-1; j > -1; j--) {
                if (gamestate->board[i][j] == '@') {
                    gamestate->board[i][j] = '#';
                }
            }
        }
    }
}

void rotate_piece(gameboard* gamestate, int direction) {
    paused = 1;
    canvas* canvas = calloc(1, sizeof(canvas));
    if (canvas == NULL) {
        printf("malloc failed.");
        Sleep(1000);
        exit(-1);
    }
    canvas->piece = calloc(4, sizeof(char*));
    for (int i = 0; i < 4; i++) {
        canvas->piece[i] = calloc(MAX_COLS, sizeof(char));
    }
    int min_i=19;
    int min_j=9;
    canvas->rotation = direction-2;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                if (i < min_i) {
                    min_i = i;
                }
                if (j < min_j) {
                    min_j = j;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            canvas->piece[i][j] = '0';
        }
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                canvas->piece[i-min_i][j-min_j] = '@';
            }
        }
    }
    rotate(canvas);
    char** temp_board = malloc(sizeof(char*)* MAX_ROWS);
    if (temp_board == NULL) {
        printf("malloc failed.");
        Sleep(1000);
        exit(-1);
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        temp_board[i] = malloc(sizeof(char) * MAX_COLS);
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                temp_board[i][j] = ' ';
                continue;
            }
            temp_board[i][j] = gamestate->board[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (canvas->piece[i][j] == '@') {
                if (min_i+i >= MAX_ROWS && min_j+j >= MAX_COLS) {
                    for (int f = 0; f < MAX_ROWS; f++) {
                        free(gamestate->board[f]);
                    }
                    free(gamestate->board);
                    gamestate->board = temp_board;
                    for (int f = 0; f < 4; f++) {
                        free(canvas->piece[f]);
                    }
                    free(canvas->piece);
                    free(canvas);
                    return;
                }
                if (temp_board[min_i+i][min_j+j] == ' ') {
                    temp_board[min_i+i][min_j+j] = '@';
                    continue;
                }
                for (int f = 0; f < MAX_ROWS; f++) {
                    free(gamestate->board[f]);
                }
                free(gamestate->board);
                gamestate->board = temp_board;
                for (int f = 0; f < 4; f++) {
                    free(canvas->piece[f]);
                }
                free(canvas->piece);
                free(canvas);
                return;
            }
        }
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        free(gamestate->board[i]);
    }
    free(gamestate->board);
    gamestate->board = temp_board;
    for (int i = 0; i < 4; i++) {
        free(canvas->piece[i]);
    }
    free(canvas->piece);
    paused = 0;
}

void* drop(gameboard* gamestate) {
    while (!gamestate->gameover) {
        if (paused == 1) continue;
        drop_pieces(gamestate);
        Sleep(700);
    }
    return NULL;
}


