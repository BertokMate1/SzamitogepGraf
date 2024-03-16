#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_COUNT 100

typedef struct
{
    Uint8 r, g, b;
} Color;

typedef struct
{
    SDL_Point start;
    SDL_Point end;
    Color color;
} Line;

void printMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    printf("Mouse position: (%d, %d)\n", x, y);
}

Color pickColor(SDL_Renderer *renderer)
{
    Color colors[] = {
        {255, 0, 255}, // Purple
        {0, 255, 255},  // Cyan
        {255, 255, 0}, // Yellow
        {0, 255, 0},   // Green
        {0, 0, 255},   // Blue
        {255, 0, 0}   // Red
    };

    int paletteSize = sizeof(colors) / sizeof(colors[0]);
    int boxWidth = 20;
    int boxHeight = 20;
    int paletteX = 10;
    int paletteY = 10;

    SDL_Event e;
    SDL_Rect rect;
    rect.w = boxWidth;
    rect.h = boxHeight;

    for (int i = 0; i < paletteSize; ++i)
    {
        rect.x = paletteX + i * (boxWidth + 5);
        rect.y = paletteY;
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_RenderPresent(renderer);

    while (1)
    {
        SDL_WaitEvent(&e);
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseY >= paletteY && mouseY <= paletteY + boxHeight)
            {
                int colorIndex = (mouseX - paletteX) / (boxWidth + 5);
                if (colorIndex >= 0 && colorIndex < paletteSize)
                {
                    return colors[colorIndex];
                }
            }
        }
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Line Drawing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Line lines[MAX_LINE_COUNT];
    int lineCount = 0;

    SDL_Event e;
    int drawingLine = 0;
    Line currentLine;
    Color currentColor = {255, 255, 255};

    while (1)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                SDL_Quit();
                return 0;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (drawingLine == 0)
                {
                    currentLine.start.x = e.button.x;
                    currentLine.start.y = e.button.y;
                    drawingLine = 1;
                }
                else
                {
                    currentLine.end.x = e.button.x;
                    currentLine.end.y = e.button.y;
                    currentLine.color = currentColor;
                    lines[lineCount++] = currentLine;
                    drawingLine = 0;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < lineCount; ++i)
        {
            SDL_SetRenderDrawColor(renderer, lines[i].color.r, lines[i].color.g, lines[i].color.b, 255);
            SDL_RenderDrawLine(renderer, lines[i].start.x, lines[i].start.y, lines[i].end.x, lines[i].end.y);
            SDL_Rect rect = {lines[i].start.x, lines[i].start.y, lines[i].end.x - lines[i].start.x, lines[i].end.y - lines[i].start.y};
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_RenderPresent(renderer);
    }
}