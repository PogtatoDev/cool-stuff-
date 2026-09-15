#include "shittyfb.h"
#include <stdio.h>

sfb_window sfb_open_window(
        SDL_WindowFlags w_flags,
        SDL_RendererFlags r_flags,
        size_t width,
        size_t height,
        uint32_t pixelformat
)
{
    SDL_Window *window = SDL_CreateWindow(
          "shittyfb window",
          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
          width,  height,
          w_flags
    );
    if (window == NULL) {
        printf("couldnt open window bla bla: %s", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, r_flags | SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("couldnt open windi mean renderer yeahj: %s", SDL_GetError());
        exit(1);
    }

    // lowk i found out about textures from a random french sdl tutorial
    SDL_Texture *rushin = SDL_CreateTexture(
            renderer,
            pixelformat, SDL_TEXTUREACCESS_STREAMING, width, height
    );

    SDL_PixelFormat *format = SDL_AllocFormat(pixelformat);

    SDL_DisplayMode display_mode;

    SDL_GetDesktopDisplayMode(0, &display_mode);
    return (sfb_window) {
          .sdl_w = window,
          .sdl_r = renderer,
          .texture = rushin,
          .format = format,
          .display_mode = display_mode,
          .is_open = true,
          .target_fps = display_mode.refresh_rate,
    };
}

void sfb_update_with_buffer(sfb_window* window, uint32_t* buffer, size_t width) {
    SDL_UpdateTexture(window->texture,
            NULL,
            buffer,
            width * sizeof(uint32_t)
    );

    SDL_RenderClear(window->sdl_r);
    SDL_RenderCopy(
            window->sdl_r,
            window->texture,
            NULL, NULL
    );

    SDL_RenderPresent(window->sdl_r);
    SDL_Delay(1000.0 / window->target_fps);
}

void sfb_close(sfb_window* window) {
    SDL_DestroyWindow(window->sdl_w);
    SDL_DestroyRenderer(window->sdl_r);
    SDL_DestroyTexture(window->texture);
    SDL_FreeFormat(window->format);
}
