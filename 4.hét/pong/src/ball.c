#include "ball.h"

void init_ball(Ball *ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 300;
    ball->speed_y = 300;
}

void update_ball(Ball *ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
}

void increase_ball_size(Ball *ball, float radius)
{
    if (ball->radius < 120)
    {
        ball->radius += radius;
    }
}

void decrease_ball_size(Ball *ball, float radius)
{
    if (ball->radius > 20)
    {
        ball->radius -= radius;
    }
}

void ball_position(Ball *ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
}

void render_ball(Ball *ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1)
    {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.1;
    }
    glEnd();
    glPopMatrix();
}