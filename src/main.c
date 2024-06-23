#include <raylib.h>
#include <stdio.h>
#include "render.h"
#include "sudoku.h"
#include "solver.h"

int main() {

    InitWindow(500, 500, "Sudoku");
    SetTargetFPS(60);

    render_init();


    Sudoku sudoku;
    sudoku_init(&sudoku);
    if (sudoku_load(&sudoku, "../data/sudoku.txt") != 0) {
        printf("Failed to load sudoku\n");
        return -1;
    }


    while (!WindowShouldClose()) {
        
        Vector2 pos = GetMousePosition();
        set_hovered_cell(get_cell_by_mouse(pos));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            set_selected_cell(get_cell_by_mouse(pos));
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)) {
            Cell sel = get_selected_cell();
            if (sel.row >= 0 && sel.col >= 0)
                sudoku.nums[sel.row][sel.col] = 0;

        }

        if (IsKeyPressed(KEY_S)) {
            int ret = sovler_solve_sudoku(&sudoku);
            if (ret == SUDOKU_VALID) {
                printf("Sudoku solved!\n");
            } else {
                printf("Sudoku not solvable\n");
            }
            
        }

        // user number input
        char ch = GetCharPressed();
        if (ch >= '1' && ch <= '9') {
            Cell sel = get_selected_cell();

            if (!sudoku_is_cell_fixed(&sudoku, sel)) {
                if (cell_valid(sel))
                    sudoku.nums[sel.row][sel.col] = ch - '0';
            }
        }

        Cell first_err = {-1, -1};
        SudokuErr ret = solver_check_sudoku(&sudoku, &first_err);
        if (ret != SUDOKU_VALID)
            set_error_cell(first_err);
        else
            set_error_cell((Cell){-1, -1});

        BeginDrawing();

            ClearBackground(WHITE);
            render_sudoku(&sudoku); 

        EndDrawing();
    }    


    CloseWindow();
    return 0;
}