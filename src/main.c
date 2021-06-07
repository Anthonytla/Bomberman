#include "../include/game.h"

int main(void) {
    stGame *game = game_init();

    while (!game->quit) {
        game_draw(game);
        game_event(game);
    }
    
    game_destroy(game);

    return 0;
}