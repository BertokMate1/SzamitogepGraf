#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct Circle
{
	double x;
	double y;
	double radius;
} Circle;

void set_circle_data(Circle *circle, double x, double y, double radius, SDL_Color color);
double calc_circle_area(const Circle *circle);

#endif // CIRCLE_H
