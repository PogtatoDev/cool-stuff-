#ifndef __HANDLERS__
#define __HANDLERS__

#include <SDL2/SDL.h>

typedef struct DrawItem DrawItem;
typedef struct EntityBase EntityBase;

typedef struct {
    SDL_Event event;
    SDL_DisplayMode display_mode;
    SDL_Renderer* renderer;
    SDL_Window* window;
} WindowContext;

typedef struct {
    EntityBase* entity_pool;
    int entity_pool_size;
    int active_entities;
} EntityContext;

typedef struct {
    DrawItem* draw_pool;
    int draw_pool_size;
    int active_draw_items;
} DrawContext;

#endif
