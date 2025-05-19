#pragma once

namespace SnakeGame {
    // Направление движения змеи
    public enum class Direction { Up, Down, Left, Right };

    // Тип клетки
    public enum class CellType { Empty, Wall, Snake, Food };
}