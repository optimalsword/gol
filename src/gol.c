#include <stdio.h>
#include "board.h"



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
    for (int32_t i = 0; i < b->rows; ++i) {
        for (int32_t j = 0; j < b->cols; ++j) {
            Cell* cur_cell = b->board[i] + j;
            uint32_t alive_neighbors = find_num_neighbors(b, i, j);
            if (cur_cell->isAlive) {
                // rule 1 - solitude
                // each cell with one or no neighbors dies
                if (alive_neighbors <= 1) {
                    cur_cell->isAlive = 0;
                }
                // rule 2 - overpopulation
                // each cell with four or more neighbors dies
                if (alive_neighbors >= 4) {
                    cur_cell->isAlive = 0;
                }
                // rule 3 is implicit
                // each cell with 2 or three neihbors remains alive
            } else {
                // each cell with three neighbors becomes populated
                if (alive_neighbors == 3) {
                    cur_cell->isAlive = 1;
                }
            }
        }
    }
}



int main() {
    Board board;
    init_board(&board, 64, 64);

    board.board[0][0].isAlive = 1;
    board.board[0][1].isAlive = 1;
    board.board[1][1].isAlive = 1;

    printf("0, 0: %d\n", board.board[0][0].isAlive);
    simulate(&board);
    printf("0, 0: %d\n", board.board[0][0].isAlive);


    free_board(&board);

    return 0;
}