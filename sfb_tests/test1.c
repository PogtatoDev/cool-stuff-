#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>
#include <shittyfb.h>
#include <SDL2/SDL.h>

#define WINDOW_W 1024
#define WINDOW_H 1024
#define WINDOW_SIZE (Vec2) { WINDOW_W, WINDOW_H }

typedef struct {
    int x;
    int y;
} Vec2;


static inline __attribute__((always_inline)) void drawPixel(Vec2* position, Vec2* window_size, uint32_t color, uint32_t* buffer) {
    if (position->y > window_size->y || position->x > window_size->x) {
        return;
    }

    buffer[position->y * window_size->x + position->x] = color;
}

void drawLine(
        Vec2* start, Vec2* end,
        Vec2* window_size,
        uint32_t color,
        uint32_t* buffer
) {
    int32_t dx = abs(start->x - start->y);
    int32_t dy = abs(end->y - start->y);

    int32_t sex = (start->x < end->x) ? 1 : -1;
    int32_t sy = (start->y < end->y) ? 1 : -1;

    int32_t err = dx - dy;

    while (1) {
        drawPixel(&(Vec2){ start->x, start->y }, window_size, color, buffer);
        if (start->x == end->x && start->y == end->y) break;
        int32_t e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            start->x += sex;
        }

        if (e2 < dx) {
            err += dx;
            start->y += sy;
        }
    }
}

void drawRect(
        Vec2* position,
        uint32_t width, uint32_t height,
        Vec2* window_size,
        uint32_t color,
        uint32_t* buffer
) {
    for (int i = position->y; i < (position->y + height); i++) {
        drawLine(
                &(Vec2) { position->x, i }, &(Vec2) { position->x + width, i },
                &WINDOW_SIZE,
                color,
                buffer
        );
    }
}

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s\n", SDL_GetError());
        exit(-1);
    }

    sfb_window window = sfb_open_window(
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL,
            0,
            WINDOW_W, WINDOW_H,
            0
    );


    SDL_FreeFormat(window.format);
    window.format = SDL_AllocFormat(window.display_mode.format);
    window.target_fps = INFINITY;

    uint32_t* buffer = (uint32_t*)calloc(sizeof(uint32_t), WINDOW_H * WINDOW_W);

    SDL_Event event;
    while (window.is_open) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                window.is_open = false;
        }


        Vec2 mouse_pos = (Vec2) {};
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        drawLine(&(Vec2) { 0, 0 }, &mouse_pos, &WINDOW_SIZE, SDL_MapRGB(window.format, 255, 0, 0), buffer);


        sfb_update_with_buffer(&window, buffer, WINDOW_W, WINDOW_H);
    }

    sfb_close(&window);
    return 0;
}
