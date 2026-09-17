#include <SDL2/SDL_pixels.h>
#include <shittyfb.h>
#include <SDL2/SDL.h>
#include <stdint.h>

#define WINDOW_W 1200
#define WINDOW_H 800

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    sfb_window window = sfb_open_window(
            SDL_WINDOW_SHOWN, 0,
            WINDOW_W, WINDOW_H,
            SDL_PIXELFORMAT_ARGB8888
    );

    SDL_FreeFormat(window.format);
    window.format = SDL_AllocFormat(window.display_mode.format);

    uint32_t* buffer = (uint32_t*)calloc(sizeof(uint32_t), WINDOW_H * WINDOW_W);

    SDL_Event event;
    while (window.is_open) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window.is_open = false;
            }
        }

        for (int i = 0; i < WINDOW_H * WINDOW_W; i++) {
            buffer[i] = SDL_MapRGB(window.format, 255, (i % 255), 0);
        }

        sfb_update_with_buffer(&window, buffer, WINDOW_W);
    }

    sfb_close(&window);
}

