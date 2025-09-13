#pragma once

#include "food.hpp"
#include "snake.hpp"

struct Game {
    explicit Game(double interval_update, uint64_t cell_size, uint64_t cell_count)
        : m_snake{interval_update, cell_size}, m_food{cell_size, cell_count} {}

    void update() {
        check_catch(m_snake.head(), m_food.position());
        m_food.draw();
        m_snake.draw();
    }

    void check_catch(Vector2 head_snake, Vector2 food) {
        if (Vector2Equals(head_snake, food)) {
            m_food.move_new_position();
            while (m_snake.check_food_placement(m_food.position()) != Placement::GOOD) {
                m_food.move_new_position();
                std::cout << "while" << std::endl;
            }
            m_snake.change_state(State::INCREASE);
            std::cout << "position food: " << food.x << " " << food.y << std::endl;
        }
    }

    Snake m_snake;
    Food m_food;
};