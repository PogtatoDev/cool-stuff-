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

void update_buffer(uint32_t* buffer, SDL_PixelFormat* format) {
    int i = 0;
    for (int y = 0; y < WINDOW_H; y++) {
        for (int x = 0; x < WINDOW_W; x++) {
            buffer[i] = SDL_MapRGB(format, 255, 0, 0);

            i++;
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("failed to initialize sdl video: %s", SDL_GetError());
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow(
            "shittyfb window",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_W, WINDOW_H,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (window == NULL) {
        printf("couldnt open window bla bla: %s", SDL_GetError());
        exit(1);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("couldnt open windi mean renderer yeahj: %s", SDL_GetError());
        exit(1);
    }

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
    const uint32_t dt_ms = (1000.0 / target_fps);

    uint32_t* buffer = (uint32_t*)calloc(sizeof(uint32_t), WINDOW_H * WINDOW_W);

    while (open) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                open = false;
        }

        update_buffer(buffer, format);

        SDL_UpdateTexture(rushin, NULL, buffer, WINDOW_W * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderCopy(
                renderer,
                rushin,
                NULL, NULL
        );

        SDL_RenderPresent(renderer);

        SDL_Delay(dt_ms);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeFormat(format);
    free(buffer);

    SDL_Quit();
}
