#ifndef __UTILS__
#define __UTILS__

#include "structs.h"

int cmp_z_idx(const void* a, const void* b) {
    DrawItem* item1 = (DrawItem*)a;
    DrawItem* item2 = (DrawItem*)b;

    if (!item1->active && !item2->active) return 0;
    if (!item1->active) return 1;
    if (!item2->active) return -1;

    return (item1->z_idx - item2->z_idx);
}

#endif
