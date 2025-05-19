#include "pch.h"
#include "GameForm.h"
#include "StartScreen.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Показать стартовый экран
    SnakeGame::StartScreen^ startScreen = gcnew SnakeGame::StartScreen();
     
    // Начать игру
    if (startScreen->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        // Получить настройки
        SnakeGame::GameSettings^ settings = startScreen->Settings;

        // Создать и запустить игру
        SnakeGame::GameForm^ gameForm = gcnew SnakeGame::GameForm(settings);
        Application::Run(gameForm);
    }
    return 0;
}