#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include <SDL.h>

// void setUpShip(Ship *ship)
// {
//     // TOP
//     ship->points[0].x = -5;
//     ship->points[0].y = -1000 + 20;
//     ship->points[0].z = 1.2;

//     ship->points[1].x = 5;
//     ship->points[1].y = -1000 + 20;
//     ship->points[1].z = 1.2;

//     ship->points[2].x = 10;
//     ship->points[2].y = -1000 + 30;
//     ship->points[2].z = 1.15;

//     ship->points[3].x = 10;
//     ship->points[3].y = -1000 + 30;
//     ship->points[3].z = 1.1;

//     ship->points[4].x = 80;
//     ship->points[4].y = -1000 + 40;
//     ship->points[4].z = 1.09;

//     ship->points[5].x = 80;
//     ship->points[5].y = -1000 + 40;
//     ship->points[5].z = 1.08;

//     ship->points[6].x = 10;
//     ship->points[6].y = -1000 + 30;
//     ship->points[6].z = 1.08;

//     ship->points[7].x = -10;
//     ship->points[7].y = -1000 + 30;
//     ship->points[7].z = 1.08;

//     ship->points[8].x = -80;
//     ship->points[8].y = -1000 + 40;
//     ship->points[8].z = 1.08;

//     ship->points[9].x = -80;
//     ship->points[9].y = -1000 + 40;
//     ship->points[9].z = 1.09;

//     ship->points[10].x = -10;
//     ship->points[10].y = -1000 + 30;
//     ship->points[10].z = 1.1;

//     ship->points[11].x = -10;
//     ship->points[11].y = -1000 + 30;
//     ship->points[11].z = 1.15;

//     ship->points[12].x = -5;
//     ship->points[12].y = -1000 + 20;
//     ship->points[12].z = 1.2;

//     // BOTTOM
//     ship->points[13].x = -5;
//     ship->points[13].y = -1000 + 20;
//     ship->points[13].z = 1.2;

//     ship->points[14].x = 5;
//     ship->points[14].y = -1000 + 20;
//     ship->points[14].z = 1.2;

//     ship->points[15].x = 10;
//     ship->points[15].y = -1000 + 10;
//     ship->points[15].z = 1.15;

//     ship->points[16].x = 10;
//     ship->points[16].y = -1000 + 10;
//     ship->points[16].z = 1.1;

//     ship->points[17].x = 80;
//     ship->points[17].y = -1000 - 0;
//     ship->points[17].z = 1.09;

//     ship->points[18].x = 80;
//     ship->points[18].y = -1000 - 0;
//     ship->points[18].z = 1.08;

//     ship->points[19].x = 10;
//     ship->points[19].y = -1000 + 10;
//     ship->points[19].z = 1.08;

//     ship->points[20].x = -10;
//     ship->points[20].y = -1000 + 10;
//     ship->points[20].z = 1.08;

//     ship->points[21].x = -80;
//     ship->points[21].y = -1000 - 0;
//     ship->points[21].z = 1.08;

//     ship->points[22].x = -80;
//     ship->points[22].y = -1000 - 0;
//     ship->points[22].z = 1.09;

//     ship->points[23].x = -10;
//     ship->points[23].y = -1000 + 10;
//     ship->points[23].z = 1.1;

//     ship->points[24].x = -10;
//     ship->points[24].y = -1000 + 10;
//     ship->points[24].z = 1.15;

//     ship->points[25].x = -5;
//     ship->points[25].y = -1000 + 20;
//     ship->points[25].z = 1.2;
// }

void setUpShip(Ship *ship)
{
    // TOP
    ship->points[0].x = -3;
    ship->points[0].y = -1000 + 20;
    ship->points[0].z = 1.2;

    ship->points[1].x = 3;
    ship->points[1].y = -1000 + 20;
    ship->points[1].z = 1.2;

    ship->points[2].x = 20;
    ship->points[2].y = -1000 + 30;
    ship->points[2].z = 1.1;

    ship->points[3].x = 100;
    ship->points[3].y = -1000 + 40;
    ship->points[3].z = 1.09;

    ship->points[4].x = 100;
    ship->points[4].y = -1000 + 40;
    ship->points[4].z = 1.08;

    ship->points[5].x = 20;
    ship->points[5].y = -1000 + 30;
    ship->points[5].z = 1.08;

    ship->points[6].x = -20;
    ship->points[6].y = -1000 + 30;
    ship->points[6].z = 1.08;

    ship->points[7].x = -100;
    ship->points[7].y = -1000 + 40;
    ship->points[7].z = 1.08;

    ship->points[8].x = -100;
    ship->points[8].y = -1000 + 40;
    ship->points[8].z = 1.09;

    ship->points[9].x = -20;
    ship->points[9].y = -1000 + 30;
    ship->points[9].z = 1.1;

    ship->points[10].x = -3;
    ship->points[10].y = -1000 + 20;
    ship->points[10].z = 1.2;

    // BOTTOM
    ship->points[11].x = -3;
    ship->points[11].y = -1000 + 20;
    ship->points[11].z = 1.2;

    ship->points[12].x = 3;
    ship->points[12].y = -1000 + 20;
    ship->points[12].z = 1.2;

    ship->points[13].x = 20;
    ship->points[13].y = -1000 + 10;
    ship->points[13].z = 1.1;

    ship->points[14].x = 100;
    ship->points[14].y = -1000 - 0;
    ship->points[14].z = 1.09;

    ship->points[15].x = 100;
    ship->points[15].y = -1000 - 0;
    ship->points[15].z = 1.08;

    ship->points[16].x = 20;
    ship->points[16].y = -1000 + 10;
    ship->points[16].z = 1.08;

    ship->points[17].x = -20;
    ship->points[17].y = -1000 + 10;
    ship->points[17].z = 1.08;

    ship->points[18].x = -100;
    ship->points[18].y = -1000 - 0;
    ship->points[18].z = 1.08;

    ship->points[19].x = -100;
    ship->points[19].y = -1000 - 0;
    ship->points[19].z = 1.09;

    ship->points[20].x = -20;
    ship->points[20].y = -1000 + 10;
    ship->points[20].z = 1.1;

    ship->points[21].x = -3;
    ship->points[21].y = -1000 + 20;
    ship->points[21].z = 1.2;
}

void drawShip(SDL_Renderer *renderer, Ship *ship)
{
    SDL_SetRenderDrawColor(renderer, 218, 112, 214, 0);
    for (int i = 0; i < 22 - 1; i++)
        SDL_RenderDrawLine(renderer,
                           x(ship->points[i].x, ship->points[i].z),
                           y(ship->points[i].y, ship->points[i].z),
                           x(ship->points[i + 1].x, ship->points[i + 1].z),
                           y(ship->points[i + 1].y, ship->points[i + 1].z));
}