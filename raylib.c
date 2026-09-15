#include <raylib.h>

int main() {
    InitWindow(800, 600, "i3 floating");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        DrawRectangle(10, 10, 50, 50, RED);
        EndDrawing();
    }

    return 0;
}
