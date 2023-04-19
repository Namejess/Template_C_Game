#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#define kGameName "SDL2 Game"
#define kGameWidth 800
#define kGameHeight 600

SDL_Texture *LoadTexture(SDL_Renderer *renderer, char *path)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path);

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s", path, IMG_GetError());
        return NULL;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s", path, SDL_GetError());
            return NULL;
        }
        else
        {
            SDL_FreeSurface(loadedSurface);
            loadedSurface = NULL;
        }

        return texture;
    }
}

SDL_Texture *LoadTexture2(SDL_Renderer *renderer, char *path)
{
    SDL_Texture *texture = NULL;

    texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s", path, SDL_GetError());
        return NULL;
    }

    return texture;
}

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
    else
    {
        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!IMG_Init(imgFlags) & imgFlags)
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            return -1;
        }

        SDL_Texture *texBG = LoadTexture(renderer, "gfx/background.jpg");
        int iTexBG_w, iTexBG_h;
        SDL_QueryTexture(texBG, NULL, NULL, &iTexBG_w, &iTexBG_h);

        SDL_Texture *texPlanet = LoadTexture2(renderer, "gfx/planet.png");
        int iTexPlanet_w, iTexPlanet_h;
        SDL_QueryTexture(texPlanet, NULL, NULL, &iTexPlanet_w, &iTexPlanet_h);
        int x = 0;
        int y = 0;
        int vx = 4;
        int vy = 4;

        int xBG = 0;

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
            // Update
            x += vx;
            y += vy;

            xBG -= 4;

            if (xBG <= -iTexBG_w)
            {
                xBG = 0;
            }

            if (x + iTexPlanet_w > kGameWidth)
            {
                vx = -vx;
                x = kGameWidth - iTexPlanet_w;
            }
            if (x < 0)
            {
                vx = -vx;
                x = 0;
            }

            if (y + iTexPlanet_h > kGameHeight)
            {
                vy = -vy;
                y = kGameHeight - iTexPlanet_h;
            }
            if (y < 0)
            {
                vy = -vy;
                y = 0;
            }

            // Clear the screen
            SDL_RenderClear(renderer);

            // Draw a rectangle white

            SDL_Rect rectBG = {xBG, 0, iTexBG_w, iTexBG_h};
            SDL_RenderCopy(renderer, texBG, NULL, &rectBG);
            SDL_Rect rectBG2 = {xBG + iTexBG_w, 0, iTexBG_w, iTexBG_h};
            SDL_RenderCopy(renderer, texBG, NULL, &rectBG2);

            // Affichage image
            SDL_Rect rect = {x, y, iTexPlanet_w, iTexPlanet_h};
            SDL_RenderCopy(renderer, texPlanet, NULL, &rect);

            // Draw the screen
            SDL_RenderPresent(renderer);
        }

        // Clean up
        SDL_DestroyTexture(texPlanet);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();

        return 0;
    }
}
