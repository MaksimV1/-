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

    // �������� ��������� �����
    SnakeGame::StartScreen^ startScreen = gcnew SnakeGame::StartScreen();
     
    // ������ ����
    if (startScreen->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        // �������� ���������
        SnakeGame::GameSettings^ settings = startScreen->Settings;

        // ������� � ��������� ����
        SnakeGame::GameForm^ gameForm = gcnew SnakeGame::GameForm(settings);
        Application::Run(gameForm);
    }
    return 0;
}