#pragma once
#include "Point.h"
#include "GameSettings.h"

namespace SnakeGame {
    using namespace System;
    using namespace System::Collections::Generic;

    public ref class WallManager {
    private:
        List<Point^>^ walls;
        int gridSize;
        int width;
        int height;
        MapGenerationType mapType;
        int obstacleDensity;
        Random^ random;

    public:
        WallManager(int width, int height, int gridSize, MapGenerationType mapType, int obstacleDensity) {
            this->gridSize = gridSize;
            this->width = width;
            this->height = height;
            this->mapType = mapType;
            this->obstacleDensity = obstacleDensity;
            this->random = gcnew Random();
            walls = gcnew List<Point^>();
            GenerateMap();
        }

        property List<Point^>^ Walls {
            List<Point^>^ get() { return walls; }
        }

        void GenerateMap() {
            // Очистка
            walls->Clear();

            // Создание стен по краям
            AddBorderWalls();

            // Создание стен на карте
            switch (mapType) {
            case MapGenerationType::Classic:
                GenerateClassicMap();
                break;
            case MapGenerationType::Random:
                GenerateRandomMap();
                break;
            case MapGenerationType::Maze:
                GenerateMazeMap();
                break;
            case MapGenerationType::Islands:
                GenerateIslandsMap();
                break;
            }
        }

    private:
        void AddBorderWalls() {
            int maxX = width / gridSize;
            int maxY = height / gridSize;

            // Верхняя и нижняя граничные стены
            for (int x = 0; x < maxX; x++) {
                walls->Add(gcnew Point(x * gridSize, 0));
                walls->Add(gcnew Point(x * gridSize, (maxY - 1) * gridSize));
            }

            // Правая и левая граничные стены
            for (int y = 0; y < maxY; y++) {
                walls->Add(gcnew Point(0, y * gridSize));
                walls->Add(gcnew Point((maxX - 1) * gridSize, y * gridSize));
            }
        }

        // Классическая карта
        void GenerateClassicMap() {}

        // Случайная карта
        void GenerateRandomMap() {
            int maxX = width / gridSize - 1;
            int maxY = height / gridSize - 1;

            // Количество объектов
            int totalCells = (maxX - 1) * (maxY - 1);
            int numObstacles = (totalCells * obstacleDensity) / 100;
            numObstacles = numObstacles * obstacleDensity / 5;

            // Размещение
            for (int i = 0; i < numObstacles; i++) {
                int x, y;
                bool validPosition;

                do {
                    validPosition = true;
                    x = random->Next(2, maxX - 1);
                    y = random->Next(2, maxY - 1);

                    // Проверка позиций
                    if (IsWall(x * gridSize, y * gridSize)) {
                        validPosition = false;
                    }

                    // Проверка мест рядом
                    int centerX = width / (2 * gridSize);
                    int centerY = height / (2 * gridSize);
                    if (Math::Abs(x - centerX) < 3 && Math::Abs(y - centerY) < 3) {
                        validPosition = false;
                    }

                } while (!validPosition);

                walls->Add(gcnew Point(x * gridSize, y * gridSize));
            }
        }

        // Карта лабиринт
        void GenerateMazeMap() {
            int maxX = width / gridSize - 1;
            int maxY = height / gridSize - 1;

            // Сетка лабиринта
            array<bool, 2>^ visited = gcnew array<bool, 2>(maxX, maxY);

            // Инициализировать все ячейки как стены
            for (int x = 1; x < maxX; x++) {
                for (int y = 1; y < maxY; y++) {
                    // Пропустить центр
                    int centerX = width / (2 * gridSize);
                    int centerY = height / (2 * gridSize);
                    if (Math::Abs(x - centerX) < 3 && Math::Abs(y - centerY) < 3) {
                        continue;
                    }

                    // Расставить стены
                    if (x % 2 == 0 || y % 2 == 0) {
                        if (random->Next(10) < obstacleDensity) {
                            walls->Add(gcnew Point(x * gridSize, y * gridSize));
                        }
                    }
                }
            }

            // Пути между стенами
            int pathCount = (maxX * maxY) / (12 - obstacleDensity);

            for (int i = 0; i < pathCount; i++) {
                int startX = random->Next(2, maxX - 2);
                int startY = random->Next(2, maxY - 2);
                int length = random->Next(3, 8);
                bool horizontal = random->Next(2) == 0;

                if (horizontal) {
                    for (int j = 0; j < length && startX + j < maxX - 1; j++) {
                        RemoveWallAt((startX + j) * gridSize, startY * gridSize);
                    }
                }
                else {
                    for (int j = 0; j < length && startY + j < maxY - 1; j++) {
                        RemoveWallAt(startX * gridSize, (startY + j) * gridSize);
                    }
                }
            }
        }

        // Карта из островов
        void GenerateIslandsMap() {
            int maxX = width / gridSize - 1;
            int maxY = height / gridSize - 1;

            // Число островов
            int numIslands = 2 + obstacleDensity / 2; // 2-7

            for (int i = 0; i < numIslands; i++) {
                // Случайный центр островов
                int centerX = random->Next(5, maxX - 5);
                int centerY = random->Next(5, maxY - 5);

                int snakeCenterX = width / (2 * gridSize);
                int snakeCenterY = height / (2 * gridSize);
                if (Math::Abs(centerX - snakeCenterX) < 4 && Math::Abs(centerY - snakeCenterY) < 4) {
                    continue;
                }

                // Размер островов
                int size = 2 + obstacleDensity / 3; // 2-5

                // Генерация острова
                for (int x = -size; x <= size; x++) {
                    for (int y = -size; y <= size; y++) {
                        if (x * x + y * y <= size * size) {
                            int wallX = centerX + x;
                            int wallY = centerY + y;

                            // Проверка границ
                            if (wallX > 1 && wallX < maxX - 1 && wallY > 1 && wallY < maxY - 1) {
                                // Неправильная форма острова
                                if (random->Next(10) < 7) {
                                    walls->Add(gcnew Point(wallX * gridSize, wallY * gridSize));
                                }
                            }
                        }
                    }
                }
            }
        }

        void RemoveWallAt(int x, int y) {
            for (int i = walls->Count - 1; i >= 0; i--) {
                if (walls[i]->X == x && walls[i]->Y == y) {
                    walls->RemoveAt(i);
                    break;
                }
            }
        }

    public:
        bool IsWall(int x, int y) {
            for each (Point ^ wall in walls) {
                if (wall->X == x && wall->Y == y)
                    return true;
            } 
            return false;
        }

        bool CollidesWithWall(Point^ point) {
            return IsWall(point->X, point->Y);
        }
    };
}