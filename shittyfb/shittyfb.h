#ifndef __SHITTYFB__
#define __SHITTYFB__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* sdl_w;
    SDL_Renderer* sdl_r;
    SDL_Texture* texture;
    SDL_PixelFormat* format;
    SDL_DisplayMode display_mode;

    bool is_open;
    size_t target_fps;
} sfb_window;

sfb_window sfb_open_window(SDL_WindowFlags w_flags, SDL_RendererFlags r_flags, size_t width, size_t height, uint32_t pixelformat);
void sfb_update_with_buffer(sfb_window* window, uint32_t* buffer, size_t width);
void sfb_close(sfb_window* window);

#endif
