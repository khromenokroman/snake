#pragma once
#include <raylib-cpp.hpp>

/**
 * @brief Класс, представляющий еду в игре
 *
 * Этот класс управляет размещением и отображением еды на игровом поле
 */
class Food {
   public:
    /**
     * @brief Конструктор еды
     * @param cell_size Размер ячейки игрового поля в пикселях
     * @param cell_count Количество ячеек по одному измерению игрового поля
     */
    explicit Food(uint64_t cell_size, uint64_t cell_count);
    ~Food() = default;

    /**
     * @brief Отрисовывает еду на игровом поле
     */
    void draw() const;

    /**
     * @brief Возвращает текущие координаты еды
     * @return Vector2 Координаты еды
     */
    Vector2 position() const;

    /**
     * @brief Перемещает еду на новую случайную позицию
     */
    void move_new_position();

   private:
    /**
     * @brief Генерирует случайную позицию для еды
     */
    void generate_random_position();

    Vector2 m_position;        // 8
    uint64_t m_cell_size = 0;  // 8
    uint64_t m_cell_count = 0; // 8

    static_assert(sizeof m_position == 8);
    static_assert(sizeof m_cell_size == 8);
    static_assert(sizeof m_cell_count == 8);
};