#pragma once
#include "Point.h"
#include "Snake.h"
#include "WallManager.h"

namespace SnakeGame {
    using namespace System;

    public ref class Food {
    private:
        Point^ position;
        int gridSize;
        int width;
        int height;

    public:
        Food(int width, int height, int gridSize) {
            this->gridSize = gridSize;
            this->width = width;
            this->height = height;
            position = gcnew Point(0, 0);
        }

        property Point^ Position {
            Point^ get() { return position; }
        }

        void Generate(Snake^ snake, WallManager^ wallManager) {
            Random^ rand = gcnew Random();
            int x, y;
            bool validPosition;

            do {
                validPosition = true;
                x = rand->Next(1, (width / gridSize) - 1) * gridSize;
                y = rand->Next(1, (height / gridSize) - 1) * gridSize;

                // Проверка не находится ли еда на теле змеи
                for each (Point ^ segment in snake->Body) {
                    if (segment->X == x && segment->Y == y) {
                        validPosition = false;
                        break;
                    }
                }

                // Проверка не находится ли еда на стене
                if (wallManager->IsWall(x, y)) {
                    validPosition = false;
                }

            } while (!validPosition);

            position = gcnew Point(x, y);
        }

        bool IsEatenBy(Snake^ snake) 
        {
            if (snake->Head->X == position->X)
            {
                if (snake->Head->Y == position->Y)
                {
                    return true;
                }
            }
            return false;
        }
    };
}