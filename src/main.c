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
    if (sudoku_load(&sudoku, "../data/sudoku.txt") != 0) {
        printf("Failed to load sudoku\n");
        return -1;
    }


    while (!WindowShouldClose()) {
        
        Vector2 pos = GetMousePosition();
        set_hovered_cell(get_cell_by_mouse(pos));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            // set_selected_cell(get_cell_by_mouse(pos));
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)) {
            Cell sel = get_selected_cell();
            if (sel.row >= 0 && sel.col >= 0)
                sudoku.nums[sel.row][sel.col] = 0;

        }

        // user number input
        char ch = GetCharPressed();
        if (ch != 0) {

            if (ch >= '1' && ch <= '7') {
                Cell sel = get_selected_cell();
                if (sel.row >= 0 && sel.col >= 0)
                    sudoku.nums[sel.row][sel.col] = ch - '0';
            }
        }

        Cell first_err = {-1, -1};
        SudokuErr ret = solver_check_sudoku(&sudoku, &first_err);
        set_selected_cell(first_err);

        BeginDrawing();

            ClearBackground(WHITE);
            render_sudoku(&sudoku); 

        EndDrawing();
    }    


    CloseWindow();
    return 0;
}