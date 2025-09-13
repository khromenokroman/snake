#include <chrono>
#include <deque>
#include <iostream>

#include "game.hpp"
#include "raylib-cpp.hpp"

static constexpr uint64_t CELL_SIZE = 30;
static constexpr uint64_t CELL_COUNT = 25;
static constexpr double UPDATE_INTERVAL = 200;
static constexpr int FPS = 60;

int main() {
    InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, "Snake");
    SetTargetFPS(FPS);

    Game game(UPDATE_INTERVAL, CELL_SIZE, CELL_COUNT);

    while (!WindowShouldClose()) {
        BeginDrawing();

        game.update();

        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
