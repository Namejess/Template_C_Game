#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "include/shoot.h"

typedef float f32;
typedef double f64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef size_t usize;
typedef ssize_t isize;

#define PI 3.14159265359f
#define TAU (2.0f * PI)
#define PI_2 (PI / 2.0f)
#define PI_4 (PI / 4.0f)
#define kGameName "SDL2 Game"
#define kGameWidth 1000
#define kGameHeight 600

static Shoot shoot;
static Uint32 last_shoot_time = 0;
#define SHOOT_DELAY 200

typedef struct
{
    int x;
    int y;
    int vx;
    int vy;
    SDL_Texture *texture;
} Projectile;

#define MAX_PROJECTILES 1024
static Projectile projectiles[MAX_PROJECTILES];
static int num_projectiles = 0;

void add_projectile(int x, int y, int vx, int vy, SDL_Texture *texture)
{
    if (num_projectiles < MAX_PROJECTILES)
    {
        projectiles[num_projectiles].x = x;
        projectiles[num_projectiles].y = y;
        projectiles[num_projectiles].vx = vx;
        projectiles[num_projectiles].vy = vy;
        projectiles[num_projectiles].texture = texture;
        ++num_projectiles;
    }
}

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

SDL_Texture *LoadTexture3(SDL_Renderer *renderer, char *path)
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

SDL_Texture *LoadTexture4(SDL_Renderer *renderer, char *path)
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

        /**
         Charge les textures
         */
        SDL_Texture *texBG = LoadTexture(renderer, "gfx/background.jpg");
        int iTexBG_w, iTexBG_h;
        SDL_QueryTexture(texBG, NULL, NULL, &iTexBG_w, &iTexBG_h);

        SDL_Texture *texPlanet = LoadTexture2(renderer, "gfx/ship.png");
        int iTexPlanet_w, iTexPlanet_h;
        SDL_QueryTexture(texPlanet, NULL, NULL, &iTexPlanet_w, &iTexPlanet_h);

        SDL_Texture *texBG2 = LoadTexture3(renderer, "gfx/background_stars.png");
        int iTexBG2_w, iTexBG2_h;
        SDL_QueryTexture(texBG2, NULL, NULL, &iTexBG2_w, &iTexBG2_h);

        SDL_Texture *texShoot = LoadTexture4(renderer, "gfx/fireball.png");
        int iTexShoot_w, iTexShoot_h;
        SDL_QueryTexture(texShoot, NULL, NULL, &iTexShoot_w, &iTexShoot_h);

        int x = 0;
        int y = 0;
        int vx = 4;
        int vy = 4;

        i8 xShoot = 0;
        i8 yShoot = 0;
        i8 vxShoot = 4;
        i8 vyShoot = 4;

        int xBG = 0;
        int xBG2 = 0;

        shoot_init(renderer);

        bool isShooting = false;

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

            xBG -= 4;
            xBG2 -= 30;

            if (xBG2 <= -iTexBG2_w)
            {
                xBG2 = 0;
            }

            if (xBG <= -iTexBG_w)
            {
                xBG = 0;
            }

            // Add direction to the planet ZQSD
            const u8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_UP])
            {
                y -= 5;
            }

            if (state[SDL_SCANCODE_DOWN])
            {
                y += 5;
            }

            if (state[SDL_SCANCODE_LEFT])
            {
                x -= 5;
            }

            if (state[SDL_SCANCODE_RIGHT])
            {
                x += 5;
            }

            if (state[SDL_SCANCODE_SPACE])
            {
                Uint32 current_time = SDL_GetTicks();
                if (current_time - last_shoot_time >= SHOOT_DELAY)
                {
                    add_projectile(x + iTexPlanet_w - 25, y + iTexPlanet_h / 2 - 25, 10, 0, texShoot);
                    last_shoot_time = current_time;
                }
            }

            // Clear the screen
            SDL_RenderClear(renderer);

            // Draw a rectangle white
            SDL_Rect rectBG = {xBG, 0, iTexBG_w, iTexBG_h};
            SDL_RenderCopy(renderer, texBG, NULL, &rectBG);
            SDL_Rect rectBG2 = {xBG + iTexBG_w, 0, iTexBG_w, iTexBG_h};
            SDL_RenderCopy(renderer, texBG, NULL, &rectBG2);
            SDL_Rect rectBG2Stars = {xBG2, 0, iTexBG2_w, iTexBG2_h};
            SDL_RenderCopy(renderer, texBG2, NULL, &rectBG2Stars);
            SDL_Rect rectBG2Stars2 = {xBG2 + iTexBG2_w, 0, iTexBG2_w, iTexBG2_h};
            SDL_RenderCopy(renderer, texBG2, NULL, &rectBG2Stars2);

            // Affichage image
            SDL_Rect rect = {x, y, iTexPlanet_w, iTexPlanet_h};
            SDL_RenderCopy(renderer, texPlanet, NULL, &rect);

            // Update projectiles
            for (int i = 0; i < num_projectiles; ++i)
            {
                projectiles[i].x += projectiles[i].vx;
                projectiles[i].y += projectiles[i].vy;
            }

            // Draw projectiles
            for (int i = 0; i < num_projectiles; ++i)
            {
                SDL_Rect rectShoot = {projectiles[i].x, projectiles[i].y, iTexShoot_w, iTexShoot_h};
                SDL_RenderCopy(renderer, projectiles[i].texture, NULL, &rectShoot);
            }

            // Draw the screen
            SDL_RenderPresent(renderer);
        }

        // Clean up
        SDL_DestroyTexture(texPlanet);
        SDL_DestroyTexture(texBG);
        SDL_DestroyTexture(texBG2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();

        return 0;
    }
}
