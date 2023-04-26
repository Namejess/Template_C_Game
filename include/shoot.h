#ifndef SHOOT_H
#define SHOOT_H

#include <SDL2/SDL.h>
#define kGameWidth 1000
#define kGameHeight 600
#define MAX_SHOOTS 10
static SDL_Texture *shoot_texture;
static SDL_Rect shoot_srcRect;
static SDL_Rect shoot_dstRect;
static int vxShoot = 10;
static int num_shoots = 0;

// Structure pour le shoot
typedef struct Shoot
{
    int x, y;             // Position de départ du shoot
    int w, h;             // Largeur et hauteur du shoot
    int vxShoot, vyShoot; // Vitesse du shoot
    SDL_Texture *texture; // Texture du shoot
    SDL_Rect srcRect;     // Rectangle source du shoot
    SDL_Rect dstRect;     // Rectangle destination du shoot
} Shoot;

static Shoot shoot;
static Shoot shoots[MAX_SHOOTS];

// Fonction pour charger une texture shoot_texture
SDL_Texture *LoadTexture(SDL_Renderer *renderer, char *path);

// Fonction pour initialiser le shoot
void shoot_init(SDL_Renderer *renderer);

// Fonction pour dessiner le shoot
void shoot_draw(SDL_Renderer *renderer);

// Fonction pour lancer le shoot
void shoot_launch(int x, int y, int w);

#endif /* Shoot_h */
