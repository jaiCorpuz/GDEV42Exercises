#include <raylib.h>
#include <raymath.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

static ios_base::Init iostream_initializer;

const float WINDOW_WIDTH(1000);
const float WINDOW_HEIGHT(1000);

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dungeon Meshi");


    while (!WindowShouldClose()) {
        
        
        
        
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// clang++ Main.cpp libraylib.a -std=c++17 \-framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL -framework Foundation -o dungeon