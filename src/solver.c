#include "solver.h"

SudokuErr solver_check_cell(Sudoku *s, Cell cell)
{

    // check row
    uint16_t numSetMask = 0;

    for (int i = 0; i < 9; i++) 
    {
        uint8_t val = s->nums[cell.row][i];
        if (val) 
        {
            if (!(numSetMask & 1<<val)) // if number has not occoured
            {         
                numSetMask |= 1<<val;
            }
            else 
            {
                // ERROR, same number twice in row
                return SUDOKU_ROW_ERROR;
            }
        }
    }


    // check col
    numSetMask = 0;

    for (int i = 0; i < 9; i++) 
    {
        uint8_t val = s->nums[i][cell.col];

        if (val) 
        {
            if (!(numSetMask & 1<<val)) // if number has not occoured 
            {         
                numSetMask |= 1<<val;
            }
            else 
            {
                // ERROR, same number twice in col
                return SUDOKU_COL_ERROR;
            }
        }
    }

    // field check
    numSetMask = 0;

    int off_col = cell.col / 3;
    int off_row = cell.row / 3;

    for (int i = 0; i < 9; i++) 
    {
        int col = i % 3;
        int row = i / 3;

        uint8_t val = s->nums[off_row + row][off_col + col];
        if (val) 
        {
            if (!(numSetMask & 1<<val)) // if number has not occoured 
            {         
                numSetMask |= 1<<val;
            }
            else 
            {
                // ERROR, same number twice in field
                return SUDOKU_FIELD_ERROR;
            }
        }
    }

    return SUDOKU_VALID;
}

SudokuErr solver_check_sudoku(Sudoku *s, Cell *first_err)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            int ret = solver_check_cell(s, (Cell){i, j});
            if (ret != SUDOKU_VALID) {
                first_err->row = i;
                first_err->col = j;
                return ret;
            }
        }
    }

    return SUDOKU_VALID;
}

SudokuErr sovler_solve_sudoku(Sudoku *s)
{

}
