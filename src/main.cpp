#include <bits/this_thread_sleep.h>

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
    try {
        InitAudioDevice();
        InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, "Snake");
        SetTargetFPS(FPS);

        Game game(UPDATE_INTERVAL, CELL_SIZE, CELL_COUNT);

        while (!WindowShouldClose()) {
            BeginDrawing();

            if (game.update() == StateGame::GAME_OVER) {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            }

            ClearBackground(WHITE);

            EndDrawing();
        }
        CloseAudioDevice();

        CloseWindow();
    } catch (GameOver const& ex) {
        std::cerr << "Game over: " << ex.what() << std::endl;
        CloseAudioDevice();
    } catch (std::exception const& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        CloseAudioDevice();
    }
    return 0;
}
