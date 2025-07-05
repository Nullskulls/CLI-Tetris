//
// Created by Segfault on 7/5/2025.
//

#include "threading.h"

DWORD WINAPI drop_thread_func(LPVOID param) {
    gameboard* gamestate = (gameboard*)param;
    drop(gamestate);  // this already has its own while loop inside
    return 0;
}

HANDLE start_drop_thread(gameboard* gamestate) {
    return CreateThread(
        NULL,
        0,
        drop_thread_func,
        gamestate,
        0,
        NULL
    );
}

