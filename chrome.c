#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main() {
    for (uint64_t i = 0; i < UINT64_MAX; i++) {
        void *leaker = malloc(exp2(i));
    }
}
