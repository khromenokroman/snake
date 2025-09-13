#include <chrono>
#include <deque>
#include <iostream>

#include "raylib-cpp.hpp"

uint64_t cell_size = 30;
uint64_t cell_count = 25;

struct Snake {
    Snake(double interval_update) : m_body{{4, 2}, {5, 2}, {6, 2}}, m_last_time{std::chrono::steady_clock::now()} {}

    void draw() {
        for (auto const& elem_body : m_body) {
            Rectangle segment{elem_body.x * cell_size, elem_body.y * cell_size, static_cast<float>(cell_size), static_cast<float>(cell_size)};
            DrawRectangleRounded(segment, 0.5, 6, BLACK);
        }
    }
    void move() {
        m_body.pop_back();
        m_body.push_front(Vector2Add(m_body.at(0), m_direction));
    }

    std::deque<Vector2> m_body;                        // 80
    Vector2 m_direction{1, 0};                         // 8
    std::chrono::steady_clock::time_point m_last_time; // 8
    double m_interval_update = 200;                    // 8

    static_assert(sizeof m_body == 80);
    static_assert(sizeof m_direction == 8);
    static_assert(sizeof m_last_time == 8);
};

struct Food {
    Food() : position{0, 0} { generate_random_position(); }
    explicit Food(float x, float y) : position{x, y} {}

    void draw() { DrawRectangle(position.x * cell_size, position.y * cell_size, cell_size, cell_size, BLACK); }
    void generate_random_position() {
        position.x = GetRandomValue(0, cell_count);
        position.y = GetRandomValue(0, cell_count);
    }
    Vector2 position; // 8

    static_assert(sizeof position == 8);
};

int main() {
    auto background_white = RAYWHITE;
    auto background_eat = BLACK;

    InitWindow(cell_size * cell_count, cell_size * cell_count, "Snake");
    SetTargetFPS(60);

    Food food;
    Snake snake;

    while (!WindowShouldClose()) {
        BeginDrawing();

        food.draw();
        snake.move();
        snake.draw();

        ClearBackground(background_white);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
