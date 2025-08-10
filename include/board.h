#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define BOARD_SIZE 256
// number of cells is going to be board_size squared


typedef unsigned char byte;


typedef struct Cell {
    byte isAlive; // 0 for false, 1 for true
} Cell;


typedef struct Board {
    Cell** board;

    uint32_t rows;
    uint32_t cols;

    byte simulating;
} Board;


void init_board(Board* b, uint32_t rows, uint32_t cols);
void free_board(Board* b);
void update_board(Board* b);


#endif