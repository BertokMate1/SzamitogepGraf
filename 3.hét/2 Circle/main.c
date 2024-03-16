#include "circle.h"

#define NUM_SEGMENTS 32

int main(int argc, char *argv[])
{
    Circle circle;
    double area;
    SDL_Color color = {255, 0, 255, 255};
    set_circle_data(&circle, 5, 10, 8, color);
    area = calc_circle_area(&circle);

    printf("Circle area: %lf\n", area);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    bool quit = false;
    SDL_Event event;

    double radius = circle.radius;
    double centerX = 400;
    double centerY = 300;
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Kör közelítése szakaszokkal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    double angle;
    double segmentAngle = 2 * M_PI / NUM_SEGMENTS;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < NUM_SEGMENTS; i++)
    {
        angle = i * segmentAngle;
        double x1 = centerX + radius * cos(angle);
        double y1 = centerY + radius * sin(angle);
        double x2 = centerX + radius * cos(angle + segmentAngle);
        double y2 = centerY + radius * sin(angle + segmentAngle);
        SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }

    SDL_RenderPresent(renderer);

    while (!quit)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
