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

int main() {
    try {
        InitAudioDevice();
        InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, "Snake");
        SetTargetFPS(FPS);

        Game game(UPDATE_INTERVAL, CELL_SIZE, CELL_COUNT);

        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(WHITE);

            // Рисуем клетчатый фон
            for (int x = 0; x < CELL_COUNT; x++) {
                for (int y = 0; y < CELL_COUNT; y++) {
                    if ((x + y) % 2 == 0) {
                        DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, Color{230, 255, 230, 255});
                    } else {
                        DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, Color{220, 245, 220, 255});
                    }
                }
            }

            if (game.update() == StateGame::GAME_OVER) {
                char final_score[64];
                sprintf(final_score, "Game Over! Current score: %lu", game.get_score());

                int text_width = MeasureText(final_score, 30);
                DrawText(final_score, 0, 0, 40, BLACK);

                EndDrawing();
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            }

            EndDrawing();
        }
        CloseAudioDevice();

        CloseWindow();
    } catch (std::exception const& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        CloseAudioDevice();
    }
    return 0;
}
