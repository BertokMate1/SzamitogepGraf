#include "square.h"

Square createSquare(float x, float y) {
    Square square;
    square.x = x;
    square.y = y;
    square.jumping = 0;
    return square;
}

void jump(Square *square) {
    if (!square->jumping && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]) {
        square->jumping = 1;
    }

    if (square->jumping) {
        square->y -= 20.0f;

        if (square->y <= 100.0f) {
            square->y = 100.0f;
            square->jumping = 0;
        }
    } else {
        if (square->y < 300.0f) {
            square->y += 10.0f;
        }
    }
}

void drawSquare(Square *square) {
    glColor3f(1.0f, 0.5f, 0.0f); // Orange color

    glBegin(GL_QUADS);
        glVertex2f(square->x, square->y);              // Top-left corner
        glVertex2f(square->x + 30.0f, square->y);      // Top-right corner
        glVertex2f(square->x + 30.0f, square->y + 30.0f); // Bottom-right corner
        glVertex2f(square->x, square->y + 30.0f);      // Bottom-left corner
    glEnd();
}
