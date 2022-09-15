#include <stdio.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>

// gcc main.c -F/Library/Frameworks -framework SDL2_image -lSDL2
// gcc main.c -I/Library/Frameworks/SDL2_image.framework/Headers -lSDL2

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("hello world",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          400,
                                          300,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (!window)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, render_flags);

    if (!rend)
    {
        printf("Error creating renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // SDL_Surface *surface = IMG_Load("assets/image.png");
    // if (!surface)
    // {
    //     printf("Error rendering image");
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }

    SDL_Delay(5000);

    SDL_DestroyWindow(window);

    SDL_Quit();
}