cmake_minimum_required(VERSION 3.10)
project(CLI_Tetris)

set(CMAKE_C_STANDARD 11)

add_executable(CLI_Tetris
        Source/main.c
        Source/game.c
        Source/edit_game.c
        Source/draw.c
        Source/threading.c
)
