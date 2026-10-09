#ifndef __ROOM__
#define __ROOM__

#include "drawpool.h"
#include "utils.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <ctype.h>

#define FULL_PATH_SIZE 128 + sizeof("assets/tilemap/img/") + sizeof(fuck) + sizeof(line)

typedef struct {
    int count;
    SDL_Texture** textures;
} TileSet;

typedef struct {
    int row_size;
    int tile_size;
    int tile_arr_size;

    int* tiles;
    int* tile_draw_pool_ids;
} TileMap;

TileSet* create_tileset(char *filename, SDL_Renderer* renderer) {
    FILE* tileset_f = fopen(filename, "r");
    if (tileset_f == NULL) {
        printf("HI file doesnt exist edition\n");
        exit(1);
    }

    char line[32];
    fgets(line, sizeof(line), tileset_f);
    line[strcspn(line, "\n")] = 0;

    char myfatballs[5];
    strncpy(myfatballs, line, sizeof(myfatballs));

    if (strcmp(myfatballs, "NAME") == 0) {
        printf("No bruh\n");
        exit(1);
    }

    char fuck[16];
    strncpy(fuck, line + 5, 16);

    int count = 0;
    char** paths = malloc(32 * sizeof(char*));
    while (fgets(line, sizeof(line), tileset_f))  {
        if (isspace(line[0])) continue;
        line[strcspn(line, "\n")] = 0;

        char full_path[FULL_PATH_SIZE];
        snprintf(full_path, sizeof(full_path), "%sassets/tileset/img/%s/%s", base_path, fuck, line);
        printf("%s\n", full_path);

        paths[count] = strdup(full_path);
        count++;
    }

    fclose(tileset_f);

    SDL_Texture** textures = SDL_malloc((1 + count) * sizeof(SDL_Texture*));
    for (int i = 0; i < count; i++) {
        textures[i + 1] = IMG_LoadTexture(renderer, paths[i]);
    }
    textures[0] = NULL;

    TileSet* fuckmebro = malloc(sizeof(TileSet));
    fuckmebro->count = count;
    fuckmebro->textures = textures;

    return fuckmebro;
}

void destroy_tileset(TileSet* tileset) {
    free(tileset->textures);
    free(tileset);
}

TileMap* create_tilemap(char* filename, int tile_size, int window_w, int window_h) {
    FILE* tilemap_f = fopen(filename, "r");
    char line[16];
    const int TILE_ARR_SIZE = (window_h / tile_size) * (window_w / tile_size);
    int* tiles = malloc(TILE_ARR_SIZE);
    int i = 0;
    while (fgets(line, sizeof(line), tilemap_f)) {
        line[strcspn(line, "\n")] = 0;
        tiles[i] = atoi(line);
        i++;
    }

    fclose(tilemap_f);

    TileMap* tilemap = malloc(sizeof(TileMap));
    tilemap->row_size = window_w / tile_size;
    tilemap->tile_size = tile_size;
    tilemap->tiles = tiles;
    tilemap->tile_draw_pool_ids = malloc(TILE_ARR_SIZE);
    tilemap->tile_arr_size = TILE_ARR_SIZE;

    return tilemap;
}


void draw_pool_load_tilemap(
        TileMap* tilemap,
        TileSet* tileset,
        size_t window_w,
        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {

    SDL_Point tile_size = (SDL_Point) { tilemap->tile_size , tilemap->tile_size };
    for (int i = 0; i < tilemap->tile_arr_size; i++) {
        int x = i % tilemap->row_size;
        int y = i / tilemap->row_size;

        SDL_Point pos = (SDL_Point) {
            tilemap->tile_size * x,
            tilemap->tile_size * y
        };

        int id;
        if (tilemap->tiles[i]) {
            id = draw_pool_insert_sprite_size(
                    tileset->textures[tilemap->tiles[i]],
                    pos, tile_size, 0,
                    draw_pool, draw_pool_size, active_draw_items
            );
        } else {
            id = draw_pool_insert_rect(
                    &(SDL_Rect) { pos.x, pos.y, tile_size.x, tile_size.y },
                    (SDL_Color) { 0, 0, 0, 0 },
                    0,
                    draw_pool, draw_pool_size, active_draw_items
            );
        }

        tilemap->tile_draw_pool_ids[i] = id;
    }
}

void destroy_tilemap(
        TileMap* tilemap,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    for (int i = 0; i < tilemap->tile_arr_size; i++) {
        draw_pool_remove(tilemap->tile_draw_pool_ids[i], draw_pool, draw_pool_size, active_draw_items);
    }

    free(tilemap->tiles);
    free(tilemap->tile_draw_pool_ids);
    free(tilemap);
}

#endif
