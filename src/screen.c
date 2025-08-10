#include <stdlib.h>
#include "screen.h"


static CellCoords convert_grid_to_cell(uint32_t height, uint32_t width, Vector2 grid, uint32_t rows, uint32_t cols) {
    float cell_height = height / rows;
    float cell_width = width / cols;

    uint32_t row = 0;
    uint32_t col = 0;
    for (uint32_t i = 0; i < rows; ++i) {
        // find row
        if (i * cell_height <= grid.y && (i * cell_height) + cell_height >= grid.y) {
            row = i;
            break;
        }
    }
    for (uint32_t i = 0; i < cols; ++i) {
        // find column
        if (i * cell_width <= grid.x && (i * cell_width) + cell_width >= grid.x) {
            col = i;
            break;
        }
    }

    CellCoords coords;
    coords.x = col;
    coords.y = row;

    return coords;
}


static Vector2 convert_cell_to_grid(uint32_t height, uint32_t width, CellCoords coords, uint32_t rows, uint32_t cols) {
    Vector2 grid;

    float cell_height = height / rows;
    float cell_width = width / cols;

    grid.x = coords.x * cell_width;
    grid.y = coords.y * cell_height;

    return grid;
}



void init_screen(GolScreen* screen, Board* b, uint32_t height, uint32_t width, const char* title) {
    screen->height = height;
    screen->width = width;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(width, height, title);
}


void draw_lines(GolScreen* screen, Board* b) {
    uint32_t cell_height = screen->height / b->rows;
    uint32_t cell_width = screen->width / b->cols;

    for (uint32_t i = 1; i <= b->rows; ++i) {
        DrawLine(0, i * cell_height, screen->width, i * cell_height, BLACK);
    }

    for (uint32_t i = 1; i <= b->cols; ++i) {
        DrawLine(i * cell_width, 0, i * cell_width, screen->height, BLACK);
    }
}


void update_screen(GolScreen* screen, Board* b) {
    screen->height = GetScreenHeight();
    screen->width = GetScreenWidth();

    // just draw the squares to the screen
    for (uint32_t i = 0; i < b->rows; ++i) {
        for (uint32_t j = 0; j < b->cols; ++j) {
            if (b->board[i][j].isAlive) {
                // draw the square to the screen
                CellCoords coords;
                coords.x = j;
                coords.y = i;
                Vector2 grid_coords = convert_cell_to_grid(screen->height, screen->width, coords, b->rows, b->cols);
                // DRAW THE SQUARE
                uint32_t cell_height = screen->height / b->rows;
                uint32_t cell_width = screen->width / b->cols;
                DrawRectangle(grid_coords.x, grid_coords.y, cell_width, cell_height, YELLOW);
            }
        }
    }
}


void process_controls(GolScreen* screen, Board* b) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // update board and color in the screen
        // first, figure out which cell we are in
        Vector2 mouse_pos = GetMousePosition();
        
        CellCoords coords = convert_grid_to_cell(screen->height, screen->width, mouse_pos, b->rows, b->cols);

        printf("row %d column %d\n", coords.y, coords.x);

        // set the board
        Cell* cur = b->board[coords.y] + coords.x;
        if (cur->isAlive) {
            cur->isAlive = 0;
        } else {
            cur->isAlive = 1;
        }

    } else if (IsKeyPressed(KEY_SPACE)) {
        // start simulation
        // TODO: find a way to decouple this
        if (b->simulating) {
            b->simulating = 0;
        } else {
            b->simulating = 1;
        }
    }
}