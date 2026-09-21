#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

#include "drawpool.h"
#include "structs.h"

#define WINDOW_W 640
#define WINDOW_H 480

#define SPRITE 0
#define RECT 1

void game_update(Game* g, float dt) {
    while (SDL_PollEvent(&g->event)) {
        if (g->event.type == SDL_QUIT) {
            g->is_open = 0;
        }
    }

    SDL_GetMouseState(&g->mouse_x, &g->mouse_y);
}

void game_draw(Game* g) {
    SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
    SDL_RenderClear(g->renderer);

    for (int i = 0; i < g->draw_pool_size; i++) {
        if (g->draw_pool[i] == NULL) continue;
        switch (g->draw_pool[i]->type) {
        case RECT:
            SDL_RenderFillRect(g->renderer, &g->draw_pool[i]->Rect.rect);
        }
    }

    SDL_RenderPresent(g->renderer);
}

void game_ready(Game* g) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        exit(1);
    }

    g->window = SDL_CreateWindow(
            "hi",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_W, WINDOW_H,
            SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(g->renderer, WINDOW_W, WINDOW_H);

    SDL_GetDesktopDisplayMode(-1, &g->display_mode);

    g->draw_pool_size = 256;
    g->draw_pool = (DrawItem**)malloc(sizeof(DrawItem*) * g->draw_pool_size);

    for (int i = 0; i < g->draw_pool_size; i++) {
        g->draw_pool[i] = NULL;
    }

    g->is_open = 1;

    DrawItem d;
    d.type = RECT;
    d.Rect.rect = (SDL_Rect) { .x = 50, .y = 50, .w = 10, .h = 10 };
    draw_pool_insert(&d, -1, g->draw_pool, g->draw_pool_size, &g->active_draw_items);
}

#endif
