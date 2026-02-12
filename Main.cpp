#include <raylib.h>
#include "Player.cpp"
#include "Player.hpp"

const float WINDOW_WIDTH(800);
const float WINDOW_HEIGHT(600);

// Vector2 MIN_EDGE = {-300.0f, -500.0f};
Vector2 MIN_EDGE = {-500.0f, -300.0f};
// Vector2 MAX_EDGE = {538.0f, 1620.0f};
Vector2 MAX_EDGE = {1420.0f, 738.0f};

void ClampPlayer(Player& player, Vector2 min_edge, Vector2 max_edge, float radius) {
    Vector2 player_position = player.GetPosition();
    
    player_position.x = (player_position.x - radius < min_edge.x) ? min_edge.x + radius : (player_position.x + radius > max_edge.x ? max_edge.x - radius : player_position.x);
    player_position.y = (player_position.y - radius < min_edge.y) ? min_edge.y + radius : (player_position.y + radius > max_edge.y ? max_edge.y - radius : player_position.y);

    player.SetPosition(player_position);

}

void ClampCamera(Player& player, Vector2 min_edge, Vector2 max_edge, Camera2D& camera) {
    Vector2 half_view = {(GetScreenWidth()/2)/camera.zoom, (GetScreenHeight()/2)/camera.zoom};

    float cam_min_x = min_edge.x + half_view.x;
    float cam_min_y = min_edge.y + half_view.y;
    float cam_max_x = max_edge.x - half_view.x;
    float cam_max_y = max_edge.y - half_view.y;

    camera.target = Vector2Clamp(camera.target, {cam_min_x, cam_min_y}, {cam_max_x, cam_max_y});
}

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "State Machines");

    Texture2D background = LoadTexture("ponyo underwater.jpg");

    SetTargetFPS(60.0f);
    Vector2 position = {400, 300};
    Player player ({400, 300});

    int cam_type = 0;
    Camera2D camera = {0};
    camera.target = position;
    camera.offset = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        float delta_time = GetFrameTime();

        player.Update(delta_time);
        
        ClampPlayer(player, MIN_EDGE, MAX_EDGE, 40.0f);

        camera.target = player.GetPosition();

        ClampCamera(player, MIN_EDGE, MAX_EDGE, camera);



        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(RAYWHITE);
        DrawTexture(background, MIN_EDGE.x, MIN_EDGE.y, WHITE);
        player.Draw();
        EndMode2D();
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
    return 0;
}

// clang++ Main.cpp Player.cpp libraylib.a -std=c++17 \-framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL -framework Foundation -o state