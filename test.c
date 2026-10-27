#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

int main() {
    SDL_Window* window1 = SDL_CreateWindow("hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 50, 50, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);
    SDL_Window* window2 = SDL_CreateWindow("hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 50, 50, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED);
    SDL_Window* window3 = SDL_CreateWindow("hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 50, 50, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer3 = SDL_CreateRenderer(window3, -1, SDL_RENDERER_ACCELERATED);
    SDL_Window* window4 = SDL_CreateWindow("hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 50, 50, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer4 = SDL_CreateRenderer(window4, -1, SDL_RENDERER_ACCELERATED);
    SDL_Window* window5 = SDL_CreateWindow("hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 50, 50, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer5 = SDL_CreateRenderer(window5, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    int is_open = 1;

    while (is_open) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                is_open = 0;
            }
        }

        SDL_RenderClear(renderer1);
        SDL_RenderClear(renderer2);
        SDL_RenderClear(renderer3);
        SDL_RenderClear(renderer4);
        SDL_RenderClear(renderer5);

        SDL_RenderPresent(renderer1);
        SDL_RenderPresent(renderer2);
        SDL_RenderPresent(renderer3);
        SDL_RenderPresent(renderer4);
        SDL_RenderPresent(renderer5);
    }

    return 0;
}
