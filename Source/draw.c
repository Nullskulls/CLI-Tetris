//
// Created by Segfault on 7/3/2025.
//

#include "draw.h"

void draw_state(gameboard* gamestate) {
    printf("Press ESC to exit.\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("   %c", gamestate->board[i][j]);
        }
    }
    printf("\n WASD to move.");
}
