#pragma once

#include "food.hpp"
#include "snake.hpp"

enum class StateGame : uint8_t { RUNNING, GAME_OVER };

struct Game {
    explicit Game(double interval_update, uint64_t cell_size, uint64_t cell_count);
    ~Game();

    StateGame update();
    void check_catch(Vector2 head_snake, Vector2 food);

    Snake m_snake;
    Food m_food;
    Sound m_eat_sound; // 40

    static_assert(sizeof m_eat_sound == 40);
};