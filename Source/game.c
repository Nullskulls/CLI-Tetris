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
bool is_rotatable(gameboard* gamestate, int direction) {
    if (direction == 3) {
        //TODO: To be added

    }
}

void* drop(gameboard* gamestate) {
    while (!gamestate->gameover) {
        if (paused == 1) continue;
        drop_pieces(gamestate);
        Sleep(700);
    }
    return NULL;
}


