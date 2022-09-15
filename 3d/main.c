#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include "cube.h"
#include "ship.h"

#define CHECK_ERROR(test, message)              \
    do                                          \
    {                                           \
        if ((test))                             \
        {                                       \
            fprintf(stderr, "%s\n", (message)); \
            exit(1);                            \
        }                                       \
    } while (0)

static const int HEIGHT = 800;
static const int WIDTH = 800;

int main()
{
    srand(time(NULL));

    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
    SDL_Window *window = SDL_CreateWindow("3d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    CHECK_ERROR(!window, SDL_GetError());
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    CHECK_ERROR(!renderer, SDL_GetError());

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    const int FLOOR_LEVEL = -1000;
    const int DEPTH = 5;

    Cube player;
    Point origins = {-100 / 2, FLOOR_LEVEL, 1.1};
    Dimensions dimensions = {30, 100, 0.1};
    setCubePos(&player, &dimensions, &origins);

    Ship ship;
    setUpShip(&ship);

    Obstacle obstacles[6];
    Dimensions obstacleDimensions = {100, 100, 0.1};
    for (int i = 0; i < sizeof(obstacles) / sizeof(obstacles[0]); i++)
    {
        Point obstacleOrigins = {rand() % (800 - obstacleDimensions.width) - 400, FLOOR_LEVEL, i * ((DEPTH - 0.8) / 6.0) + 5};
        // printf("%f\n", obstacleOrigins.z);
        obstacles[i].alive = true;
        setCubePos(&obstacles[i].cube, &obstacleDimensions, &obstacleOrigins);
    }

    int left = 0;
    int right = 0;
    int space = 0;

    int displacement = 0;
    int displacementVelocity = 10;
    int playerVelocity = 10;

    float obstaclesVelocity = 0.012;

    Line floorGrid[20];
    for (int i = 0; i < sizeof(floorGrid) / sizeof(floorGrid[0]); i++)
    {
        floorGrid[i].a.x = -400;
        floorGrid[i].a.y = FLOOR_LEVEL;
        floorGrid[i].a.z = i * ((DEPTH - 1) / 20.0) + 1;

        floorGrid[i].b.x = 400;
        floorGrid[i].b.y = FLOOR_LEVEL;
        floorGrid[i].b.z = i * ((DEPTH - 1) / 20.0) + 1;
        // printf("%f\n", floorGrid[i].b.z);
    }

    Line lasers[10];
    int laserCount = 0;

    int gameIndex = 0;
    int shootingIndex = 0;

    bool running = true;
    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN)
            {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                if (!left)
                    left = !strcmp(key, "Left");
                if (!right)
                    right = !strcmp(key, "Right");
                if (!space)
                    space = !strcmp(key, "Space");
            }

            if (event.type == SDL_KEYUP)
            {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                if (!strcmp(key, "Left"))
                    left = 0;
                if (!strcmp(key, "Right"))
                    right = 0;
                if (!strcmp(key, "Space"))
                    space = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        if (right)
            displacement -= displacementVelocity;
        if (left)
            displacement += displacementVelocity;
        if (space && laserCount < sizeof(lasers) / sizeof(lasers[0]) && gameIndex - shootingIndex >= 20)
        {
            shootingIndex = gameIndex;

            Line laser;

            laser.a.x = ship.points[0].x + 3;
            laser.a.y = FLOOR_LEVEL + 15;
            laser.a.z = 1.2;

            laser.b.x = ship.points[0].x + 3;
            laser.b.y = FLOOR_LEVEL + 15;
            laser.b.z = 1.3;

            lasers[laserCount] = laser;
            laserCount++;
        }

        SDL_SetRenderDrawColor(renderer, 100, 50, 150, 0);
        SDL_RenderDrawLine(renderer,
                           x(-400 + displacement, 1),
                           y(FLOOR_LEVEL, 1),
                           x(-400 + displacement, 5),
                           y(FLOOR_LEVEL, 5));
        SDL_RenderDrawLine(renderer,
                           x(-200 + displacement, 1),
                           y(FLOOR_LEVEL, 1),
                           x(-200 + displacement, 5),
                           y(FLOOR_LEVEL, 5));
        SDL_RenderDrawLine(renderer,
                           x(0 + displacement, 1),
                           y(FLOOR_LEVEL, 1),
                           x(0 + displacement, 5),
                           y(FLOOR_LEVEL, 5));
        SDL_RenderDrawLine(renderer,
                           x(200 + displacement, 1),
                           y(FLOOR_LEVEL, 1),
                           x(200 + displacement, 5),
                           y(FLOOR_LEVEL, 5));
        SDL_RenderDrawLine(renderer,
                           x(400 + displacement, 1),
                           y(FLOOR_LEVEL, 1),
                           x(400 + displacement, 5),
                           y(FLOOR_LEVEL, 5));

        for (int i = 0; i < sizeof(floorGrid) / sizeof(floorGrid[0]); i++)
        {
            SDL_RenderDrawLine(renderer,
                               x(floorGrid[i].a.x, floorGrid[i].a.z),
                               y(floorGrid[i].a.y, floorGrid[i].a.z),
                               x(floorGrid[i].b.x, floorGrid[i].b.z),
                               y(floorGrid[i].b.y, floorGrid[i].b.z));

            // floorGrid[i].a.z -= obstaclesVelocity;
            // floorGrid[i].b.z -= obstaclesVelocity;

            if (left)
            {
                floorGrid[i].a.x += displacementVelocity;
                floorGrid[i].b.x += displacementVelocity;
            }
            if (right)
            {
                floorGrid[i].a.x -= displacementVelocity;
                floorGrid[i].b.x -= displacementVelocity;
            }

            if (floorGrid[i].a.z <= 1)
            {
                floorGrid[i].a.z = 5;
                floorGrid[i].b.z = 5;
            }
        }

        // LASERS
        for (int i = 0; i < laserCount; i++)
        {
            SDL_SetRenderDrawColor(renderer, 50, 150, 230, 0);
            SDL_RenderDrawLine(renderer,
                               x(lasers[i].a.x - 1, lasers[i].a.z),
                               y(lasers[i].a.y, lasers[i].a.z),
                               x(lasers[i].b.x - 1, lasers[i].b.z),
                               y(lasers[i].b.y, lasers[i].b.z));
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderDrawLine(renderer,
                               x(lasers[i].a.x, lasers[i].a.z),
                               y(lasers[i].a.y, lasers[i].a.z),
                               x(lasers[i].b.x, lasers[i].b.z),
                               y(lasers[i].b.y, lasers[i].b.z));
            SDL_SetRenderDrawColor(renderer, 50, 150, 230, 0);
            SDL_RenderDrawLine(renderer,
                               x(lasers[i].a.x + 1, lasers[i].a.z),
                               y(lasers[i].a.y, lasers[i].a.z),
                               x(lasers[i].b.x + 1, lasers[i].b.z),
                               y(lasers[i].b.y, lasers[i].b.z));

            lasers[i].a.z += 0.04;
            lasers[i].b.z += 0.04;

            if (left)
            {
                lasers[i].a.x += displacementVelocity;
                lasers[i].b.x += displacementVelocity;
            }
            if (right)
            {
                lasers[i].a.x -= displacementVelocity;
                lasers[i].b.x -= displacementVelocity;
            }

            if (lasers[i].a.z >= 5)
            {
                for (int j = i; j < laserCount - 1; j++)
                    lasers[j] = lasers[j + 1];
                laserCount--;
            }

            for (int j = 0; j < sizeof(obstacles) / sizeof(obstacles[0]); j++)
            {
                if (obstacles[j].alive && lasers[i].b.z >= obstacles[j].cube.points->z && lasers[i].a.z <= obstacles[j].cube.points[4].z && lasers[i].b.x >= obstacles[j].cube.points->x && lasers[i].b.x <= obstacles[j].cube.points[1].x)
                {
                    obstacles[j].alive = false;
                    for (int k = i; k < laserCount - 1; k++)
                        lasers[k] = lasers[k + 1];
                    laserCount--;
                }
            }
        }

        // PLAYER
        drawShip(renderer, &ship);
        if (left)
            for (int i = 0; i < 22; i++)
                ship.points[i].x -= playerVelocity;
        if (right)
            for (int i = 0; i < 22; i++)
                ship.points[i].x += playerVelocity;

        // SDL_SetRenderDrawColor(renderer, 218, 112, 214, 0);
        // draw(renderer, &player);
        // // if (left)
        // // {
        // //     for (int i = 0; i < 8; i++)
        // //         player.points[i].x -= playerVelocity;
        // // }
        // // if (right)
        // // {
        // //     for (int i = 0; i < 8; i++)
        // //         player.points[i].x += playerVelocity;
        // // }

        // OBSTACLES
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        for (int i = 0; i < sizeof(obstacles) / sizeof(obstacles[0]); i++)
        {
            if (obstacles[i].alive)
                draw(renderer, &obstacles[i].cube);

            bool obstaclePassedScreen = obstacles[i].cube.points[5].z <= 0.8;
            if (obstaclePassedScreen)
            {
                Point obstacleOrigins = {(rand() % (800 - obstacleDimensions.width) - 400) + displacement, FLOOR_LEVEL, DEPTH};
                setCubePos(&obstacles[i].cube, &obstacleDimensions, &obstacleOrigins);
                obstacles[i].alive = true;
            }

            if (left)
                for (int j = 0; j < 8; j++)
                    obstacles[i].cube.points[j].x += displacementVelocity;
            if (right)
                for (int j = 0; j < 8; j++)
                    obstacles[i].cube.points[j].x -= displacementVelocity;

            for (int j = 0; j < 8; j++)
                obstacles[i].cube.points[j].z -= obstaclesVelocity;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
        gameIndex++;
        if (obstaclesVelocity <= 0.025)
            obstaclesVelocity += 0.000003;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
