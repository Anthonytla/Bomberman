#include "../include/game.h"

int main(void) {
    stGame *game = game_init();

    while (!game->quit) {
        game_draw(game);
        game_event(game);
<<<<<<< HEAD
=======
        game_move(game);
>>>>>>> 5b00709a96ee74fe022af6685b8cddf3b75fafe8
    }
    
    game_destroy(game);

    return 0;
}