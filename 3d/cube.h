#ifndef H_CUBE
#define H_CUBE
#include <SDL.h>
#include <stdbool.h>

typedef struct
{
    int x;
    int y;
    double z;
} Point;

typedef struct
{
    Point points[8];
} Cube;

typedef struct
{
    int height;
    int width;
    double depth;
} Dimensions;

typedef struct
{
    Point a;
    Point b;
} Line;

typedef struct
{
    bool alive;
    Cube cube;
} Obstacle;



int y(int x, double y);
int x(int x, double y);
void draw(SDL_Renderer *renderer, Cube *cube);
void setCubePos(Cube *cube, Dimensions *dimensions, Point *origins);

#endif