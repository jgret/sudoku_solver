#include <stdio.h>
#include <solver.h>
#include <sudoku.h>
#include <time.h>

#define N_SOLVE 100

int main(char** argv, int argc) {

    char *filepath = "../data/hard_sudokus.txt";
    printf("Loading sudokus from %s\n", filepath);

    Sudoku sudokus[N_SOLVE];
    int loaded = sudoku_multi_load(sudokus, sizeof(sudokus) / sizeof(sudokus[0]), filepath);
    printf("Loaded %d sudokus\n", loaded);

    printf("Starting to solve\n");
    printf("----------------- START -----------------\n");
    int success = 0;

    double total_time = 0;

    for (int i = 0; i < loaded; i++) {
        printf(" > solving sudoku[%d]: ", i);
        clock_t t = clock();
        int ret = sovler_solve_sudoku(&sudokus[i]);
        t = clock() - t;
        double time_taken_ms = ((double)t)/CLOCKS_PER_SEC * 1000;
        total_time += time_taken_ms;
        if (ret == SUDOKU_VALID) {
            printf("success");
            success++;
        } else {
            printf("failed");
        }
        printf(" \t(%.01fms)\n", time_taken_ms);
    }

    printf("------------------ END ------------------\n");
    printf("solved %d/%d sudokus\n", success, loaded);
    printf("total time: %.1fms\n", total_time);
    printf("test done\n");

    printf("\n");

}