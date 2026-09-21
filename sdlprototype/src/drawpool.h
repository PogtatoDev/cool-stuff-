#ifndef __DRAWPOOL__
#define __DRAWPOOL__

#include "structs.h"
#include "utils.h"

void draw_pool_insert(
        DrawItem* draw_item,
        int z_idx,
        DrawItem** draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    int idx = -1;
    for (int i = 0; i < draw_pool_size; i++) {
        if (draw_pool[i] == NULL) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("massive balls\n");
        exit(1);
    }

    if (z_idx != -1) {
        draw_item->z_idx = z_idx;
    } else {
        draw_item->z_idx = idx;
    }

    draw_pool[idx] = draw_item;
    (*active_draw_items) += 1;

    qsort(draw_pool, draw_pool_size, sizeof(DrawItem), cmp_z_idx);
}

void draw_pool_remove(DrawItem* draw_item, DrawItem** draw_pool, int draw_pool_size, int* active_draw_items) {
    for (int i = 0; i < draw_pool_size; i++) {
        if (draw_pool[i] == draw_item) {
            draw_pool[i] = NULL;
            break;
        }
    }

    (*active_draw_items) -= 1;
    qsort(draw_pool, draw_pool_size, sizeof(DrawItem), cmp_z_idx);
}

#endif
