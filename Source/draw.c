#include "draw.h"

extern const int MAX_ROWS;
extern const int MAX_COLS;


void draw_state(gameboard* gamestate) {
    printf("\033[H");
    printf("Press ESC to exit.\n");

    for (int i = 0; i < MAX_COLS*2+1; i++) {
        printf("*");
    }
    printf("\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        printf("*");
        for (int j = 0; j < MAX_COLS; j++) {
            if (j == 9) {
                printf("%c", gamestate->board[i][j]);
                continue;
            }
            printf("%c ", gamestate->board[i][j]);
        }
        printf("*\n");
    }
    for (int i = 0; i < MAX_COLS*2+1; i++) {
        printf("*");
    }
    printf("\n A-D to move and Q-E to rotate pieces.");
}
void draw_canvas(canvas* canvas) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%c", canvas->piece[i][j]);
        }
        printf("\n");
    }
}