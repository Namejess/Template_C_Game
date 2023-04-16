#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#define SDL_ASSERT_LEVEL 2
#define kGameName "SDL2 Game"
#define kGameWidth 800
#define kGameHeight 600

int main(int argc, char const *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Starting SDL2\n");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error\n%s", SDL_GetError());
        return -1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        kGameName,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        kGameWidth,
        kGameHeight,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        printf("SDL_CreateWindow Error\n%s", SDL_GetError());
        return -1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        printf("SDL_CreateRenderer Error\n%s", SDL_GetError());
        return -1;
    }

    // Main Game loop
    while (true)
    {
        // Handle events
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            return 0;
            break;
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
