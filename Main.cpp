#include <raylib.h>
#include "Player.h"


const float WINDOW_WIDTH(800);
const float WINDOW_HEIGHT(600);


int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "State Machines");

    SetTargetFPS(60.0f);
    Vector2 position = {400, 300};
    Player player ({400, 300});

    // int cam_type = 0;
    // Camera2D camera = {0};
    // camera.target = position;
    // camera.offset = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
    // camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        float delta_time = GetFrameTime();

        player.Update(delta_time);

        // camera.target = position;

        BeginDrawing();
        //BeginMode2D(camera);
        ClearBackground(DARKGRAY);
        player.Draw();
        //EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

// clang++ Main.cpp libraylib.a -std=c++17 \-framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL -framework Foundation -o camera