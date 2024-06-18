#ifndef SOLVER_H_
#define SOLVER_H_

#include "sudoku.h"

typedef enum {
    SUDOKU_VALID = 0,
    SUDOKU_ROW_ERROR = -1,
    SUDOKU_COL_ERROR = -2,
    SUDOKU_FIELD_ERROR = -3,
} SudokuErr;

SudokuErr solver_check_cell(Sudoku *s, Cell cell);

SudokuErr solver_check_sudoku(Sudoku *s, Cell *fist_err);

SudokuErr sovler_solve_sudoku(Sudoku *s);

#endif