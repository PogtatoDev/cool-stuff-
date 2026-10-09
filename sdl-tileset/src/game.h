#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <stdlib.h>

#include "defines.h"
#include "room.h"
#include "drawitem.h"
#include "entity.h"
#include "utils.h"

#define WINDOW_W 640
#define WINDOW_H 480

typedef struct {
    SDL_Event event;
    SDL_DisplayMode display_mode;

    SDL_Renderer* renderer;
    SDL_Window* window;

    DrawItem* draw_pool;
    EntityBase* entity_pool;

    SDL_Point mouse_pos;

    int draw_pool_size;
    int active_draw_items;

    int entity_pool_size;
    int active_entities;

    int8_t is_open;
} Game;

void game_poll_events(Game *g) {
    while (SDL_PollEvent(&g->event)) {
        if (g->event.type == SDL_QUIT) {
            g->is_open = 0;
        }
    }

    SDL_GetMouseState(&(g->mouse_pos.x), &(g->mouse_pos.y));
}

void game_update(Game* g, float dt_ms) {
    game_poll_events(g);
    SDL_Delay(dt_ms);
}

void game_draw(Game* g) {
    SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
    SDL_RenderClear(g->renderer);

    for (int i = 0; i < g->active_draw_items; i++) {
        if (!g->draw_pool[i].active) continue;
        switch (g->draw_pool[i].type) {
        case RECT:
        {
            SDL_Color* c = &g->draw_pool[i].Rect.rect_color;

            SDL_SetRenderDrawColor(
                    g->renderer,
                    c->r,
                    c->g,
                    c->b,
                    c->a
            );
       }
            SDL_RenderFillRect(g->renderer, &g->draw_pool[i].Rect.rect);
            break;
        case SPRITE:
        {
            SDL_RenderCopy(
                    g->renderer,
                    g->draw_pool[i].Sprite.sprite,
                    NULL,
                    &g->draw_pool[i].Sprite.dest_rect
            );
            break;
        }
        }

    }



    SDL_RenderPresent(g->renderer);
}


void init_draw_pool(Game* g) {
    g->draw_pool_size = 1024;
    g->draw_pool = (DrawItem*)malloc(sizeof(DrawItem) * g->draw_pool_size);

    for (int i = 0; i < g->draw_pool_size; i++) {
        g->draw_pool[i].active = 0;
        g->draw_pool[i].id = i;
    }
}

void game_init(Game* g) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) < 0) {
        exit(1);
    }

    base_path = malloc(128 * sizeof(char));
    strncpy(base_path, SDL_GetBasePath(), 128);

    g->window = SDL_CreateWindow(
            "hi",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_W, WINDOW_H,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(g->renderer, WINDOW_W, WINDOW_H);
    SDL_GetDesktopDisplayMode(-1, &g->display_mode);

    init_draw_pool(g);
    g->is_open = 1;
}

void game_ready(Game* g) {
    game_init(g);

    TileSet* tileset = create_tileset("../assets/tileset/test.tileset", g->renderer);
}

#endif
