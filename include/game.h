#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct {

    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    SDL_Texture *pTextPlayer;
    SDL_Texture *pTextBackground;
    SDL_Texture *pTextBomb;
    SDL_Rect backgroundRect;
    SDL_Rect playerPositionRect;
    SDL_Rect bombRect;
    SDL_bool hasBomb[15];
    SDL_bool quit;
} stGame;

stGame *game_init();
void game_draw(stGame *game);
void game_event(stGame *game);
void game_destroy(stGame *game);

#endif