#ifndef __DRAWITEM__
#define __DRAWITEM__

#include <SDL2/SDL.h>

#define DRAWITEM_ACTIVE (1 << 1)
#define DRAWITEM_ALWAYS_ON_TOP (1 << 2)

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

    int flags;

    int type;
    int z_idx;
    int id;
} DrawItem;

#endif
