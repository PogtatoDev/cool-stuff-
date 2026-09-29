#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <stdlib.h>

#include "defines.h"
#include "drawpool.h"
#include "structs.h"

#define WINDOW_W 640
#define WINDOW_H 480


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

    for (int i = 0; i < g->active_draw_items; i++) {
        if (g->draw_pool[i].type == SPRITE) {
            g->draw_pool[i].Sprite.dest_rect.x = rand() % WINDOW_W;
            g->draw_pool[i].Sprite.dest_rect.y = rand() % WINDOW_H;
        }
    }

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

    for (int i = 0; i < 16; i++) {
        SDL_Texture* texture = IMG_LoadTexture(g->renderer, "hi.png");
        if (texture == NULL) {
            printf("%s\n", IMG_GetError());
        }

        draw_pool_insert_sprite(texture, (SDL_Point) { rand() % WINDOW_W, rand() % WINDOW_H }, -1, DRAWPOOL_FUNC_END);
    }
}

void game_init(Game* g) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) < 0) {
        exit(1);
    }

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
}

#endif
