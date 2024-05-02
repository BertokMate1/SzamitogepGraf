#include "whitesquare.h"

WhiteSquare createWhiteSquare(float x, float y) {
    WhiteSquare whiteSquare;
    whiteSquare.x = x;
    whiteSquare.y = y;
    return whiteSquare;
}

void drawWhiteSquare(WhiteSquare *whiteSquare) {
    glColor3f(1.0f, 1.0f, 1.0f); // White color

    glBegin(GL_QUADS);
        glVertex2f(whiteSquare->x, whiteSquare->y);
        glVertex2f(whiteSquare->x + 800.0f, whiteSquare->y);
        glVertex2f(whiteSquare->x + 800.0f, whiteSquare->y + 330.0f);
        glVertex2f(whiteSquare->x, whiteSquare->y + 330.0f);
    glEnd();
}
