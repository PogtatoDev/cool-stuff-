#ifndef __DRAWITEM__
#define __DRAWITEM__

#include <SDL2/SDL.h>

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
    int ui_element;
    int type;
    int z_idx;
    int id;
} DrawItem;

#endif
