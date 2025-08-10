#ifndef GOL_H
#define GOL_H

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
} Board;


// the board will take up a very large amount of memory.. oh well
// get it correct first and then optimize later

#endif