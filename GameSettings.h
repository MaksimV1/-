#pragma once

namespace SnakeGame 
{
    // Тип карты
    public enum class MapGenerationType 
    {
        Classic,    // Заранее созданная
        Random,     // Случайная
        Maze,       // Лабиринт
        Islands     // Острова
    };

    public enum class ControlScheme 
    {
        ArrowKeys,
        WASD
    };

    public ref class GameSettings 
    {
    public:
        int Width;
        int Height;
        int GridSize;
        int GameSpeed;
        MapGenerationType MapType;
        int ObstacleDensity;
        ControlScheme PreferredControls;

        GameSettings() 
        {
            // Стандартные настройки
            Width = 600;
            Height = 600;
            GridSize = 20;
            GameSpeed = 100;
            MapType = MapGenerationType::Classic;
            ObstacleDensity = 5;
            PreferredControls = ControlScheme::ArrowKeys;
        }

        GameSettings(int width, int height, int gridSize, int gameSpeed,
            MapGenerationType mapType, int obstacleDensity, ControlScheme controls) 
        {
            // Пользовательские настройки
            Width = width;
            Height = height;
            GridSize = gridSize;
            GameSpeed = gameSpeed;
            MapType = mapType;
            ObstacleDensity = obstacleDensity;
            PreferredControls = controls;
        }
    };
}