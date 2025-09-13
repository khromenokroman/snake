#include "food.hpp"

Food::Food(uint64_t cell_size, uint64_t cell_count) : m_position{0, 0}, m_cell_size{cell_size}, m_cell_count{cell_count} {
    generate_random_position();
}

void Food::draw() { DrawRectangle(m_position.x * m_cell_size, m_position.y * m_cell_size, m_cell_size, m_cell_size, BLACK); }

Vector2 Food::position() const { return m_position; }

void Food::move_new_position() { generate_random_position(); }

void Food::generate_random_position() {
    m_position.x = GetRandomValue(0, m_cell_count - 1);
    m_position.y = GetRandomValue(0, m_cell_count - 1);
}