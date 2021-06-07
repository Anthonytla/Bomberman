#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct {

    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
} stGame;

stGame *game_init();
void game_destroy(stGame *game);

#endif