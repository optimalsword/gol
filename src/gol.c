#include <stdio.h>
#include "board.h"



int main() {
    Board board;
    init_board(&board, 64, 64);


    free_board(&board);

    return 0;
}