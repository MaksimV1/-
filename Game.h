#pragma once
#include "Snake.h"
#include "Food.h"
#include "WallManager.h"
#include "GameSettings.h"

namespace SnakeGame 
{
    public ref class Game 
    {
    private:
        Snake^ snake;
        Food^ food;
        WallManager^ wallManager;
        GameSettings^ settings;
        bool gameOver;
        int score;

    public:
        Game(GameSettings^ gameSettings) 
        {
            this->settings = gameSettings;
            InitializeGame();
        }

        property bool GameOver 
        {
            bool get() { return gameOver; }
        }

        property int Score 
        {
            int get() { return score; }
        }

        property Snake^ GameSnake 
        {
            Snake^ get() { return snake; }
        }

        property Food^ GameFood 
        {
            Food^ get() { return food; }
        }

        property WallManager^ GameWalls 
        {
            WallManager^ get() { return wallManager; }
        }

        void InitializeGame() 
        {
            // Создание объектов игры
            snake = gcnew Snake(settings->Width / 2, settings->Height / 2, 3, settings->GridSize);
            wallManager = gcnew WallManager(settings->Width, settings->Height, settings->GridSize,
                settings->MapType, settings->ObstacleDensity);
            food = gcnew Food(settings->Width, settings->Height, settings->GridSize);

            // Создание еды
            food->Generate(snake, wallManager);

            // Перезагрузка
            gameOver = false;
            score = 0;
        }

        void SetDirection(Direction direction) 
        {
            snake->CurrentDirection = direction;
        }

        void Update() 
        {
            if (gameOver)
                return;

            // Проверка еды
            bool grow = food->IsEatenBy(snake);

            if (grow) 
            {
                score++;
                food->Generate(snake, wallManager);
            }

            // Движение
            snake->Move(grow);

            // Проверка столкновений
            if (snake->CollidesWithSelf() || wallManager->CollidesWithWall(snake->Head)) 
            {
                gameOver = true;
            }
        }

        void Restart() 
        {
            InitializeGame();
        }
    };
}