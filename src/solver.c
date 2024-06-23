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
    off_col *= 3;
    off_row *= 3;

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

static int solve_rec(Sudoku *s, int idx) 
{

    if (idx == 81)
        return 0;

    Cell cell = {
        .row = idx / 9,   
        .col = idx % 9,
    };

    if (cell.col == 7) {
        cell.col = 7;
    }
    
    if (sudoku_is_cell_fixed(s, cell)) 
    {
         // cell is fixed, goto next cell
        return solve_rec(s, idx + 1);
    } 
    else 
    {
        // try each number
        for (uint8_t n = 1; n <= 9; n++) {
            
            sudoku_set(s, cell, n); // set num in sudoku

            if (solver_check_cell(s, cell) == SUDOKU_VALID) 
            {
                // if no error, continue with next field
                int ret = solve_rec(s, idx + 1);
                if (ret == 0) {
                    // all cells have valid numbers
                    return 0;
                }
                
            }
        }

        // no number fits, clear cell and return error
        sudoku_set(s, cell, 0);
        return -1;

    }
}


SudokuErr sovler_solve_sudoku(Sudoku *s)
{
    int ret = solve_rec(s, 0);

    return ret == 0 ? SUDOKU_VALID : SUDOKU_NOT_SOLVABLE;
}
