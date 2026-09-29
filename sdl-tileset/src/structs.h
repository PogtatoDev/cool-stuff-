#ifndef __STRUCTS__
#define __STRUCTS__


#include <SDL2/SDL.h>

typedef struct {
    int row_size;
    int tile_size;
    int tile_arr_size;

    int* tiles;
} TileMap;


typedef struct {
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

    int active;
    int type;
    int z_idx;
    int id;
} DrawItem;

typedef struct {
    SDL_Event event;
    SDL_DisplayMode display_mode;

    SDL_Renderer* renderer;
    SDL_Window* window;
    DrawItem* draw_pool;

    SDL_Point mouse_pos;

    int draw_pool_size;
    int active_draw_items;

    int8_t is_open;
} Game;

#endif
