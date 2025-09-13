#include "food.hpp"

Food::Food(uint64_t cell_size, uint64_t cell_count) : m_position{0, 0}, m_cell_size{cell_size}, m_cell_count{cell_count} {
    Image food_image = LoadImage("/usr/share/bitmaps/food.png");
    ImageResize(&food_image, m_cell_size, m_cell_size);
    m_texture = LoadTextureFromImage(food_image);
    UnloadImage(food_image);

    generate_random_position();
}
Food::~Food() { UnloadTexture(m_texture); }

void Food::draw() const { DrawTexture(m_texture, m_position.x * m_cell_size, m_position.y * m_cell_size, WHITE); }

Vector2 Food::position() const { return m_position; }

void Food::move_new_position() { generate_random_position(); }

void Food::generate_random_position() {
    m_position.x = GetRandomValue(0, m_cell_count - 1);
    m_position.y = GetRandomValue(0, m_cell_count - 1);
}