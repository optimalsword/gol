#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"


typedef struct GolScreen {
    uint32_t height;
    uint32_t width;
} GolScreen;


void init_screen(GolScreen* screen, uint32_t height, uint32_t width, const char* title) {
    screen->height = height;
    screen->width = width;

}


#endif