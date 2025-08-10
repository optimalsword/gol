#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "screen.h"



uint32_t find_num_neighbors(Board* b, int32_t row, int32_t col) {
    uint32_t ret = 0;

    int8_t index = 0;
    if (row > 0) {
        index = row - 1;
    }
    // check left side
    int8_t i = index;
    while (col > 0 && i <= row + 1 && i < b->rows) {
        if (b->board[i][col-1].isAlive) {
            ++ret;
        }

        ++i;
    }

    // check right side
    i = index;
    while (col + 1 < b->cols && i <= row + 1 && i < b->rows) {
        if (b->board[i][col+1].isAlive) {
            ++ret;
        }

        ++i;
    }

    // check above
    if (row > 0 && b->board[row-1][col].isAlive) {
        ++ret;
    }
    
    // check below
    if (row + 1 < b->rows && b->board[row+1][col].isAlive) {
        ++ret;
    }


    return ret;
}


void simulate(Board* b) {
    CellCoords* dying_cells = (CellCoords*)malloc(sizeof(CellCoords));
    CellCoords* spawning_cells = (CellCoords*)malloc(sizeof(CellCoords));

    uint32_t num_dying_cells = 0;
    uint32_t num_spawning_cells = 0;

    uint32_t dying_buf_size = 1;
    uint32_t spawning_buf_size = 1;


    for (int32_t i = 0; i < b->rows; ++i) {
        for (int32_t j = 0; j < b->cols; ++j) {
            Cell* cur_cell = b->board[i] + j;
            uint32_t alive_neighbors = find_num_neighbors(b, i, j);
            if (cur_cell->isAlive) {
                // rule 1 - solitude
                // each cell with one or no neighbors dies
                // rule 2 - overpopulation
                if (alive_neighbors <= 1 || alive_neighbors >= 4) {
                    CellCoords cell;
                    cell.x = j;
                    cell.y = i;
                    uint32_t index = num_dying_cells++;
                    if (num_dying_cells > dying_buf_size) {
                        dying_buf_size = num_dying_cells + 1;
                        dying_cells = realloc(dying_cells, dying_buf_size*sizeof(CellCoords));
                    }

                    dying_cells[index] = cell;
                    printf("not crashed yet %d\n", index);
                }
                // rule 3 is implicit
                // each cell with 2 or three neihbors remains alive
            } else {
                // each cell with three neighbors becomes populated
                if (alive_neighbors == 3) {
                    CellCoords cell;
                    cell.x = j;
                    cell.y = i;
                    uint32_t index = num_spawning_cells++;
                    if (num_spawning_cells > spawning_buf_size) {
                        spawning_buf_size = num_spawning_cells + 1;
                        spawning_cells = realloc(spawning_cells, spawning_buf_size*sizeof(CellCoords));
                    }

                    spawning_cells[index] = cell;
                }
            }
        }
    }

    for (uint32_t i = 0; i < num_dying_cells; ++i) {
        b->board[dying_cells[i].y][dying_cells[i].x].isAlive = 0;
    }

    for (uint32_t i = 0; i < num_spawning_cells; ++i) {
        b->board[spawning_cells[i].y][spawning_cells[i].x].isAlive = 1;
    }

    free(dying_cells);
    free(spawning_cells);
}



int main() {
    Board board;
    init_board(&board, 16, 16);

    printf("TEST\n");

    GolScreen screen;
    const char* title = "Conway's Game Of Life";

    init_screen(&screen, &board, 1200, 1200, title);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_lines(&screen, &board);
        EndDrawing();

        if (board.simulating) {
            simulate(&board);
        }

        process_controls(&screen, &board);
        update_screen(&screen, &board);
    }

    CloseWindow();


    free_board(&board);

    return 0;
}