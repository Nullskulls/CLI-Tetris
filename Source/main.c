#include "game.h"
#include "threading.h"
#include <pthread.h>

int main(void) {
    srand(time(NULL));
    hide_cursor();
    system("cls");
    pthread_t dropper;
    gameboard* gamestate = initialize_state();
    canvas* canvas = setup_canvas(gamestate);
    get_block(canvas);
    place_block(canvas, gamestate);
    Sleep(100);
    draw_state(gamestate);
    start_drop_thread(gamestate);
    while (true) {
        if (kbhit() || true) {
            int input = get_input();
            if (input == 1 || input == 2) {
                move_pieces(input, gamestate);
            }else if (input == 3 || input == 4) {
                rotate_piece(gamestate, input);
            }else if (input == 5) {
                for (int i = 0; i < MAX_ROWS; i++) {
                    free(gamestate->board[i]);
                }
                free(gamestate->board);
                exit(0);
            }
            Sleep(100);
            draw_state(gamestate);
        }
    }
}