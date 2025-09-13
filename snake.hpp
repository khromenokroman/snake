#pragma once
#include <chrono>
#include <deque>
#include <raylib-cpp.hpp>

enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };
enum class Placement : uint8_t { GOOD, BAD };
enum class State : uint8_t { INCREASE, STABLE };

class Snake {
   public:
    explicit Snake(double interval_update, uint64_t cell_size)
        : m_body{{6, 2}, {5, 2}, {4, 2}}, m_last_time{std::chrono::steady_clock::now()}, m_interval_update{interval_update}, m_cell_size{cell_size} {
        change_direction(Direction::RIGHT);
    }
    ~Snake() = default;

    void draw() {
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

    Vector2 head() const { return m_body.at(0); }

    Placement check_food_placement(Vector2 const& food) const {
        if (Vector2Equals(m_body.at(0), food)) {
            return Placement::BAD;
        }

        return Placement::GOOD;
    }

    void change_state(State state) { m_state = state; }

   private:
    void move() {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_time).count() > m_interval_update) {
            m_body.pop_back();
            m_body.push_front(Vector2Add(m_body.at(0), m_direction));
            m_last_time = now;
        }
    }
    void change_direction(Direction direction) {
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

    void process_keymap_user() {
        if (IsKeyDown(KEY_UP) && m_direction.y != 1) {
            change_direction(Direction::UP);
        }
        if (IsKeyDown(KEY_DOWN) && m_direction.y != -1) {
            change_direction(Direction::DOWN);
        }
        if (IsKeyDown(KEY_LEFT) && m_direction.x != 1) {
            change_direction(Direction::LEFT);
        }
        if (IsKeyDown(KEY_RIGHT) && m_direction.x != -1) {
            change_direction(Direction::RIGHT);
        }
    }

    std::deque<Vector2> m_body;                        // 80
    Vector2 m_direction;                               // 8
    std::chrono::steady_clock::time_point m_last_time; // 8
    double m_interval_update;                          // 8
    uint64_t m_cell_size = 0;                          // 8
    State m_state{State::STABLE};                      // 1

    static_assert(sizeof m_body == 80);
    static_assert(sizeof m_direction == 8);
    static_assert(sizeof m_last_time == 8);
};