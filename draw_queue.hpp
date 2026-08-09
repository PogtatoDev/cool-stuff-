#include "numerictypes.h"
#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef DRAW_QUEUE_SIZE
#define DRAW_QUEUE_SIZE 128
#endif

std::array<sf::Drawable *, DRAW_QUEUE_SIZE> draw_queue;

i32 dq_add(sf::Drawable *d) {
    for (i32 i = 0; i < DRAW_QUEUE_SIZE; i++)
        if (!draw_queue[i]) {
            draw_queue[i] = d;
            return i;
        }

    std::cerr << "draw queue full you fucker\n";
    exit(1);
}

void dq_remove(i32 index) { draw_queue[index] = nullptr; }
