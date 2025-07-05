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
            int input = get_input_blocking();
            move_pieces(input, gamestate);
            Sleep(100);
            draw_state(gamestate);
        }
    }
}