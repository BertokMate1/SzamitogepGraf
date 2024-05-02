#ifndef SQUARE_H
#define SQUARE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float x, y;
    int jumping;
} Square;

Square createSquare(float x, float y);
void jump(Square *square);
void drawSquare(Square *square);

#endif // SQUARE_H