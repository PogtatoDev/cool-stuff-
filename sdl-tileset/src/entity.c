#ifndef __ENTITY__
#define __ENTITY__

#include "utils.c"
#include "drawpool.c"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define ENTITY_COLLIDING (1 << 1)
#define ENTITY_NOCLIP    (1 << 2)
#define ENTITY_ACTIVE    (1 << 3)

typedef struct EntityBase {
    SDL_Point position;

    int flags;
    int draw_item_id;
    int type;
    int id;

    void (*ready) (struct EntityBase*);
    void (*update)(struct EntityBase*);
} EntityBase;

int push_inactive(const void* a, const void* b);
int draw_pool_insert_sprite_size(
        SDL_Texture* sprite,
        SDL_Point position,
        SDL_Point size,
        int z_idx,
        int flags,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
);

int place_entity(
        SDL_Point position,
        int type,
        int draw_item_id,
        int flags,
        void (*ready) (struct EntityBase*),
        void (*update)(struct EntityBase*),

        EntityBase* entity_pool,
        int entity_pool_size,
        int* active_entities
) {
    int idx = -1;
    for (int i = 0; i < entity_pool_size; i++) {
        if (!(entity_pool[i].flags & ENTITY_ACTIVE)) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("br.c");
        exit(1);
    }

    entity_pool[idx].type = type;
    entity_pool[idx].position = position;
    entity_pool[idx].flags |= ENTITY_ACTIVE;
    entity_pool[idx].draw_item_id = draw_item_id;

    return entity_pool[idx].id;
}

int place_entity_with_sprite(
        SDL_Texture* sprite,
        int z_idx,
        int draw_item_flags,
        SDL_Point position,
        int type,
        int entity_flags,
        void (*ready) (struct EntityBase*),
        void (*update)(struct EntityBase*),

        EntityBase* entity_pool,
        int entity_pool_size,
        int* active_entities,

        DrawItem* draw_pool,
        int draw_pool_size,
        int* active_draw_items
) {
    int idx = -1;
    for (int i = 0; i < entity_pool_size; i++) {
        if (!(entity_pool[i].flags & ENTITY_ACTIVE)) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("br.c");
        exit(1);
    }

    entity_pool[idx].type = type;
    entity_pool[idx].position = position;
    entity_pool[idx].flags |= ENTITY_ACTIVE;

    int w, h;
    SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

    int id = draw_pool_insert_sprite_size(
            sprite,
            position,
            (SDL_Point) { w, h },
            z_idx,
            draw_item_flags,
            draw_pool, draw_pool_size, active_draw_items
    );

    entity_pool[idx].draw_item_id = id;
    id = entity_pool[idx].id;

    qsort(entity_pool, entity_pool_size, sizeof(EntityBase), push_inactive);
    return entity_pool[idx].id;
}

#endif
