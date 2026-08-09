#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdarg.h>
#include <stdint.h>

void crash(char *msg) {
    printf("%s\n", msg);
    exit(1);
}

void crash_free(char *msg, int32_t ptr_count, ...) {
    va_list ptrs;
    va_start(ptrs, ptr_count);

    for (int32_t i = 0; i < ptr_count; i++) {
        void *ptr = va_arg(ptrs, void *);

        if (ptr != NULL) {
            free(ptr);
            printf("freed %p\n", ptr);
        }
    }

    crash(msg);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("could not init sdl: ");
        crash((char *)SDL_GetError());
    }

    SDL_Window *main_window =
        SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         800, 600, SDL_WINDOW_SHOWN);
    if (main_window == NULL)
        crash("could not initialize sdl window");

    SDL_Renderer *renderer =
        SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        crash("could not initialize sdl renderer");

    SDL_Event evt;
    int8_t window_is_open = 1;
    while (window_is_open) {
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT)
                window_is_open = 0;
        }

        int32_t x, y;
        SDL_GetMouseState(&x, &y);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(
            renderer, &(SDL_Rect){.x = x - 25, .y = y - 25, .w = 50, .h = 50});

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(main_window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}
