#include "square.h"
#include "obstacle.h"
#include "whitesquare.h"

SDL_Window *window = NULL;
SDL_GLContext context;

float squareX = 50.0f;
float squareY = 300.0f;

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Gamblers Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation error: %s\n", SDL_GetError());
        return -1;
    }

    context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        printf("OpenGL context creation error: %s\n", SDL_GetError());
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    srand(time(NULL));

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (init() < 0) {
        MessageBox(NULL, "Initialization error", "Error", MB_ICONERROR | MB_OK);
        return -1;
    }

    Square square = createSquare(squareX, squareY);
    Obstacle obstacles[100];
    int numObstacles = 0;
    int highscore = 0;
    WhiteSquare whiteSquare = createWhiteSquare(0.0f, 330.0f);

    for (int i = 0; i < 5; i++) {
        generateObstacles(obstacles, &numObstacles);
    }

    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        jump(&square);
        moveObstacles(obstacles, &numObstacles, &square, &highscore);
        glClear(GL_COLOR_BUFFER_BIT);
        drawWhiteSquare(&whiteSquare); // Draw the white square
        drawObstacles(obstacles, numObstacles);
        drawSquare(&square);
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}