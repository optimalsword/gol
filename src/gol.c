#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "gol.h"

// @param b : board to initialize

void init_board(Board* b, uint32_t rows, uint32_t cols) {

    b->rows = rows;
    b->cols = cols;

    // the board itself
    b->board = (Cell**)malloc(rows * sizeof(void*)); // fancy size of for just getting pointer size
    for (uint32_t i = 0; i < rows; ++i) {
        // allocate the row
        b->board[i] = (Cell*)malloc(cols * sizeof(Cell));
        for (uint32_t j = 0; j < cols; ++j) {
            // do some initialization for each cell
            b->board[i][j].isAlive = 0;
        }
    }
}


void free_board(Board* b) {
    for (uint32_t i = 0; i < b->rows; ++i) {
        free(b->board[i]);
    }
    free(b->board);
}



int main() {
    Board board;
    init_board(&board, 64, 64);


    free_board(&board);

    return 0;
}