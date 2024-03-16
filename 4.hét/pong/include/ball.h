#ifndef BALL_H
#define BALL_H

#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_stdinc.h>

/**
 * Ball position and speed
 */
typedef struct Ball
{
    float x;
    float y;
    float radius;
    float speed_x;
    float speed_y;
} Ball;

/**
 * Move the ball to the given position.
 */
void init_ball(Ball *ball, float x, float y);

/**
 * Update the ball.
 * @param time elapsed time in seconds.
 */
void update_ball(Ball *ball, double time);

void increase_ball_size(Ball *ball, float radius);

void decrease_ball_size(Ball *ball, float radius);

void ball_position(Ball *ball, float x, float y);

/**
 * Render the ball.
 */
void render_ball(Ball *ball);

#endif /* BALL_H */
