cmake_minimum_required(VERSION 3.29)
project(SudokuSolver)

add_compile_options(-ggdb)

file(GLOB C_FILES src/*.c)

add_executable(sudokusolver ${C_FILES})

target_link_libraries(sudokusolver raylib.a winmm)