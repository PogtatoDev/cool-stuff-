#ifndef __ROOM__
#define __ROOM__

#include "drawpool.h"
#include "utils.h"
#include <SDL2/SDL_image.h>
#include <ctype.h>

typedef struct {
    int count;
    SDL_Texture** textures;
} TileSet;

typedef struct {
    int row_size;
    int tile_size;
    int tile_arr_size;

    int* tiles;
} TileMap;

TileSet* create_tileset(char *filename, SDL_Renderer* renderer) {
    printf("HI\n");
    FILE* tileset_f = fopen(filename, "r");
    if (tileset_f == NULL) {
        printf("HI file doesnt exist edition\n");
        exit(1);
    }

    char buffer[64];

    fgets(buffer, 64, tileset_f);

    char myfatballs[5];
    strncpy(myfatballs, buffer, 5);

    if (strcmp(myfatballs, "NAME") == 0) {
        printf("No bruh\n");
        exit(1);
    }

    char fuck[16];
    strncpy(fuck, buffer + 5, 16);

    for (int i = 0; i < sizeof(buffer) - 1; i++) {
        buffer[i] = '!';
    }

    int idx = 0;
    char c;
    int count;

    SDL_Texture** textures = SDL_malloc(64 * sizeof(SDL_Texture*));

    char line[32];
    while (fgets(line, sizeof(line), tileset_f))  {
        if (isspace(line)) continue;
        line[strcspn(line, "\n")] = 0;

        printf("%s\n", line);

        char full_path[128 + 64];
        strncpy(full_path, base_path, 128);
        strncat(full_path, line, 64);
        printf("%s\n", full_path);

        idx = 0;
        count++;
    }

    while ((c = fgetc(tileset_f)) != EOF) {
        if (isspace(c)) continue;
        if (c == ';') {
            char filename_but_like_not_the_full_path[64];

            for (int i = 0; i < sizeof(buffer) - 1; i++) {
                if (buffer[i] != '!' && buffer[i]) {
                    filename_but_like_not_the_full_path[i] = buffer[i];
                } else {
                    break;
                }
            }

            for (int i = 0; i < sizeof(buffer); i++) {
                buffer[i] = '!';
            }

            printf("%s\n", filename_but_like_not_the_full_path);

            char full_path[128 + 64];
            strncpy(full_path, base_path, 128);
            
            strncat(full_path, filename_but_like_not_the_full_path, 64);
            printf("%s\n", full_path);

            idx = 0;
            count++;
        } else {
            while (buffer[idx] + 1 && buffer[idx] != '!') idx++;
            buffer[idx] = c;
        }
    }

    TileSet* fuckmebro = malloc(sizeof(TileSet));
    fuckmebro->count = 6767;
    fuckmebro->textures = textures;

    return fuckmebro;
}

void destroy_tileset(TileSet* tileset) {
    free(tileset->textures);
    free(tileset);
}

void draw_tilemap(
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

        draw_pool_insert_sprite_size(
                tileset->textures[tilemap->tiles[i]],
                pos, tile_size, 0,
                draw_pool, draw_pool_size, active_draw_items
        );
    }
}

void load_collisions() {

}

#endif
