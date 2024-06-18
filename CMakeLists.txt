cmake_minimum_required(VERSION 3.29)
project(SudokuSolver)

add_compile_options(-ggdb)

file(GLOB C_FILES src/*.c)

add_executable(sudokusolver ${C_FILES})

target_include_directories(sudokusolver PUBLIC D:/lib/raylib-5.0_win64_mingw-w64/raylib-5.0_win64_mingw-w64/include)
target_link_libraries(sudokusolver raylib.a winmm)