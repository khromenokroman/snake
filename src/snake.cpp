#include "snake.hpp"
Snake::Snake(double interval_update, uint64_t cell_size, uint64_t cell_count)
    : m_body{{6, 2}, {5, 2}, {4, 2}},
      m_last_time{std::chrono::steady_clock::now()},
      m_interval_update{interval_update},
      m_cell_size{cell_size},
      m_cell_count{cell_count} {
    change_direction(Direction::RIGHT);
}
void Snake::draw() {
    process_keymap_user();
    if (m_state == State::INCREASE) {
        m_body.push_front(Vector2Add(m_body.at(0), m_direction));
        m_state = State::STABLE;
    } else {
        move();
    }

    for (auto const& elem_body : m_body) {
        Rectangle segment{elem_body.x * m_cell_size, elem_body.y * m_cell_size, static_cast<float>(m_cell_size), static_cast<float>(m_cell_size)};
        DrawRectangleRounded(segment, 0.5, 6, BLACK);
    }
}
Vector2 Snake::head() const { return m_body.at(0); }
Placement Snake::check_food_placement(Vector2 const& food) const {
    if (Vector2Equals(m_body.at(0), food)) {
        return Placement::BAD;
    }

    return Placement::GOOD;
}
void Snake::change_state(State state) { m_state = state; }
void Snake::move() {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_time).count() > m_interval_update) {
        m_body.pop_back();
        m_body.push_front(Vector2Add(m_body.at(0), m_direction));
        if (m_body.at(0).x == -1 || m_body.at(0).x == m_cell_count) {
            throw GameOver("Вышел за границу");
        }
        if (m_body.at(0).y == -1 || m_body.at(0).y == m_cell_count) {
            throw GameOver("Вышел за границу");
        }
        for (auto i = 2ull; i < m_body.size(); ++i) {
            if (Vector2Equals(m_body[i], m_body.at(0))) {
                throw GameOver("Врезался в себя");
            }
        }
        m_last_time = now;
        m_state_keycap = StateKeyCap::UP;
    }
}
void Snake::change_direction(Direction direction) {
    switch (direction) {
        case Direction::UP:
            m_direction = Vector2{0, -1};
            break;
        case Direction::DOWN:
            m_direction = Vector2{0, 1};
            break;
        case Direction::LEFT:
            m_direction = Vector2{-1, 0};
            break;
        case Direction::RIGHT:
            m_direction = Vector2{1, 0};
            break;
        default:
            throw std::runtime_error("Unknown direction");
    }
}
void Snake::process_keymap_user() {
    if (m_state_keycap == StateKeyCap::DOWN) {
        return;
    }

    bool key_was_pressed = false;

    if (IsKeyDown(KEY_UP) && m_direction.y != 1) {
        change_direction(Direction::UP);
        key_was_pressed = true;
    } else if (IsKeyDown(KEY_DOWN) && m_direction.y != -1) {
        change_direction(Direction::DOWN);
        key_was_pressed = true;
    } else if (IsKeyDown(KEY_LEFT) && m_direction.x != 1) {
        change_direction(Direction::LEFT);
        key_was_pressed = true;
    } else if (IsKeyDown(KEY_RIGHT) && m_direction.x != -1) {
        change_direction(Direction::RIGHT);
        key_was_pressed = true;
    }

    if (key_was_pressed) {
        m_state_keycap = StateKeyCap::DOWN;
    }
}