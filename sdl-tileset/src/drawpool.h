#ifndef __DRAWPOOL__
#define __DRAWPOOL__

#include "structs.h"
#include "utils.h"
#include "defines.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

void draw_pool_insert_rect(
        SDL_Rect* rect,
        SDL_Color color,
        int z_idx,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    int idx = -1;
    for (int i = 0; i < draw_pool_size; i++) {
        if (!draw_pool[i].active) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        fputs("what", stderr);
        exit(-1);
    }

    draw_pool[idx].type = RECT;
    draw_pool[idx].Rect.rect = *rect;
    draw_pool[idx].Rect.rect_color = color;

    if (z_idx == -1) {
        draw_pool[idx].z_idx = idx;
    } else {
        draw_pool[idx].z_idx = z_idx;
    }

    draw_pool[idx].active = 1;
    *(active_draw_items) += 1;

    qsort(draw_pool, draw_pool_size, sizeof(DrawItem), cmp_z_idx);
}

inline DrawItem* get_item_from_id(int id, DrawItem* draw_pool, int draw_pool_size) {
    for (int i = 0; i < draw_pool_size; i++) {
        if (draw_pool[i].id == id) {
            return &draw_pool[i];
        }
    }

    return NULL;
}

void draw_pool_insert_sprite(
        SDL_Texture* sprite,
        SDL_Point position,
        int z_idx,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    int idx = -1;
    for (int i = 0; i < draw_pool_size; i++) {
        if (!draw_pool[i].active) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        fputs("what (evil version)", stderr);
        exit(-1);
    }

    SDL_Rect dest_rect;

    SDL_QueryTexture(
            sprite,
            NULL,
            NULL,
            &dest_rect.w,
            &dest_rect.h
    );

    dest_rect.x = position.x;
    dest_rect.y = position.y;

    draw_pool[idx].type = SPRITE;
    draw_pool[idx].Sprite.sprite = sprite;
    draw_pool[idx].Sprite.dest_rect = dest_rect;

    if (z_idx == -1) {
        draw_pool[idx].z_idx = idx;
    } else {
        draw_pool[idx].z_idx = z_idx;
    }

    draw_pool[idx].active = 1;
    (*active_draw_items) += 1;

    qsort(draw_pool, draw_pool_size, sizeof(DrawItem), cmp_z_idx);
}

void draw_pool_remove(
        int draw_item_id,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    for (int i = 0; i < draw_pool_size; i++) {
        if (draw_pool[i].id == draw_item_id) {
            draw_pool[i].active = 0;
            break;
        }
    }

    (*active_draw_items) -= 1;
    qsort(draw_pool, draw_pool_size, sizeof(DrawItem), cmp_z_idx);
}


#endif
