#ifndef __ENTITY__
#define __ENTITY__

#include "utils.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    SDL_Point position;

    int colliding;
    int noclip;
    int draw_item_id;
    int type;
    int active;
} EntityBase;

void place_entity(
        SDL_Point position,
        int type,
        int draw_item_id,
        EntityBase* entity_pool,
        int entity_pool_size,
        int* active_entities
) {
    int idx = -1;
    for (int i = 0; i < entity_pool_size; i++) {
        if (!entity_pool[i].active) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("bruh");
        exit(1);
    }

    entity_pool[idx].type = type;
    entity_pool[idx].position = position;
    entity_pool[idx].active = 1;
    entity_pool[idx].draw_item_id = draw_item_id;

}

#endif
