#ifndef __DRAWPOOL__
#define __DRAWPOOL__

#include <stdio.h>
#include <SDL2/SDL.h>

#define DRAWPOOL_FINALIZE_INSERTION\
    if (z_idx == -1) { \
        draw_pool[idx].z_idx = idx; \
    } else { \
        draw_pool[idx].z_idx = z_idx; \
    } \
    draw_pool[idx].flags |= DRAWITEM_ACTIVE; \
    draw_pool[idx].flags |= flags; \
    *(active_draw_items) += 1; \
    qsort(draw_pool, draw_pool_size, sizeof(DrawItem), cmp_z_idx); \

#include "defines.c"
#include "drawitem.c"
#include "utils.c"

int push_inactive(const void* a, const void* b);

int draw_pool_insert_sprite_size(
        SDL_Texture* sprite,
        SDL_Point position,
        SDL_Point size,
        int z_idx,
        int flags,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    int idx = -1;
    for (int i = 0; i < draw_pool_size; i++) {
        if (!(draw_pool[i].flags & DRAWITEM_ACTIVE)) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        fputs(".cat (seey.c version)", stderr);
        exit(-1);
    }

    // seeyuhis

    SDL_Rect dest_rect;

    dest_rect.w = size.x;
    dest_rect.h = size.y;
    // im back form santo domingo
    dest_rect.x = position.x;
    dest_rect.y = position.y;

    draw_pool[idx].type = SPRITE;
    draw_pool[idx].Sprite.sprite = sprite;
    draw_pool[idx].Sprite.dest_rect = dest_rect;

    int id = draw_pool[idx].id;
    DrawItem* temp_drawitem = &draw_pool[idx];

    DRAWPOOL_FINALIZE_INSERTION;
#ifdef __DEBUG__
    printf(
            "created sprite drawitem\n pos: %d %d\n size: %d %d\n texture: %p\n id: %d\n drawitem: %p\n",
            position.x, position.y,
            size.x, size.y,
            sprite,
            id, temp_drawitem
     );
#endif

    return id;
}

int draw_pool_insert_rect(
        SDL_Rect* rect,
        SDL_Color color,
        int z_idx,
        int flags,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    int idx = -1;
    for (int i = 0; i < draw_pool_size; i++) {
        if (!(draw_pool[i].flags & DRAWITEM_ACTIVE)) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        fputs("hhat", stderr);
        exit(-1);
    }

    draw_pool[idx].type = RECT;
    draw_pool[idx].Rect.rect = *rect;
    draw_pool[idx].Rect.rect_color = color;

    int id = draw_pool[idx].id;
    DrawItem* temp_drawitem = &draw_pool[idx];
    DRAWPOOL_FINALIZE_INSERTION;
#ifdef __DEBUG__
    printf(
            "created rect drawitem\n pos: %d %d\n size: %d %d\n rect: %p\n id: %d\n drawitem: %p\n",
            rect->x, rect->y,
            rect->w, rect->h,
            rect,
            id, temp_drawitem
     );
#endif
    return id;
}

inline DrawItem* get_item_from_id(int id, DrawItem* draw_pool, int draw_pool_size) {
    for (int i = 0; i < draw_pool_size; i++) {
        if (draw_pool[i].id == id) {
            return &draw_pool[i];
        }
    }

    return NULL;
}

inline void draw_pool_clear(DrawItem* draw_pool, int draw_pool_size, int* active_draw_items) {
    for (int i = 0; i < draw_pool_size; i++) {
        draw_pool[i].flags &= ~DRAWITEM_ACTIVE;
    }

    active_draw_items = 0;
}

void draw_pool_remove(
        int draw_item_id,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    for (int i = 0; i < draw_pool_size; i++) {
        if (draw_pool[i].id == draw_item_id) {
            draw_pool[i].flags &= ~DRAWITEM_ACTIVE;
            break;
        }
    }

#ifdef __DEBUG__
    printf("deleted drawitem with id %d\n", draw_item_id);
#endif

    (*active_draw_items) -= 1;
    qsort(draw_pool, draw_pool_size, sizeof(DrawItem), cmp_z_idx);
}

#undef DRAWPOOL_FINALIZE_INSERTION
#endif
