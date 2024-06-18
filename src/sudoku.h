#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <stdint.h>

typedef struct {

    uint8_t nums[9][9];
    
} Sudoku;

typedef struct {
    int row;
    int col;
} Cell;

void sudoku_clear(Sudoku* s);

int sudoku_load(Sudoku* s, char* filepath);

#endif
