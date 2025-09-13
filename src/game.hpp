#pragma once

#include "food.hpp"
#include "snake.hpp"

struct Game {
    explicit Game(double interval_update, uint64_t cell_size, uint64_t cell_count);
    ~Game() = default;

    void update() ;
    void check_catch(Vector2 head_snake, Vector2 food);

    Snake m_snake;
    Food m_food;
};