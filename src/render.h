#ifndef RENDER_H_
#define RENDER_H_

#include "sudoku.h"

void render_init();

void set_hovered_cell(Cell cell);
void set_selected_cell(Cell cell);
void set_error_cell(Cell cell);

Cell get_selected_cell();
Cell get_hovered_cell();
Cell get_error_cell();

Cell get_cell_by_mouse(Vector2 pos);

void render_sudoku(Sudoku *sudoku);

#endif