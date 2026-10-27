#ifndef __UTILS__
#define __UTILS__

#include "drawitem.c"
#include "entity.c"
#include <SDL2/SDL_filesystem.h>

char* base_path;

int cmp_z_idx(const void* a, const void* b) {
    const DrawItem* item1 = (DrawItem*)a;
    const DrawItem* item2 = (DrawItem*)b;

    if (!(item1->flags & DRAWITEM_ACTIVE) && !(item1->flags & DRAWITEM_ACTIVE)) return 0;
    if (!(item1->flags & DRAWITEM_ACTIVE)) return 1;
    if (!(item2->flags & DRAWITEM_ACTIVE)) return -1;

    return (item1->z_idx - item2->z_idx);
}

int push_inactive(const void* a, const void* b) {
    const EntityBase* item1 = (EntityBase*)a;
    const EntityBase* item2 = (EntityBase*)b;

    if (!(item1->flags & ENTITY_ACTIVE) && !(item1->flags & ENTITY_ACTIVE)) return 0;
    if (!(item1->flags & ENTITY_ACTIVE)) return 1;
    if (!(item2->flags & ENTITY_ACTIVE)) return -1;
}


#endif
