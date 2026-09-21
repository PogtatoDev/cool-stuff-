#ifndef __STRUCTS__
#define __STRUCTS__

#include <SDL2/SDL.h>

typedef struct {
    int type;
    int z_idx;
    union {
        struct {
            SDL_Rect rect;
            SDL_Color rect_color;
        } Rect;

        struct {
            SDL_Texture* sprite;
            SDL_Rect dest_rect;
        } Sprite;
    };
} DrawItem;

typedef struct {
    SDL_Event event;
    SDL_DisplayMode display_mode;

    SDL_Renderer* renderer;
    SDL_Window* window;
    DrawItem** draw_pool;

    int mouse_x;
    int mouse_y;
    int draw_pool_size;
    int active_draw_items;

    int8_t is_open;
} Game;

#endif
