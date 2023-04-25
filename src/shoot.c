#include "shoot.h"
#include <SDL2/SDL.h>

#define MAX_SHOOTS 10
static SDL_Texture *shoot_texture;
static SDL_Rect shoot_srcRect;
static SDL_Rect shoot_dstRect;
static Shoot shoot;
static int vxShoot = 10;
static Shoot shoots[MAX_SHOOTS];
static int num_shoots = 0;

void shoot_init(SDL_Renderer *renderer)
{
    // Chargement de la texture du shoot
    SDL_Texture *shoot_texture = LoadTexture(renderer, "gfx/fireball.png");
    num_shoots = 0;
    if (!shoot_texture)
    {
        SDL_Log("Erreur de chargement de la texture : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialisation du rectangle source du shoot
    shoot.x = shoot.y = -100;
    SDL_QueryTexture(shoot_texture, NULL, NULL, &shoot.w, &shoot.h);
    shoot_srcRect.x = shoot_srcRect.y = 0;
    shoot_srcRect.w = shoot.w;
    shoot_srcRect.h = shoot.h;
    shoot_dstRect.x = shoot.x;
    shoot_dstRect.y = shoot.y;
    shoot_dstRect.w = shoot.w;
    shoot_dstRect.h = shoot.h;
}

void shoot_draw(SDL_Renderer *renderer)
{
    if (shoot.x >= 0 && shoot.y >= 0)
    {
        shoot.x += vxShoot;
        shoot_dstRect.x = shoot.x;
        shoot_dstRect.y = shoot.y;
        SDL_RenderCopy(renderer, shoot_texture, &shoot_srcRect, &shoot_dstRect);

        if (shoot.x > kGameWidth)
        {
            // Réinitialiser le tir si il sort de l'écran
            shoot.x = shoot.y = -100;
        }
    }
}

void shoot_launch(int x, int y, int w)
{
    shoot.x = x + w; // position en x + largeur du vaisseau
    shoot.y = y;
}
