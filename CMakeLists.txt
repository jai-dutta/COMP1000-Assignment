cmake_minimum_required(VERSION 3.29)
project(COMP1000_Assignment C)

set(CMAKE_C_STANDARD 90)

include_directories(src)

add_executable(COMP1000_Assignment
    src/game.c
    src/game.h
    src/input.c
    src/input.h
    src/linkedList.c
    src/linkedList.h
    src/main.c
    src/map.c
    src/map.h
    src/random.c
    src/random.h)
