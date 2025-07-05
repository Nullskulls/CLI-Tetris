#include "game.h"

#ifndef THREADING_H
#define THREADING_H
HANDLE start_drop_thread(gameboard* gamestate);
DWORD WINAPI drop_thread_func(LPVOID param);
#endif //THREADING_H
