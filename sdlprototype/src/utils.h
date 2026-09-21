#ifndef __UTILS__
#define __UTILS__

#include "structs.h"

int cmp_z_idx(const void* a, const void* b) {
    DrawItem* item1 = *(DrawItem**)a;
    DrawItem* item2 = *(DrawItem**)b;

    return (item1->z_idx - item2->z_idx);
}

#endif
