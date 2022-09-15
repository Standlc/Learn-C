#ifndef H_SHIP
#define H_SHIP
#include "cube.h"

typedef struct
{
    Point points[30];
} Ship;

void setUpShip(Ship *ship);
void drawShip(SDL_Renderer *renderer, Ship *ship);

#endif
