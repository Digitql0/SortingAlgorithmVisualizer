#include <raylib.h>

int main() {
    InitWindow(800, 800, "Soritng Algorithm Visualizer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawRectangle(400, 400, 20, 20, BLUE);
        EndDrawing();
    }

    CloseWindow();
}