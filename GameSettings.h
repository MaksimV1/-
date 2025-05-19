#pragma once

namespace SnakeGame 
{
    // ��� �����
    public enum class MapGenerationType 
    {
        Classic,    // ������� ���������
        Random,     // ���������
        Maze,       // ��������
        Islands     // �������
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
            // ����������� ���������
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
            // ���������������� ���������
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