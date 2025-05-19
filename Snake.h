#pragma once
#include "Point.h"
#include "Direction.h"
#include <list>

namespace SnakeGame {
    using namespace System::Collections::Generic;

    public ref class Snake {
    private:
        List<Point^>^ body;
        Direction direction;
        int gridSize;

    public:
        Snake(int startX, int startY, int initialLength, int gridSize) {
            this->gridSize = gridSize;
            body = gcnew List<Point^>();
            direction = Direction::Right;

            // Создание тела змеи
            for (int i = 0; i < initialLength; i++) {
                body->Add(gcnew Point(startX - i * gridSize, startY));
            }
        }

        property Point^ Head {
            Point^ get() { return body[0]; }
        }

        property List<Point^>^ Body {
            List<Point^>^ get() { return body; }
        }

        property Direction CurrentDirection {
            Direction get() { return direction; }
            void set(Direction value) {
                if ((value == Direction::Up && direction != Direction::Down) ||
                    (value == Direction::Down && direction != Direction::Up) ||
                    (value == Direction::Left && direction != Direction::Right) ||
                    (value == Direction::Right && direction != Direction::Left)) {
                    direction = value;
                }
            }
        }

        void Move(bool grow) {
            // Вычисление новой позиции головы
            int newX = Head->X;
            int newY = Head->Y;

            switch (direction) {
            case Direction::Up:
                newY -= gridSize;
                break;
            case Direction::Down:
                newY += gridSize;
                break;
            case Direction::Left:
                newX -= gridSize;
                break;
            case Direction::Right:
                newX += gridSize;
                break;
            }

            // Добавление иновой головы
            body->Insert(0, gcnew Point(newX, newY));

            // Удаление хвоста, если нет роста
            if (!grow && body->Count > 1) {
                body->RemoveAt(body->Count - 1);
            }
        }

        bool CollidesWithSelf() {
            // Проверка столкновений головы с телом
            for (int i = 1; i < body->Count; i++) {
                if (Head->Equals(body[i])) {
                    return true;
                }
            }
            return false;
        }

        bool Contains(Point^ point) {
            for each (Point ^ segment in body) {
                if (segment->Equals(point)) {
                    return true;
                }
            }
            return false;
        }
    };
}