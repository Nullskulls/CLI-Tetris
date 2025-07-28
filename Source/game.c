#include "game.h"

const int MAX_ROWS = 20;
const int MAX_COLS = 10;
int paused = 0;
int dropping = 0;
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
        case 'q': return 4;
        case 'e': return 3;
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
void fill_piece(char** piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece[i][j] = ' ';
        }
    }
}
void free_board(char** board) {
    for (int i = 0; i < MAX_ROWS; i++) {
        free(board[i]);
    }
    free(board);
}

void free_rotated(char** rotated_piece) {
    for (int i = 0; i < 4; i++) {
        free(rotated_piece[i]);
    }
    free(rotated_piece);
}

void rotate_piece(gameboard* gamestate, int rotation) {
    while (dropping == 1) {
        Sleep(10);
    }
    paused=1;
    //initializing piece holder
    char** rotated_piece = calloc(4, sizeof(char*));
    if (rotated_piece == NULL) {
        paused = 0;
        return;
    }
    for (int i = 0; i < 4; i++) {
        rotated_piece[i] = calloc(4, sizeof(char));
        if (rotated_piece[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(rotated_piece[j]);
            }
            free(rotated_piece);
            paused = 0;
            return;
        }
    }
    fill_piece(rotated_piece);
    //first capturing min row, col
    border* borders = malloc(sizeof(border));

    if (borders == NULL) {
        free_rotated(rotated_piece);
        paused = 0;
        return;
    }
    //initialize min(i,j)
    borders->min_i = MAX_ROWS-1;
    borders->min_j = MAX_COLS-1;
    //find border
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                if (i < borders->min_i) {
                    borders->min_i = i;
                }
                if (j < borders->min_j) {
                    borders->min_j = j;
                }
            }
        }
    }
    //now that we have our borders time to capture our piece.
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                if (rotated_piece[i-borders->min_i][j-borders->min_j] == ' ') {
                    rotated_piece[i-borders->min_i][j-borders->min_j] = '@';
                }
            }
        }
    }
    //initialize a canvas
    canvas* canvas = malloc(sizeof(canvas));
    if (canvas == NULL) {
        free_rotated(rotated_piece);
        free(borders);
        paused=0;
        return;
    }
    canvas->piece = rotated_piece;
    canvas->rotation = rotation-2;
    canvas->iteration = 0;
    rotated_piece = NULL;
    //now to pass it off to our helper func to be rotated
    rotate(canvas);
    //first we copy the board to a holder board
    //initializing
    char** temp_board = calloc(MAX_ROWS, sizeof(char*));
    if (temp_board == NULL) {
        free_rotated(canvas->piece);
        free(borders);
        free(canvas);
        paused = 0;
        return;
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        temp_board[i] = calloc(MAX_COLS, sizeof(char));
        if (temp_board[i] == NULL) {
            free_rotated(canvas->piece);
            free(borders);
            free(canvas);
            for (int j = 0; j < i; j++) {
                free(temp_board[j]);
            }
            paused = 0;
            return;
        }
    }
    //wiping it just in case
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            temp_board[i][j] = ' ';
        }
    }
    //copying of the board
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] != '@') {
                temp_board[i][j] = gamestate->board[i][j];
            }
        }
    }
    //now to place it back on the board adjusted
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (canvas->piece[i][j] == '@') {
                if (i+borders->min_i >= MAX_ROWS || j+borders->min_j >= MAX_COLS || temp_board[i+borders->min_i][j+borders->min_j] != ' ') {
                    free_rotated(canvas->piece);
                    free(borders);
                    free_board(temp_board);
                    paused = 0;
                    return;
                }else {
                    temp_board[i+borders->min_i][j+borders->min_j] = '@';
                }
            }
        }
    }
    free_rotated(canvas->piece);
    free(borders);
    free_board(gamestate->board);
    gamestate->board = temp_board;
    paused = 0;
}

bool is_clear(gameboard* gamestate) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (gamestate->board[i][j] == '@') {
                return false;
            }
        }
    }
    return true;
}

bool line_is_clearable(gameboard* gamestate, int index) {
    for (int i = 0; i < MAX_COLS; i++) {
        if (gamestate->board[index][i] != '#') {
            return false;
        }
    }
    return true;
}

void clear_line(gameboard* gamestate, int index) {
    for (int i = 0; i < MAX_COLS; i++) {
        gamestate->board[index][i] = ' ';
    }
}

void* clear_lines(gameboard* gamestate) {
    for (int i = MAX_ROWS-1; i > -1; i--) {
        if (line_is_clearable(gamestate, i)) {
            clear_line(gamestate, i);
        }
    }
}
bool is_hovering(gameboard* gamestate, int index) {
    for (int i = 0; i < MAX_COLS; i++) {
        if (gamestate->board[index][i] == '#') {
            if (index+1 < MAX_ROWS && gamestate->board[index+1][i] != ' ' || index + 1 >= MAX_ROWS) {
                return false;
            }
        }
    }
    return true;
}

void drop_line(gameboard* gamestate, int index) {
    for (int i = 0; i < MAX_COLS; i++) {
        if (gamestate->board[index][i] == '#') {
            gamestate->board[index][i] = ' ';
            gamestate->board[index+1][i] = '#';
        }
    }
}
void drop_hovering(gameboard* gamestate) {
    for (int i = MAX_ROWS-1; i > -1; i--) {
        if (is_hovering(gamestate, i)) {
            drop_line(gamestate, i);
        }
    }
}
void* drop(gameboard* gamestate) {
    canvas* canvas = setup_canvas(gamestate);
    while (!gamestate->gameover) {
        if (paused == 1) continue;
        clear_lines(gamestate);
        drop_hovering(gamestate);
        if (is_clear(gamestate)) {
            get_block(canvas);
            place_block(canvas, gamestate);
        }
        dropping = 1;
        drop_pieces(gamestate);
        dropping = 0;
        Sleep(300);
    }
    return NULL;
}


