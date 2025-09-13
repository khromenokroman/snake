#pragma once
#include <chrono>
#include <cstdint>
#include <deque>
#include <raylib-cpp.hpp>

/**
 * @brief Перечисление направлений движения змейки
 */
enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };

/**
 * @brief Перечисление для результатов проверки размещения еды
 */
enum class Placement : uint8_t { GOOD, BAD };

/**
 * @brief Перечисление состояний змейки
 */
enum class State : uint8_t { INCREASE, STABLE };

/**
 * @brief Перечисление состояния клавиш управления
 */
enum class StateKeyCap : uint8_t { UP, DOWN };

/**
 * @brief Класс, представляющий змейку в игре
 *
 * Этот класс управляет логикой движения змейки, обработкой ввода
 * и проверкой столкновений с границами и собственным телом.
 */
class Snake {
   public:
    /**
     * @brief Конструктор змейки
     * @param interval_update Интервал обновления положения змейки в миллисекундах
     * @param cell_size Размер ячейки игрового поля в пикселях
     * @param cell_count Количество ячеек по одному измерению игрового поля
     */
    explicit Snake(double interval_update, uint64_t cell_size, uint64_t cell_count, uint64_t offset);
    ~Snake();

    /**
     * @brief Отрисовывает змейку
     *
     * Этот метод также обрабатывает пользовательский ввод и перемещение змейки
     */
    void draw();

    /**
     * @brief Возвращает координаты головы змейки
     * @return Vector2 Координаты головы змейки
     */
    Vector2 head() const;

    /**
     * @brief Проверяет, может ли еда быть размещена в указанных координатах
     * @param food Координаты еды для проверки
     * @return Placement::GOOD если размещение возможно, Placement::BAD в противном случае
     */
    Placement check_food_placement(Vector2 const& food) const;

    /**
     * @brief Изменяет состояние змейки
     * @param state Новое состояние
     */
    void change_state(State state);

    /**
     * @brief Проверяет, закончилась ли игра
     * @return true если игра окончена, false в противном случае
     */
    bool game_over() const;

   private:
    /**
     * @brief Перемещает змейку на следующую позицию
     *
     * Этот метод обновляет положение змейки на основе текущего направления
     * и проверяет столкновения с границами и собственным телом
     */
    void move();

    /**
     * @brief Изменяет направление движения змейки
     * @param direction Новое направление
     */
    void change_direction(Direction direction);

    /**
     * @brief Обрабатывает ввод пользователя для управления змейкой
     */
    void process_keymap_user();

    std::deque<Vector2> m_body;                        // 80
    Sound m_game_over_sound;                           // 40
    Vector2 m_direction;                               // 8
    std::chrono::steady_clock::time_point m_last_time; // 8
    double m_interval_update;                          // 8
    uint64_t m_cell_size = 0;                          // 8
    uint64_t m_cell_count = 0;                         // 8
    uint64_t m_offset = 0;                             // 8
    State m_state{State::STABLE};                      // 1
    StateKeyCap m_state_keycap{StateKeyCap::UP};       // 1
    bool m_game_over{false};                           // 1

    static_assert(sizeof m_body == 80);
    static_assert(sizeof m_game_over_sound == 40);
    static_assert(sizeof m_direction == 8);
    static_assert(sizeof m_last_time == 8);
};