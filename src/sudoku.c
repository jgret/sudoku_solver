#include "sudoku.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sudoku_clear(Sudoku* s) {
    for (int i = 0; i  < 9; i++){
        for (int j = 0; j < 9; j++) {
            s->nums[i][j] = 0;
        }
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
            int num = 0;
            if (ch >= '1' && ch <= '9')
                num = ch - '0';

            s->nums[idx / 9][idx % 9] = num;

            idx++;

            if (idx >= 81)
                break;
        }
        
        if (idx != 81)
            ret = -1;
        
    } else {
        printf("File not found: %s\n", filepath);
    }
    fclose(file);

    return ret;
}

int sudoku_load(Sudoku *s, char *filepath)
{
    sudoku_clear(s);
    return load_oneline(s, filepath);
}
