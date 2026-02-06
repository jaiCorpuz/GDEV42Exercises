#include <raylib.h>
#include <raymath.h>

const float WINDOW_WIDTH(800);
const float WINDOW_HEIGHT(600);

Vector2 position = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "State Machines");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawCircleV(position, 40.0f, MAROON);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

// clang++ Main.cpp libraylib.a -std=c++17 \-framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL -framework Foundation -o camera