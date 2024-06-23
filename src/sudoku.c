#include "sudoku.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool cell_valid(Cell cell)
{
    return cell.row >= 0 && cell.col >= 0 && cell.row < 9 && cell.col < 9;
}

void sudoku_init(Sudoku *s)
{
    sudoku_clear(s);
}

void sudoku_clear(Sudoku *s)
{
    for (int i = 0; i  < 9; i++){
        for (int j = 0; j < 9; j++) {
            s->nums[i][j] = 0;
        }
    }

    for (int i = 0; i < 9; i++) {
        s->fixed[i] = 0;
    }
}

void sudoku_set(Sudoku *s, Cell cell, uint8_t val)
{
    if (cell_valid(cell))
        if (val >= 0 && val <= 9)
            s->nums[cell.row][cell.col] = val;
}

bool sudoku_is_cell_fixed(Sudoku *s, Cell cell)
{
    return s->fixed[cell.row] & (1<<cell.col);
}

void sudoku_set_cell_fixed(Sudoku *s, Cell cell, bool fixed)
{
    if (fixed) {
        s->fixed[cell.row] |= (1<<cell.col);
    } else {
        s->fixed[cell.row] &= ~(1<<cell.col);
    }
}

static int load_csv(Sudoku *s, char* filepath) {

    FILE* file = fopen(filepath, "r");
    if (file) {

        int row = 0;

        // read line from file
        char buffer[200+1];
        while (fgets(buffer, sizeof(buffer), file)) {
            
            // numbers are seperated by commas
            // e.g.  1,2,3,4,5,6,7,8,9

            int idx = 0;
            char* part = strtok(buffer, ",");
            
            do {

                // convert number to integer
                char* endptr = NULL;
                int num = strtol(part, &endptr, 10);

                // store into sudoku
                s->nums[row][idx] = num;

                idx++;

            } while ((part = strtok(NULL, ",")));

            // should read 9 numbers
            if (idx != 9) {
                fclose(file);
                return -1;
            }

            // parse next row
            row++;
        }
    }
}

int load_oneline(Sudoku *s, char * filepath) {
    int ret = 0;
    FILE* file = fopen(filepath, "r");
    if (file) {

        char ch;
        int idx = 0;
        
        while ((ch = getc(file)) != EOF) {
            int row = idx / 9;
            int col = idx % 9;

            int num = 0;
            if (ch >= '1' && ch <= '9')
                num = ch - '0';

            s->nums[row][col] = num;
            sudoku_set_cell_fixed(s, (Cell){row, col}, num != 0);

            idx++;

            if (idx >= 81)
                break;
        }

        fclose(file);
        if (idx != 81)
            ret = -1;

    } else {
        printf("File not found: %s\n", filepath);
    }

    return ret;
}

int sudoku_load(Sudoku *s, char *filepath)
{
    sudoku_clear(s);
    return load_oneline(s, filepath);
}
