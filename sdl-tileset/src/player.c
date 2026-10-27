#include "entity.c"

typedef struct {
    EntityBase base;
    int mode;
} Player;

void player_init(EntityBase* base) {
    Player* p = (Player*)base;
}
