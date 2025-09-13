#include "game.hpp"

Game::Game(double interval_update, uint64_t cell_size, uint64_t cell_count) : m_snake{interval_update, cell_size}, m_food{cell_size, cell_count} {}
void Game::update() {
    check_catch(m_snake.head(), m_food.position());
    m_food.draw();
    m_snake.draw();
}
void Game::check_catch(Vector2 head_snake, Vector2 food) {
    if (Vector2Equals(head_snake, food)) {
        m_food.move_new_position();
        while (m_snake.check_food_placement(m_food.position()) != Placement::GOOD) {
            m_food.move_new_position();
        }
        m_snake.change_state(State::INCREASE);
    }
}