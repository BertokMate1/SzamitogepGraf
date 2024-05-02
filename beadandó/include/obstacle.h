#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "square.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    float x, y;
    float width, height;
} Obstacle;

void generateObstacles(Obstacle *obstacles, int *numObstacles);
void moveObstacles(Obstacle *obstacles, int *numObstacles, Square *square, int *highscore);
void drawObstacles(Obstacle *obstacles, int numObstacles);

#endif // OBSTACLE_H
