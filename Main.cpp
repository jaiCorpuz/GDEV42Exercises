#include <raylib.h>
#include <raymath.h>

#define CYAN (Color) {0, 220, 255, 255}

const float WINDOW_WIDTH(800);
const float WINDOW_HEIGHT(600);

Vector2 minEdge = {-500.0f, -500.0f};
Vector2 maxEdge = {1300.0f, 1100.0f};

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Camera");

    Texture2D background = LoadTexture("onepiece.jpg");

    SetTargetFPS(60.0f);
    
    Vector2 position = {400, 300};

    int cam_type = 0;
    Camera2D camera_view ={0};
    camera_view.target = position;
    camera_view.offset = {WINDOW_WIDTH /2 , WINDOW_HEIGHT / 2};
    camera_view.zoom = 1.0f;

    // Vector2 minTarget = {minEdge.x, minEdge.y};
    // Vector2 maxTarget = {maxEdge.x, maxEdge.y};
    // camera_view.target = Vector2Clamp(camera_view.target, minTarget, maxTarget);

    while (!WindowShouldClose()) {
        float delta_time = GetFrameTime();

        if(IsKeyDown(KEY_W)) {
            position.y -= 200 * delta_time;
        }
        if(IsKeyDown(KEY_A)) {
            position.x -= 200 * delta_time;
        }
        if(IsKeyDown(KEY_S)) {
            position.y += 200 * delta_time;
        }
        if(IsKeyDown(KEY_D)) {
            position.x += 200 * delta_time;
        }

        position = Vector2Clamp(position, {minEdge.x +50, minEdge.y +50}, {maxEdge.x - 50, maxEdge.y - 50});

        camera_view.target = position;

        camera_view.offset = {WINDOW_WIDTH /2 , WINDOW_HEIGHT / 2};

        float camera_view_Left = camera_view.target.x - camera_view.offset.x;
        float camera_view_Right = camera_view_Left + WINDOW_WIDTH;
        float camera_view_Top = camera_view.target.y - camera_view.offset.y;
        float camera_view_Bottom = camera_view_Top + WINDOW_HEIGHT;

        // Clamp X
        if (camera_view_Left <= minEdge.x) {
            camera_view.offset.x = camera_view.target.x - minEdge.x;
        }
        else if (camera_view_Right >= maxEdge.x) {
            camera_view.offset.x = WINDOW_WIDTH - (maxEdge.x - camera_view.target.x);
        }

        // Clamp Y
        if (camera_view_Top <= minEdge.y) {
            camera_view.offset.y = camera_view.target.y - minEdge.y;
        }
        else if (camera_view_Bottom >= maxEdge.y) {
            camera_view.offset.y = WINDOW_HEIGHT - (maxEdge.y - camera_view.target.y);
        }

        BeginDrawing();
        BeginMode2D(camera_view);
        ClearBackground(RAYWHITE);
        DrawTexture(background, minEdge.x, minEdge.y, WHITE);
        DrawCircle(position.x, position.y, 50.0f, CYAN);
        DrawCircleLines(position.x, position.y, 51.0f, BLACK);
        EndMode2D();
        // Draw UI after EndMode2D
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
    return 0;
}