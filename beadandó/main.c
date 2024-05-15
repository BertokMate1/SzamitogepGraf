#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window *window = NULL;
SDL_GLContext context;
GLuint obstacleTextureID;

float squareSize = 30.0f;
float squareX = 50.0f;
float squareY = 300.0f;

float whiteSquareSize = 800.0f;
float whiteSquareX = 0.0f;
float whiteSquareY = 330.0f;

int jumping = 0;
int highscore = 0;
Uint32 lastTime = 0;

float ambientLight = 0.2f;
float diffuseLight = 0.8f;

typedef struct {
    float x, y;
    float width, height;
} Obstacle;

Obstacle obstacles[100];
int numObstacles = 0;

void jump() {
    if (!jumping && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]) {
        jumping = 1;
    }

    if (jumping) {
        squareY -= 20.0f;

        if (squareY <= 100.0f) {
            squareY = 100.0f;
            jumping = 0;
        }
    } else {
        if (squareY < 300.0f) {
            squareY += 10.0f;
        }
    }
}

void generateObstacles() {
    Obstacle newObstacle;
    newObstacle.x = SCREEN_WIDTH + rand() % 400;
    newObstacle.y = rand() % (SCREEN_HEIGHT - 100);
    newObstacle.width = 50.0f;
    newObstacle.height = rand() % 100 + 50.0f;

    obstacles[numObstacles++] = newObstacle;
}

void moveObstacles() {
    for (int i = 0; i < numObstacles; i++) {
        obstacles[i].x -= 5.0f;

        if (obstacles[i].x + obstacles[i].width < 0) {
            for (int j = i; j < numObstacles - 1; j++) {
                obstacles[j] = obstacles[j + 1];
            }
            numObstacles--;
            generateObstacles();
        }

        if (obstacles[i].x < squareX + squareSize && obstacles[i].x + obstacles[i].width > squareX &&
            obstacles[i].y < squareY + squareSize && obstacles[i].y + obstacles[i].height > squareY) {
            if (highscore > 0) {
                printf("Highscore: %d\n", highscore);
            } else {
                printf("Highscore: None\n");
            }
            highscore = 0;
            numObstacles = 0;
            for (int k = 0; k < 5; k++) {
                generateObstacles();
            }
            return;
        }
    }

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= 1000) {
        highscore++;
        lastTime = currentTime;
    }
}

void drawObstacles() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, obstacleTextureID);

    for (int i = 0; i < numObstacles; i++) {
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(obstacles[i].x, obstacles[i].y);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(obstacles[i].x + obstacles[i].width, obstacles[i].y);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(obstacles[i].x + obstacles[i].width, obstacles[i].y + obstacles[i].height);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(obstacles[i].x, obstacles[i].y + obstacles[i].height);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

void drawSquare() {
    glColor3f(1.0f, 0.5f, 0.0f); // Narancssárga szín

    glBegin(GL_QUADS);
        glVertex2f(squareX, squareY);
        glVertex2f(squareX + squareSize, squareY);
        glVertex2f(squareX + squareSize, squareY + squareSize);
        glVertex2f(squareX, squareY + squareSize);
    glEnd();
}

void drawWhiteSquare() {
    glColor3f(1.0f, 1.0f, 1.0f); // Fehér szín

    glBegin(GL_QUADS);
        glVertex2f(whiteSquareX, whiteSquareY);
        glVertex2f(whiteSquareX + whiteSquareSize, whiteSquareY);
        glVertex2f(whiteSquareX + whiteSquareSize, whiteSquareY + whiteSquareSize);
        glVertex2f(whiteSquareX, whiteSquareY + whiteSquareSize);
    glEnd();
}

void drawHighscore() {
    char highscoreText[50];
    sprintf(highscoreText, "Highscore: %d", highscore);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(10, 10);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawObstacles();
    drawSquare();
    drawWhiteSquare();
    drawHighscore();

    SDL_GL_SwapWindow(window);
}

void adjustLights(int key) {
    switch (key) {
        case SDLK_o:
            ambientLight += 0.1f;
            if (ambientLight > 1.0f) ambientLight = 1.0f;
            break;
        case SDLK_p:
            ambientLight -= 0.1f;
            if (ambientLight < 0.0f) ambientLight = 0.0f;
            break;
        default:
            break;
    }

    GLfloat ambientColor[] = { ambientLight, ambientLight, ambientLight, 1.0f };
    GLfloat diffuseColor[] = { diffuseLight, diffuseLight, diffuseLight, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
}

void displayHelp() {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Gamblers Run Help", 
    "Gamblers Run\n\nControls:\n"
    "Space: Jump\n"
    "A and D: Move left and right\n"
    "O: Increase Ambient Light\n"
    "P: Decrease Ambient Light\n"
    "F1: Show Help\n"
    "ESC: Quit", window);
}

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

    for (int i = 0; i < 5; i++) {
        generateObstacles();
    }

    // Load and bind texture
    SDL_Surface *surface = SDL_LoadBMP("obstacle.bmp"); // Assuming the texture file is a BMP
    if (!surface) {
        printf("Texture loading error: %s\n", SDL_GetError());
        return -1;
    }
    glGenTextures(1, &obstacleTextureID);
    glBindTexture(GL_TEXTURE_2D, obstacleTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientColor[] = { ambientLight, ambientLight, ambientLight, 1.0f };
    GLfloat diffuseColor[] = { diffuseLight, diffuseLight, diffuseLight, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f }; // Directional light from the front

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (init() < 0) {
        printf("Initialization error\n");
        return -1;
    }

    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_a:
                        squareX -= 20.0f;
                        break;
                    case SDLK_d:
                        squareX += 20.0f;
                        break;
                    case SDLK_F1:
                        displayHelp();
                        break;
                    case SDLK_o:
                    case SDLK_p:
                        adjustLights(e.key.keysym.sym);
                        break;
                    default:
                        break;
                }
            }
        }

        jump();
        moveObstacles();
        render();
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}