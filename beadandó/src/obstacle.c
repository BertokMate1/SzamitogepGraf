#include "obstacle.h"

Uint32 lastTime = 0;

void generateObstacles(Obstacle *obstacles, int *numObstacles) {
    Obstacle newObstacle;
    newObstacle.x = SCREEN_WIDTH + rand() % 400;
    newObstacle.y = rand() % (SCREEN_HEIGHT - 100);
    newObstacle.width = 50.0f;
    newObstacle.height = rand() % 100 + 50.0f;

    obstacles[*numObstacles] = newObstacle;
    (*numObstacles)++;
}

void moveObstacles(Obstacle *obstacles, int *numObstacles, Square *square, int *highscore) {
    for (int i = 0; i < *numObstacles; i++) {
        obstacles[i].x -= 5.0f;

        if (obstacles[i].x + obstacles[i].width < 0) {
            for (int j = i; j < *numObstacles - 1; j++) {
                obstacles[j] = obstacles[j + 1];
            }
            (*numObstacles)--;

            generateObstacles(obstacles, numObstacles);
        }

        if (obstacles[i].x < square->x + 30.0f && obstacles[i].x + obstacles[i].width > square->x &&
            obstacles[i].y < square->y + 30.0f && obstacles[i].y + obstacles[i].height > square->y) {
            if (*highscore > 0) {
                printf("Highscore: %d\n", *highscore);
            } else {
                printf("Highscore: None\n");
            }
            *highscore = 0;
            *numObstacles = 0;
            for (int k = 0; k < 5; k++) {
                generateObstacles(obstacles, numObstacles);
            }
            return;
        }
    }

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= 1000) {
        (*highscore)++;
        lastTime = currentTime;
    }
}

void drawObstacles(Obstacle *obstacles, int numObstacles) {
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < numObstacles; i++) {
        glBegin(GL_QUADS);
            glVertex2f(obstacles[i].x, obstacles[i].y);
            glVertex2f(obstacles[i].x + obstacles[i].width, obstacles[i].y);
            glVertex2f(obstacles[i].x + obstacles[i].width, obstacles[i].y + obstacles[i].height);
            glVertex2f(obstacles[i].x, obstacles[i].y + obstacles[i].height);
        glEnd();
    }
}
