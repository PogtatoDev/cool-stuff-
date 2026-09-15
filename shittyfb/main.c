#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define WINDOW_W 1200
#define WINDOW_H 800

// fine i;ll document my code this time

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
            "shittyfb window",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_W, WINDOW_H,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // lowk i found out about textures from a random french sdl tutorial
    SDL_Texture* rushin = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_XRGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            WINDOW_W, WINDOW_H
    );

    bool open = true;
    SDL_Event event;

    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_XRGB8888);

    const uint32_t target_fps = 60;
    const uint32_t delta_time = (1000.0 / target_fps);

    const size_t buffer_size = WINDOW_W * WINDOW_H;
    uint32_t* buffer = (uint32_t*)calloc(sizeof(uint32_t), buffer_size);

    while (open) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                open = false;
        }

        // mustaaaaaaard
        for (int y = 0; y < WINDOW_H; y++) {
            for (int x = 0; x < WINDOW_W; x++) {
                buffer[y * WINDOW_W + x] = SDL_MapRGB(format, x % 255, y % 255, rand() % 255);
            }
        }

        SDL_UpdateTexture(rushin, NULL, buffer, WINDOW_W * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderCopy(
                renderer,
                rushin,
                NULL, NULL
        );

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeFormat(format);
    free(buffer);

    SDL_Quit();
}
