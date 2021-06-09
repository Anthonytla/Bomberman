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
<<<<<<< HEAD
    SDL_Rect bombRect;
    SDL_bool hasBomb[15];
    SDL_bool quit;
=======
    SDL_Rect bomb[4];
    SDL_bool hasBomb[4];
    SDL_bool key[6];
    SDL_bool quit;
    int bombNbr;
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
} stGame;

stGame *game_init();
void game_draw(stGame *game);
void game_event(stGame *game);
<<<<<<< HEAD
=======
void game_move(stGame *game);
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
void game_destroy(stGame *game);

#endif