#include "../include/game.h"
#include <err.h>

stGame *game_init() {

    stGame *game = malloc(sizeof(stGame));
    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        errx(2, "Impossible d'initialiser la SDL");
        game_destroy(game);
        return NULL;
    }

    game->pWindow = SDL_CreateWindow("Bomberman",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);

    if (game->pWindow) {
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
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

    return game;
}
void game_destroy(stGame *game) {

    if (game) {

        if (game->pRenderer) {
            SDL_DestroyRenderer(game->pRenderer)
        }

        if (game->pWindow) {
            SDL_DestroyWindow(game->pWindow);
        }

        SDL_Quit();
        free(game);

    }
}