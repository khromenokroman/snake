#include <bits/this_thread_sleep.h>

#include <chrono>
#include <deque>
#include <iostream>

#include "game.hpp"
#include "raylib-cpp.hpp"

/** @brief Размер ячейки игрового поля в пикселях */
static constexpr uint64_t CELL_SIZE = 30;

/** @brief Количество ячеек по одному измерению игрового поля */
static constexpr uint64_t CELL_COUNT = 25;

/** @brief Интервал обновления положения змейки в миллисекундах */
static constexpr double UPDATE_INTERVAL = 200;

/** @brief Количество кадров в секунду */
static constexpr int FPS = 60;

static constexpr uint64_t OFFSET = 60;

int main() {
    try {
        InitAudioDevice();
        InitWindow(2 * OFFSET + CELL_SIZE * CELL_COUNT, 2 * OFFSET + CELL_SIZE * CELL_COUNT, "Snake");
        SetTargetFPS(FPS);

        Game game(UPDATE_INTERVAL, CELL_SIZE, CELL_COUNT, OFFSET);

        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(WHITE);

            DrawText("Old Snake! Start the game!", OFFSET - 5, 15, 40, BLACK);

            // Рисуем клетчатый фон
            for (int x = 0; x < CELL_COUNT; ++x) {
                for (int y = 0; y < CELL_COUNT; ++y) {
                    if ((x + y) % 2 == 0) {
                        DrawRectangle(OFFSET + x * CELL_SIZE, OFFSET + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, Color{230, 255, 230, 255});
                    } else {
                        DrawRectangle(OFFSET + x * CELL_SIZE, OFFSET + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, Color{220, 245, 220, 255});
                    }
                }
            }

            DrawRectangleLinesEx(Rectangle{OFFSET - 5, OFFSET - 5, CELL_SIZE * CELL_COUNT + 10, CELL_SIZE * CELL_COUNT + 10}, 5, BLACK);

            if (game.update() == StateGame::GAME_OVER) {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            }
            DrawText(TextFormat("Score: %lu", game.get_score()), OFFSET - 5, OFFSET + CELL_SIZE * CELL_COUNT + 10, 40, BLACK);

            EndDrawing();
        }
        CloseAudioDevice();

        CloseWindow();
        return 0;
    } catch (std::exception const& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        CloseAudioDevice();
        CloseWindow();
    }
}
