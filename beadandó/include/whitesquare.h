#ifndef WHITESQUARE_H
#define WHITESQUARE_H

#include "square.h"

typedef struct {
    float x, y;
} WhiteSquare;

WhiteSquare createWhiteSquare(float x, float y);
void drawWhiteSquare(WhiteSquare *whiteSquare);

#endif // WHITESQUARE_H