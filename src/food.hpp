#pragma once
#include <raylib-cpp.hpp>

class Food {
   public:
    explicit Food(uint64_t cell_size, uint64_t cell_count);
    ~Food() = default;

    void draw() const;
    Vector2 position() const;
    void move_new_position();

   private:
    void generate_random_position();

    Vector2 m_position;        // 8
    uint64_t m_cell_size = 0;  // 8
    uint64_t m_cell_count = 0; // 8

    static_assert(sizeof m_position == 8);
    static_assert(sizeof m_cell_size == 8);
    static_assert(sizeof m_cell_count == 8);
};