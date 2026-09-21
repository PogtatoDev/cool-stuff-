#include <SDL2/SDL.h>
#include "game.h"

int main(void) {
    Game game;
    game_ready(&game);

    while (game.is_open) {
        game_update(&game, 1.0 / 60.0);
        game_draw(&game);
    }

    return 0;
}
