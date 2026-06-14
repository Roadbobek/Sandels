//
// Created by Roadb on 10/06/2026.
//

#include "raylib.h"

int main() {
    InitWindow(800, 450, "Raylib C++ Setup");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, world!", 190, 200, 64, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}