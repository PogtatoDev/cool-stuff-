#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include "src/game.c"

int main(void) {
    Game game;
    game_ready(&game);

    while (game.is_open) {
        game_update(&game, game.display_mode.refresh_rate);
        game_draw(&game);
    }

    return 0;
}
