#pragma once
#include <chrono>
#include <deque>
#include <raylib-cpp.hpp>

enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };
enum class Placement : uint8_t { GOOD, BAD };
enum class State : uint8_t { INCREASE, STABLE };
enum class StateKeyCap : uint8_t { UP, DOWN };

struct SnakeEx : std::runtime_error {
    using std::runtime_error::runtime_error;
};
struct GameOver final : SnakeEx {
    using SnakeEx::SnakeEx;
};

class Snake {
   public:
    explicit Snake(double interval_update, uint64_t cell_size, uint64_t cell_count);
    ~Snake();

    void draw();
    Vector2 head() const;
    Placement check_food_placement(Vector2 const& food) const;
    void change_state(State state);
    bool game_over() const;

   private:
    void move();
    void change_direction(Direction direction);
    void process_keymap_user();

    std::deque<Vector2> m_body;                        // 80
    Sound m_game_over_sound;                           // 40
    Vector2 m_direction;                               // 8
    std::chrono::steady_clock::time_point m_last_time; // 8
    double m_interval_update;                          // 8
    uint64_t m_cell_size = 0;                          // 8
    uint64_t m_cell_count = 0;                         // 8
    State m_state{State::STABLE};                      // 1
    StateKeyCap m_state_keycap{StateKeyCap::UP};       // 1
    bool m_game_over{false};                           // 1

    static_assert(sizeof m_body == 80);
    static_assert(sizeof m_game_over_sound == 40);
    static_assert(sizeof m_direction == 8);
    static_assert(sizeof m_last_time == 8);
};