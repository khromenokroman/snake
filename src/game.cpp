#include "game.hpp"

Game::Game(double interval_update, uint64_t cell_size, uint64_t cell_count)
    : m_snake{interval_update, cell_size, cell_count}, m_food{cell_size, cell_count} {
    m_eat_sound = LoadSound("sounds/eat.wav");
}

Game::~Game() { UnloadSound(m_eat_sound); }

StateGame Game::update() {
    if (m_snake.game_over()) {
        return StateGame::GAME_OVER;
    }

    check_catch(m_snake.head(), m_food.position());
    m_food.draw();
    m_snake.draw();

    return StateGame::RUNNING;
}

void Game::check_catch(Vector2 head_snake, Vector2 food) {
    if (Vector2Equals(head_snake, food)) {
        PlaySound(m_eat_sound);
        m_food.move_new_position();
        while (m_snake.check_food_placement(m_food.position()) != Placement::GOOD) {
            m_food.move_new_position();
        }
        m_snake.change_state(State::INCREASE);
        ++m_score;
    }
}
uint64_t Game::get_score() const { return m_score; }

void Game::draw_score() const {
    char score_text[32];
    sprintf(score_text, "Счет: %lu", m_score);

    DrawText(score_text, 10, 10, 20, BLACK);
}
