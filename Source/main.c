#include "game.h"
#include "threading.h"

int main(void) {
    srand(time(NULL));
    hide_cursor();
    system("cls");
    gameboard* gamestate = initialize_state();
    canvas* canvas = setup_canvas(gamestate);
    get_block(canvas);
    place_block(canvas, gamestate);
    Sleep(100);
    draw_state(gamestate);
    start_drop_thread(gamestate);
    while (!gamestate->gameover) {
        if (kbhit()) {
            int input = get_input();
            if (input == 1 || input == 2) {
                move_pieces(input, gamestate);
            }else if (input == 3 || input == 4) {
                rotate_piece(gamestate, input);
            }
            Sleep(100);
            draw_state(gamestate);
        } else {
            Sleep(50);  // Small delay to prevent busy waiting
        }
    }
    // Cleanup
    for (int i = 0; i < MAX_ROWS; i++) {
        free(gamestate->board[i]);
    }
    free(gamestate->board);
    free(gamestate);
    for (int i = 0; i < 4; i++) {
        free(canvas->piece[i]);
    }
    free(canvas->piece);
    free(canvas);
    return 0;
}