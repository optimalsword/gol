#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "raylib.h"
#include "board.h"


typedef struct CellCoords {
    uint32_t x;
    uint32_t y;
} CellCoords;


typedef struct GolScreen {
    uint32_t height;
    uint32_t width;
} GolScreen;

void init_screen(GolScreen* screen, Board* b, uint32_t height, uint32_t width, const char* title);

void draw_lines(GolScreen* screen, Board* b);

void update_screen(GolScreen* screeen, Board* b);

void process_controls(GolScreen* screen, Board* b);


#endif