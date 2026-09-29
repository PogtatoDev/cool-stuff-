#ifndef __TILEMAP__
#define __TILEMAP__

#include "structs.h"
#include "drawpool.h"

void draw_tilemap(
        TileMap* tilemap,
        SDL_Texture** tileset,
        size_t window_w,
        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    for (int i = 0; i < tilemap->tile_arr_size; i++) {
        SDL_Point pos = (SDL_Point) { i % tilemap->row_size, SDL_floorf((float)i / tilemap->row_size) };
        draw_pool_insert_sprite(tileset[tilemap->tiles[i]], pos, 0, draw_pool, draw_pool_size, active_draw_items);
    }
}

#endif
