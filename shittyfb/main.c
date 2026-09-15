#include "shittyfb.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    sfb_window window = sfb_open_window(
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
            SDL_RENDERER_ACCELERATED,
            1200,
            800,
            SDL_PIXELFORMAT_ARGB8888
    );
    window.target_fps = 10000;

    uint32_t* buffer = (uint32_t*)calloc(sizeof(uint32_t), 1200 * 800);

    SDL_Event event;
    while (window.is_open) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                window.is_open = false;
        }

        for (int i = 0; i < 1200 * 800; i++) {
            uint32_t c[3] = { (rand() % 255), (rand() % 255), (rand() % 255) };
            buffer[i] = SDL_MapRGB(window.format, c[0], c[1], c[2]);
        }

        sfb_update_with_buffer(&window, buffer, 1200);
    }

    sfb_close(&window);
    free(buffer);

    return 0;
}
