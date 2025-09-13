#pragma once

#include "food.hpp"
#include "snake.hpp"

/**
 * @brief Перечисление состояний игры
 */
enum class StateGame : uint8_t { RUNNING, GAME_OVER };

/**
 * @brief Класс, представляющий основную логику игры
 *
 * Этот класс координирует взаимодействие между змейкой и едой,
 * обрабатывает логику игры и управляет звуковыми эффектами
 */
struct Game {
    /**
     * @brief Конструктор игры
     * @param interval_update Интервал обновления положения змейки в миллисекундах
     * @param cell_size Размер ячейки игрового поля в пикселях
     * @param cell_count Количество ячеек по одному измерению игрового поля
     */
    explicit Game(double interval_update, uint64_t cell_size, uint64_t cell_count);
    ~Game();

    /**
     * @brief Обновляет состояние игры
     * @return Текущее состояние игры
     */
    StateGame update();

    /**
     * @brief Проверяет, съела ли змейка еду
     * @param head_snake Координаты головы змейки
     * @param food Координаты еды
     */
    void check_catch(Vector2 head_snake, Vector2 food);

    Snake m_snake;     // 168
    Sound m_eat_sound; // 40
    Food m_food;       // 24

    static_assert(sizeof m_snake == 168);
    static_assert(sizeof m_food == 48);
    static_assert(sizeof m_eat_sound == 40);
};