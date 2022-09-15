#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

// Utility macros
#define CHECK_ERROR(test, message)              \
    do                                          \
    {                                           \
        if ((test))                             \
        {                                       \
            fprintf(stderr, "%s\n", (message)); \
            exit(1);                            \
        }                                       \
    } while (0)

int randInt(int rmin, int rmax)
{
    return rand() % rmax + rmin;
}

static const int WIDTH = 800;
static const int HEIGHT = 800;
static const int FPS = 30;
static const int MAX_LASER_COUNT = 20;
static const int ALIEN_WIDTH = 35;

typedef struct
{
    double x;
    double y;
} Velocity;

typedef struct
{
    int space;
    int left;
    int right;
} Keys;

typedef struct
{
    SDL_Rect *rect;
    bool alive;
} Alien;

typedef struct
{
    SDL_Rect *rect;
    int health;
} Shield;

int shipShape(int x, SDL_Rect *ship)
{
    float coeff = (ship->h / 2.0) / (ship->w / 2.0);
    float offset = ship->h / 2.0;
    float height;

    if (x - ship->x <= (ship->w / 2.0))
        height = (x - ship->x) * coeff + offset;
    else
        height = (x - ship->x - ship->w / 2.0) * -coeff + ship->h;

    return ship->y + (ship->h - height);
}

void controls(SDL_Rect *rect, const char *key, Velocity *velocity)
{
    if (!strcmp(key, "Left"))
        rect->x -= velocity->x;
    if (!strcmp(key, "Right"))
        rect->x += velocity->x;
}

SDL_Texture *createTexture(SDL_Renderer *renderer, char img[30])
{
    SDL_Surface *surface = IMG_Load(img);
    CHECK_ERROR(!surface, SDL_GetError());

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    CHECK_ERROR(!texture, SDL_GetError());

    return texture;
}

SDL_Rect loadImage(SDL_Texture *texture, int h, int w)
{
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.h = h;
    rect.w = w;

    return rect;
}

void handleShipMovement(SDL_Rect *ship, Keys *keys, Velocity *shipVelocity)
{
    if (keys->left)
        ship->x -= shipVelocity->x;
    if (keys->right)
        ship->x += shipVelocity->x;
}

void shoot(SDL_Texture *laserTexture, int *lasersCount, SDL_Rect *lasers[20], SDL_Rect *ship)
{
    SDL_Rect *laser = NULL;
    laser = (SDL_Rect *)malloc(sizeof(laser));

    if (!laser)
        exit(0);

    *laser = loadImage(laserTexture, 20, 5);
    lasers[*lasersCount] = laser;
    laser->x = ship->x + (ship->w / 2) - laser->w / 2;
    laser->y = HEIGHT - 60 - laser->h;
    (*lasersCount)++;
}

void initialiseAliens(int *alienCount, SDL_Texture *alienTexture, Alien aliens[40], int size)
{
    int ROWS = 4;
    int ALIEN_PER_ROW = (size / ROWS);
    int ALIEN_GROUP_WIDTH = WIDTH * 0.8;
    int spaceBetween = (ALIEN_GROUP_WIDTH - ALIEN_PER_ROW * ALIEN_WIDTH) / (ALIEN_PER_ROW - 1);
    int offset = (WIDTH - ALIEN_GROUP_WIDTH) / 2;

    *alienCount = size;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < (size) / 4; j++)
        {
            SDL_Rect *alien = NULL;
            alien = (SDL_Rect *)malloc(sizeof(alien));
            if (!alien)
                exit(0);

            *alien = loadImage(alienTexture, 30, ALIEN_WIDTH);
            alien->x = j * (ALIEN_WIDTH + spaceBetween) + offset;
            alien->y = i * 60 - 240;
            aliens[i * (size / 4) + j].rect = alien;
            aliens[i * (size / 4) + j].alive = true;
        }
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());

    SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    CHECK_ERROR(!window, SDL_GetError());

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    CHECK_ERROR(!renderer, SDL_GetError());

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_Texture *shipTexture = createTexture(renderer, "assets/ship.png");
    SDL_Texture *alienTexture = createTexture(renderer, "assets/alien.png");
    SDL_Texture *laserTexture = createTexture(renderer, "assets/laser.png");
    SDL_Texture *starTexture = createTexture(renderer, "assets/star.png");
    SDL_Texture *alienLaserTexture = createTexture(renderer, "assets/alienLaser.png");
    SDL_Texture *shieldTexture = createTexture(renderer, "assets/laser.png");

    SDL_Rect ship = loadImage(shipTexture, 90, 80);
    ship.x = (WIDTH - ship.w) / 2;
    ship.y = HEIGHT - 20 - ship.h;

    SDL_Rect *lasers[20];
    int lasersCount = 0;

    SDL_Rect *alienLasers[10];
    int alienLasersCount = 0;

    Alien aliens[36];
    int alienCount = 36;
    initialiseAliens(&alienCount, alienTexture, aliens, sizeof(aliens) / sizeof(aliens[0]));

    Velocity shipVelocity = {15, 10};
    Velocity laserVelocity = {0, 20};
    Velocity alienVelocity = {1, 1};

    Keys keys = {0, 0, 0};

    SDL_Rect *stars[100];
    for (int i = 0; i < sizeof(stars) / sizeof(stars[0]); i++)
    {
        SDL_Rect *star = NULL;
        star = (SDL_Rect *)malloc(sizeof(star));
        if (!star)
            exit(0);
        int size = randInt(1, 2);

        *star = loadImage(starTexture, size, size);
        star->x = randInt(0, WIDTH);
        star->y = randInt(0, HEIGHT);
        stars[i] = star;
    }

    Shield shields[2];
    int shieldsCount = 2;
    for (int i = 0; i < shieldsCount; i++)
    {
        SDL_Rect *shield = NULL;
        shield = (SDL_Rect *)malloc(sizeof(*shield));
        if (!shield)
            exit(0);

        *shield = loadImage(shieldTexture, 20, 150);
        shield->x = i * (500 - shield->w) + 150;
        shield->y = HEIGHT - 150 - shield->h;
        shields[i].rect = shield;
        shields[i].health = 20;
    }

    int index = 0;
    int shotIndex = 0;
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
                if (!keys.left)
                    keys.left = !strcmp(key, "Left");
                if (!keys.right)
                    keys.right = !strcmp(key, "Right");
                if (!keys.space)
                    keys.space = !strcmp(key, "Space");
                if (!strcmp(key, "Return"))
                    initialiseAliens(&alienCount, alienTexture, aliens, sizeof(aliens) / sizeof(aliens[0]));
            }

            if (event.type == SDL_KEYUP)
            {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                if (!strcmp(key, "Left"))
                    keys.left = 0;
                if (!strcmp(key, "Right"))
                    keys.right = 0;
                if (!strcmp(key, "Space"))
                    keys.space = 0;
            }
        }

        if (aliens[0].rect->x <= 0 || aliens[(sizeof(aliens) / sizeof(aliens[0])) - 1].rect->x + aliens[0].rect->w >= WIDTH)
            alienVelocity.x = -alienVelocity.x;

        if (keys.space && lasersCount < MAX_LASER_COUNT)
        {
            if (index - shotIndex >= 7)
            {
                shotIndex = index;
                shoot(laserTexture, &lasersCount, lasers, &ship);
            }
        }

        handleShipMovement(&ship, &keys, &shipVelocity);

        SDL_RenderClear(renderer);

        for (int i = 0; i < sizeof(stars) / sizeof(stars[0]); i++)
        {
            if (stars[i]->y >= HEIGHT)
            {
                int size = randInt(1, 2);
                stars[i]->y = 0 - size;
                stars[i]->x = randInt(0, WIDTH);
                stars[i]->w = size;
                stars[i]->h = size;
            }

            stars[i]->y += 4;

            SDL_RenderCopy(renderer, starTexture, NULL, stars[i]);
        }

        for (int i = 0; i < shieldsCount; i++)
        {
            if (shields[i].health)
                SDL_RenderCopy(renderer, shieldTexture, NULL, shields[i].rect);
        }

        for (int i = 0; i < alienLasersCount; i++)
        {
            alienLasers[i]->y += laserVelocity.y;

            if (alienLasers[i]->y >= HEIGHT)
            {
                free(alienLasers[i]);
                for (int j = i; j < alienLasersCount - 1; j++)
                    alienLasers[j] = alienLasers[j + 1];
                alienLasersCount--;
            }
            if (alienLasers[i]->y + alienLasers[i]->h >= shipShape(alienLasers[i]->x, &ship) && alienLasers[i]->x + alienLasers[i]->w >= ship.x && alienLasers[i]->x <= ship.x + ship.w)
            {
                free(alienLasers[i]);
                for (int j = i; j < alienLasersCount - 1; j++)
                    alienLasers[j] = alienLasers[j + 1];
                alienLasersCount--;
                initialiseAliens(&alienCount, alienTexture, aliens, sizeof(aliens) / sizeof(aliens[0]));
            }

            for (int j = 0; j < shieldsCount; j++)
                if (alienLasers[i]->y + alienLasers[i]->h >= shields[j].rect->y && alienLasers[i]->x + alienLasers[i]->w >= shields[j].rect->x && alienLasers[i]->x <= shields[j].rect->x + shields[j].rect->w)
                {
                    shields[j].health--;

                    if (!shields[j].health)
                    {
                        free(shields[j].rect);
                        for (int k = i; k < shieldsCount - 1; k++)
                            shields[k] = shields[k + 1];
                        shieldsCount--;
                    }

                    free(alienLasers[i]);
                    for (int j = i; j < alienLasersCount - 1; j++)
                        alienLasers[j] = alienLasers[j + 1];
                    alienLasersCount--;
                }

            SDL_RenderCopy(renderer, alienLaserTexture, NULL, alienLasers[i]);
        }

        for (int i = 0; i < sizeof(aliens) / sizeof(aliens[0]); i++)
        {

            aliens[i].rect->x += alienVelocity.x;
            aliens[i].rect->y += alienVelocity.y;

            for (int j = 0; j < lasersCount; j++)
            {
                if (aliens[i].alive && (lasers[j]->x <= aliens[i].rect->x + aliens[i].rect->w) && (lasers[j]->x + lasers[j]->w >= aliens[i].rect->x) && (lasers[j]->y <= aliens[i].rect->y + aliens[i].rect->h) && (lasers[j]->y + lasers[j]->h) >= aliens[i].rect->y)
                {
                    aliens[i].alive = false;
                    alienCount--;

                    free(lasers[j]);
                    for (int k = j; k < lasersCount - 1; k++)
                        lasers[k] = lasers[k + 1];
                    lasersCount--;

                    j = lasersCount;
                }
            }

            if (aliens[i].alive)
            {
                SDL_RenderCopy(renderer, alienTexture, NULL, aliens[i].rect);

                if (!randInt(0, alienCount * 20) && alienLasersCount < 10)
                {
                    SDL_Rect *alienLaser = NULL;
                    alienLaser = (SDL_Rect *)malloc(sizeof(alienLaser));
                    if (!alienLaser)
                        exit(0);

                    *alienLaser = loadImage(alienLaserTexture, 20, 5);
                    alienLaser->x = aliens[i].rect->x + aliens[i].rect->w / 2;
                    alienLaser->y = aliens[i].rect->y;
                    alienLasers[alienLasersCount] = alienLaser;

                    alienLasersCount++;
                }
            }
        }

        for (int i = 0; i < lasersCount; i++)
        {
            lasers[i]->y -= laserVelocity.y;
            if (lasers[i]->y + lasers[i]->h <= 0)
            {
                free(lasers[i]);
                for (int j = i; j < lasersCount - 1; j++)
                    lasers[j] = lasers[j + 1];
                lasersCount--;
            }

            SDL_RenderCopy(renderer, laserTexture, NULL, lasers[i]);
        }

        SDL_RenderCopy(renderer, shipTexture, NULL, &ship);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        index++;
    }

    for (int i = 0; i < lasersCount; i++)
        free(lasers[i]);

    for (int i = 0; i < sizeof(aliens) / sizeof(aliens[0]); i++)
        free(aliens[i].rect);

    for (int i = 0; i < sizeof(shields) / sizeof(shields[0]); i++)
        free(shields[i].rect);

    for (int i = 0; i < sizeof(stars) / sizeof(stars[0]); i++)
        free(stars[i]);

    SDL_DestroyTexture(alienTexture);
    SDL_DestroyTexture(shipTexture);
    SDL_DestroyTexture(laserTexture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}