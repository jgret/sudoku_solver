#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int parse_oneline(Sudoku *s, char* str) {
    int idx = 0;

    int len = strlen(str);
    if (len < 81)
        return -1;

    char *p = str;

    while (*p != '\0') 
    {
        char ch = *p;
        int row = idx / 9;
        int col = idx % 9;

        int num = 0;
        if (ch >= '1' && ch <= '9')
            num = ch - '0';

        s->nums[row][col] = num;
        sudoku_set_cell_fixed(s, (Cell){row, col}, num != 0);

        idx++;
        p++;

        if (idx >= 81)
            break;
    }
    return 0;
}

int load_oneline(Sudoku *s, char * filepath) {
    int ret = 0;
    FILE* file = fopen(filepath, "r");
    if (file) {

        // read number of sudokus
        char buffer[200+1];
        fgets(buffer, sizeof(buffer), file);
        
        // parse sudoku
        fgets(buffer, sizeof(buffer), file);
        ret = parse_oneline(s, buffer);

        fclose(file);
 
    } else {
        printf("File not found: %s\n", filepath);
    }

    return ret;
}

/**
 * load multiple sudokus
 * @param s array of sudokus
 * @param count length of array
 * @param filepath file in wich sudokus are stored
 * @return int number of loaded sudokus
 */
int sudoku_multi_load(Sudoku *s, int count, char *filepath) 
{
    int num_loaded = 0;

    FILE* file = fopen(filepath, "r");
    if (file) {

        // read number of sudokus
        char buffer[200+1];
        fgets(buffer, sizeof(buffer), file);
        int sudoku_count = strtol(buffer, NULL, 10);

        if (count > sudoku_count)
            count = sudoku_count;

        // load sudokus
        for (int i = 0; i < count; i++) 
        {
            sudoku_clear(&s[i]);
            fgets(buffer, sizeof(buffer), file);
            int ret = parse_oneline(&s[i], buffer);
            
            if (ret == 0)
                num_loaded++;
            else 
                break;
        }

        fclose(file);

    } else {
        printf("File not found: %s\n", filepath);
    }

    return num_loaded;
}

/**
 * load one sudoku from a file
 * @param s sudoku struct pointer
 * @param filepath file with sudoku
 * @return int 0 on success, -1 on error
 */
int sudoku_load(Sudoku *s, char *filepath)
{
    int ret = sudoku_multi_load(s, 1, filepath);
    return ret == 1 ? 0 : -1;
}
