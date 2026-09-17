#include <shittyfb.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

void drawKifOnPixelBuffer(
        int x, int y,
        FILE* kif_file,
        SDL_PixelFormat* format,
        uint32_t* output_buffer, size_t buffer_len
) {
    fseek(kif_file, 0L, SEEK_END);
    char* input_buffer = (char*)malloc(ftell(kif_file));
    rewind(kif_file);

    bool start = false;
    int balls = 0;

    for (char c = getc(kif_file); c != EOF; c = getc(kif_file)) {
        if (c == ' ') {
            continue;
        }

        if (!start && c == '=') {
            start = true;
        }

        if (start) {
            if (c == ';') {
                uint32_t new_val;
                sscanf(input_buffer, "%X", &new_val);
                output_buffer[balls] = new_val;
                balls++;

                strcpy(input_buffer, "");
            } else {
                strncat(input_buffer, &c, 16);
            }

        }
    }

    for (int i = 0; i < balls; i++) {
        output_buffer[i] = input_buffer[i];
    }

    free(input_buffer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    sfb_window window = sfb_open_window(
            SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN, 0,
            640, 480,
            SDL_PIXELFORMAT_ARGB8888
    );

    SDL_FreeFormat(window.format);
    window.format = SDL_AllocFormat(window.display_mode.format);
    window.target_fps = 100000000;

    uint32_t* buffer = (uint32_t*)calloc(sizeof(uint32_t), 640 * 480);

    FILE* f = fopen("hi.kif", "r");

    SDL_Event event;
    while (window.is_open) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window.is_open = false;
            }
        }

        drawKifOnPixelBuffer(0, 0, f, window.format, buffer, 640 * 480);

        sfb_update_with_buffer(&window, buffer, 640, 480);
    }

    sfb_close(&window);
    fclose(f);


    return 0;
}
