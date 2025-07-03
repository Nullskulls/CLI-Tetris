cmake_minimum_required(VERSION 3.31)
project(CLI_Tetris C)

set(CMAKE_C_STANDARD 99)

add_executable(CLISnakeGame
        Source/main.c
        Source/edit_game.c
        Source/draw.c
)
