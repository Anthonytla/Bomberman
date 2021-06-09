#include "../include/game.h"
#include <err.h>
#include <SDL2/SDL_image.h>

stGame *game_init() {

    stGame *game = malloc(sizeof(stGame));
    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->pTextPlayer = NULL;
    game->backgroundRect.x = 0;
    game->backgroundRect.y = 0;
    game->backgroundRect.w = game->screenSize.x;
    game->backgroundRect.h = game->screenSize.y;
    game->playerPositionRect.x = game->screenSize.x / 2;
    game->playerPositionRect.y = game->screenSize.y / 2;
    game->playerPositionRect.w = 60;
    game->playerPositionRect.h = 60;
<<<<<<< HEAD
    game->bombRect.w = 60;
    game->bombRect.h = 60;
=======
    game->bombNbr = 0;
    for (int i = 0; i < 4; i++) {
        game->bomb[i].w = 60;
        game->bomb[i].h = 60;
    }
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        errx(2, "Impossible d'initialiser la SDL");
        game_destroy(game);
        return NULL;
    }

    game->pWindow = SDL_CreateWindow("Bomberman",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);

    if (game->pWindow) {
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!game->pRenderer) {
            errx(2, "Impossible de créer le renderer SDL");
            game_destroy(game);
            return NULL;
        }
    } else {
        errx(2, "Impossible de créer la fenêtre SDL");
        game_destroy(game);
        return NULL;
    }

    SDL_Surface *surfaceBackground = IMG_Load("src/background.jpg");
    if (!surfaceBackground) {
            errx(2, "Impossible de créer le background SDL");
            game_destroy(game);
            return NULL;
    }
    else {
        game->pTextBackground = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBackground);
        if (!game->pTextBackground)
        {
            printf("Impossible de créer la texture SDL: %s", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surfaceBackground);
<<<<<<< HEAD
    }


=======
        
    }

>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
    SDL_Surface *surfacePlayer = IMG_Load("src/32x32-7719.gif");
    if (!surfacePlayer) {
        errx(2, "Impossible de charger l'image");
        game_destroy(game);
        return NULL;
    } else {
        game->pTextPlayer = SDL_CreateTextureFromSurface(game->pRenderer, surfacePlayer);
        if (!game->pTextPlayer) {
            errx(2, "Impossible de traiter la texture");
            game_destroy(game);
            return NULL;
        } 
        SDL_FreeSurface(surfacePlayer);
    }
<<<<<<< HEAD
=======

    SDL_Surface *surfaceBomb = IMG_Load("src/bomb.png");
    if (!surfaceBomb) {
            errx(2, "Impossible de créer le background SDL");
            game_destroy(game);
            return NULL;
    }
    else {
        game->pTextBomb = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBomb);
        if (!game->pTextBomb)
        {
            printf("Impossible de créer la texture SDL: %s", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surfaceBomb);
    }
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
    return game;
}
void game_destroy(stGame *game) {

    if (game) {

<<<<<<< HEAD
=======
        if (game->pTextBomb) {
            SDL_DestroyTexture(game->pTextBomb);
        }

>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
        if (game->pTextPlayer){
            SDL_DestroyTexture(game->pTextPlayer);
        }
        
        if (game->pTextBackground) {
            SDL_DestroyTexture(game->pTextBackground);
        }

        if (game->pRenderer) {
            SDL_DestroyRenderer(game->pRenderer);
        }

        if (game->pWindow) {
            SDL_DestroyWindow(game->pWindow);
        }

        SDL_Quit();
        free(game);
    }
}

void game_draw(stGame *game) {

    SDL_RenderCopy(game->pRenderer, game->pTextBackground, NULL, &game->backgroundRect);
    SDL_RenderCopy(game->pRenderer, game->pTextPlayer, NULL, &game->playerPositionRect);
<<<<<<< HEAD
    for (int i = 0; i < 15; i++) {
        if (game->hasBomb[i]) {
            SDL_RenderCopy(game->pRenderer, game->pTextBomb, NULL, &game->bombRect);
=======
    for (int i = 0; i < 4; i++) {
        if (game->hasBomb[i]) {
            SDL_RenderCopy(game->pRenderer, game->pTextBomb, NULL, &game->bomb[i]);
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8

        }
    }
    SDL_RenderPresent(game->pRenderer);
}

void game_event(stGame *game) {

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type)
        {
        case SDL_QUIT:
            game->quit = SDL_TRUE;
            break;
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym)
            {
                case SDLK_RIGHT:
<<<<<<< HEAD
                    game->playerPositionRect.x += 2;
                    if (game->playerPositionRect.x + 60> 640) 
                        game->playerPositionRect.x = 640 - 60;
                    break;
                case SDLK_LEFT:
                    game->playerPositionRect.x -= 2;
                    if (game->playerPositionRect.x < 0)
                         game->playerPositionRect.x = 0;
                    break;
                case SDLK_DOWN:
                    game->playerPositionRect.y += 2;
                    if (game->playerPositionRect.y + 60> 480)
                        game->playerPositionRect.y = 480 - 60;
                    break;
                case SDLK_UP:
                    game->playerPositionRect.y -= 2;
                    if (game->playerPositionRect.y < 0)
                        game->playerPositionRect.y = 0;
                    break;
                default:
                    break;
            }
=======
                    game->key[SDL_SCANCODE_RIGHT] = SDL_TRUE;
                    break;
                case SDLK_LEFT:
                    game->key[SDL_SCANCODE_LEFT] = SDL_TRUE;
                    break;
                case SDLK_DOWN:
                    game->key[SDL_SCANCODE_DOWN] = SDL_TRUE;
                    break;
                case SDLK_UP:
                    game->key[SDL_SCANCODE_UP] = SDL_TRUE;
                    break;
                case SDLK_b:
                    game->key[SDL_SCANCODE_B] = SDL_TRUE;
                    break;
                default:
                    break;
            };
            break;
        case SDL_KEYUP:
            switch (ev.key.keysym.sym)
            {
                case SDLK_RIGHT:
                    game->key[SDL_SCANCODE_RIGHT] = SDL_FALSE;
                    break;
                case SDLK_LEFT:
                    game->key[SDL_SCANCODE_LEFT] = SDL_FALSE;
                    break;
                case SDLK_DOWN:
                    game->key[SDL_SCANCODE_DOWN] = SDL_FALSE;
                    break;
                case SDLK_UP:
                    game->key[SDL_SCANCODE_UP] = SDL_FALSE;
                    break;
                case SDLK_b:
                    game->key[SDL_SCANCODE_B] = SDL_FALSE;
                    break;
                default:
                    break;
            };
            break;
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
        default:
            break;
        }
    }
<<<<<<< HEAD
=======
}

void game_move(stGame *game) 
{
    if (game->key[SDL_SCANCODE_RIGHT]) {
        game->playerPositionRect.x += 1;
        if (game->playerPositionRect.x + 60 > 640) 
            game->playerPositionRect.x = 640 - 60;
    }
    else if (game->key[SDL_SCANCODE_LEFT])
    {
        game->playerPositionRect.x -= 1;
        if (game->playerPositionRect.x < 0)
                game->playerPositionRect.x = 0;
    }
    else if (game->key[SDL_SCANCODE_DOWN])
    {
        game->playerPositionRect.y += 1;
        if (game->playerPositionRect.y + 60 > 480)
            game->playerPositionRect.y = 480 - 60;
    }
    else if (game->key[SDL_SCANCODE_UP])
    {
        game->playerPositionRect.y -= 1;
        if (game->playerPositionRect.y < 0)
            game->playerPositionRect.y = 0;
    }
    else if (game->key[SDL_SCANCODE_B])
    {
        if (game->bombNbr < 4) {
            game->hasBomb[game->bombNbr] = SDL_TRUE;
            game->bomb[game->bombNbr].x = game->playerPositionRect.x;
            game->bomb[game->bombNbr].y = game->playerPositionRect.y;
            game->bombNbr += 1;
            game->key[SDL_SCANCODE_B] = SDL_FALSE;
        }
    }
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
}