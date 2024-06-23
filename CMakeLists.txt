cmake_minimum_required(VERSION 3.29)
project(SudokuSolver)

add_compile_options(-ggdb)

# main program

file(GLOB C_FILES src/*.c)

add_executable(sudokusolver ${C_FILES})
target_link_libraries(sudokusolver raylib.a winmm)

# test program

add_executable(test_solve_sudokus test/test_solve_sudokus.c src/solver.c src/sudoku.c)
target_link_libraries(test_solve_sudokus winmm)
target_include_directories(test_solve_sudokus PUBLIC src)