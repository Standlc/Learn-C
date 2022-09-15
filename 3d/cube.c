#include <SDL2/SDL.h>
#include "cube.h"

static const int HEIGHT = 800;
static const int WIDTH = 800;

int y(int x, double y)
{
    if (y > 0)
        return -x / y - 200;
    else
        return 0;
}

int x(int x, double y)
{
    if (y > 0)
        return (x / y) + WIDTH / 2;
    else
        return 0;
}

void draw(SDL_Renderer *renderer, Cube *cube)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
            SDL_RenderDrawLine(renderer,
                               x(cube->points[j + i * 4].x, cube->points[j + i * 4].z),
                               y(cube->points[j + i * 4].y, cube->points[j + i * 4].z),
                               x(cube->points[j == 3 ? j + i * 4 - 3 : j + i * 4 + 1].x, cube->points[j == 3 ? j + i * 4 - 3 : j + 1 + i * 4].z),
                               y(cube->points[j == 3 ? j + i * 4 - 3 : j + i * 4 + 1].y, cube->points[j == 3 ? j + i * 4 - 3 : j + i * 4 + 1].z));
    }

    for (int i = 0; i < 4; i++)
        SDL_RenderDrawLine(renderer,
                           x(cube->points[i].x, cube->points[i].z),
                           y(cube->points[i].y, cube->points[i].z),
                           x(cube->points[i + 4].x, cube->points[i + 4].z),
                           y(cube->points[i + 4].y, cube->points[i + 4].z));
}

void setCubePos(Cube *cube, Dimensions *dimensions, Point *origins)
{
    // FRONT
    cube->points[0].x = origins->x;
    cube->points[0].y = origins->y;
    cube->points[0].z = origins->z;

    cube->points[1].x = origins->x + dimensions->width;
    cube->points[1].y = origins->y;
    cube->points[1].z = origins->z;

    cube->points[2].x = origins->x + dimensions->width;
    cube->points[2].y = origins->y + dimensions->height;
    cube->points[2].z = origins->z;

    cube->points[3].x = origins->x;
    cube->points[3].y = origins->y + dimensions->height;
    cube->points[3].z = origins->z;

    // BACK
    cube->points[4].x = origins->x;
    cube->points[4].y = origins->y;
    cube->points[4].z = origins->z + dimensions->depth;

    cube->points[5].x = origins->x + dimensions->width;
    cube->points[5].y = origins->y;
    cube->points[5].z = origins->z + dimensions->depth;

    cube->points[6].x = origins->x + dimensions->width;
    cube->points[6].y = origins->y + dimensions->height;
    cube->points[6].z = origins->z + dimensions->depth;

    cube->points[7].x = origins->x;
    cube->points[7].y = origins->y + dimensions->height;
    cube->points[7].z = origins->z + dimensions->depth;
}