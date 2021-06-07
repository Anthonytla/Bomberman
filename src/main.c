#include "../include/game.h"

int main(void) {
    stGame *game = game_init();

    printf("ok\n");

    game_destroy(game);

    return 0;
}