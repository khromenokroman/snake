#pragma once
#include <raylib-cpp.hpp>

class Food {
   public:
    explicit Food(uint64_t cell_size, uint64_t cell_count) : m_position{0, 0}, m_cell_size{cell_size}, m_cell_count{cell_count} {
        generate_random_position();
    }

    void draw() { DrawRectangle(m_position.x * m_cell_size, m_position.y * m_cell_size, m_cell_size, m_cell_size, BLACK); }
    Vector2 position() const { return m_position; }
    void move_new_position() { generate_random_position(); }
   private:
    void generate_random_position() {
        m_position.x = GetRandomValue(0, m_cell_count-1);
        m_position.y = GetRandomValue(0, m_cell_count-1);
    }

    Vector2 m_position;        // 8
    uint64_t m_cell_size = 0;  // 8
    uint64_t m_cell_count = 0; // 8

    static_assert(sizeof m_position == 8);
    static_assert(sizeof m_cell_size == 8);
    static_assert(sizeof m_cell_count == 8);
};