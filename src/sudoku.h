#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {

    uint8_t nums[9][9];     // stores the sudoku grid
    uint16_t fixed[9];      // bit flag variables for modifiable gird cells (one element == one row)    

} Sudoku;

typedef struct {
    int row;
    int col;
} Cell;

bool cell_valid(Cell cell);

void sudoku_init(Sudoku *s);

void sudoku_clear(Sudoku *s);

void sudoku_set(Sudoku *s, Cell cell, uint8_t val);

bool sudoku_is_cell_fixed(Sudoku *s, Cell cell);

void sudoku_set_cell_fixed(Sudoku *s, Cell cell, bool fixed);

int sudoku_multi_load(Sudoku *s, int count, char *filepath);

int sudoku_load(Sudoku *s, char* filepath);

#endif
