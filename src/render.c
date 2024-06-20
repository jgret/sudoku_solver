#include <raylib.h>
#include "render.h"

static Cell selected_cell = {-1, -1};
static Cell hovered_cell = {-1, -1};
static Cell error_cell = {-1, -1};
static Font font;

void render_init()
{
    font = LoadFont("../data/font/ChunkFive-Regular.otf");
}

void set_hovered_cell(Cell cell)
{
    hovered_cell = cell;

}

void set_selected_cell(Cell cell)
{
    selected_cell = cell;
}

void set_error_cell(Cell cell) 
{
    error_cell = cell;
} 

Cell get_cell_by_mouse(Vector2 pos) {

    Cell ret = {
        .row = (int) pos.x / (GetScreenWidth() / 9),
        .col = (int) pos.y / (GetScreenHeight() / 9)
    };

    return ret;
}

Cell get_selected_cell() 
{
    return selected_cell;
}

Cell get_hovered_cell() 
{
    return hovered_cell;
}

Cell get_error_cell() 
{
    return error_cell;
}

void render_sudoku(Sudoku *sudoku) 
{

    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();
    float cell_w = (float) screen_w / 9.0f;
    float cell_h = (float) screen_h / 9.0f;

    if (hovered_cell.row > -1 && hovered_cell.col > -1) {
        DrawRectangle(cell_w * hovered_cell.row, cell_h * hovered_cell.col, cell_w, cell_h, YELLOW);
    }

    if (selected_cell.row > -1 && selected_cell.col > -1) {
        DrawRectangle(cell_w * selected_cell.row, cell_h * selected_cell.col, cell_w, cell_h, BLUE);
    }

    if (error_cell.row > -1 && error_cell.col > -1) {
        DrawRectangle(cell_w * error_cell.row, cell_h * error_cell.col, cell_w, cell_h, RED);
    }

    for (int i = 0; i <= 9; i++) {

        float thickness = 2.0f;
        if (i % 3 == 0)
            thickness = 3.0f;

        DrawLineEx((Vector2) { i * cell_w, 0}, (Vector2) {i * cell_w, screen_h}, thickness, BLACK);
        DrawLineEx((Vector2) {0, i * cell_h}, (Vector2) {screen_w, i * cell_h}, thickness, BLACK);
    }

    for (int rows = 0; rows < 9; rows++) {
        for (int cols = 0; cols < 9; cols++) {
            int num = sudoku->nums[rows][cols];
           
            const char* text = TextFormat("%i", num);
            int fontsize = 30;
            Vector2 dim = MeasureTextEx(font, text, fontsize, 0);

            if (num >= 1 && num <= 9)
                DrawTextEx(font, text, (Vector2){rows * cell_w + cell_w / 2 - dim.x / 2 + 1, cols * cell_h + cell_h / 2 - dim.y / 2 + 1}, fontsize, 0, BLACK);

        }
    }    
}