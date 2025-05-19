#pragma once
#include "Game.h"
#include "GameSettings.h"

namespace SnakeGame 
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class GameForm : public System::Windows::Forms::Form 
    {
    private:
        Game^ game;
        GameSettings^ settings;

        // Компоненты пользовательского интерфейса
        System::Windows::Forms::Timer^ gameTimer;
        System::ComponentModel::IContainer^ components;

    public:
        GameForm(GameSettings^ gameSettings) 
        {
            settings = gameSettings;
            InitializeComponent();
            game = gcnew Game(settings);
        }

    protected:
        ~GameForm() 
        {
            if (components) 
            {
                delete components;
            }
        }

    private:
        void InitializeComponent(void) 
        {
            this->components = gcnew System::ComponentModel::Container();
            this->gameTimer = gcnew System::Windows::Forms::Timer(this->components);
            this->SuspendLayout();

            // Игровое время
            this->gameTimer->Interval = settings->GameSpeed;
            this->gameTimer->Tick += gcnew System::EventHandler(this, &GameForm::GameTimerTick);
            this->gameTimer->Start();

            // Игровое окно
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(settings->Width, settings->Height);
            this->DoubleBuffered = true;
            this->Name = L"Snake Game";
            this->Text = L"Snake Game";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GameForm::OnPaint);
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::OnKeyDown);
            this->ResumeLayout(false);
        }

        void GameTimerTick(Object^ sender, EventArgs^ e) 
        {
            game->Update();

            if (game->GameOver) {
                gameTimer->Stop();
                MessageBox::Show("Game Over! Your score: " + game->Score, "Snake Game",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }

            this->Invalidate();
        }

        void OnPaint(Object^ sender, PaintEventArgs^ e) 
        {
            Graphics^ g = e->Graphics;

            // Задний фон
            g->Clear(Color::White);

            // Стены
            for each (Point ^ wall in game->GameWalls->Walls) {
                g->FillRectangle(Brushes::Gray, wall->X, wall->Y, settings->GridSize, settings->GridSize);
                g->DrawRectangle(Pens::Black, wall->X, wall->Y, settings->GridSize, settings->GridSize);
            }

            // Создание змеи
            for each (Point ^ segment in game->GameSnake->Body) {
                g->FillRectangle(Brushes::Green, segment->X, segment->Y, settings->GridSize, settings->GridSize);
                g->DrawRectangle(Pens::DarkGreen, segment->X, segment->Y, settings->GridSize, settings->GridSize);
            }

            // Еда
            g->FillEllipse(Brushes::Red, game->GameFood->Position->X, game->GameFood->Position->Y, settings->GridSize, settings->GridSize);

            // Счет
            g->DrawString("Score: " + game->Score, gcnew Drawing::Font("Arial", 12), Brushes::Black, 10, 10);

            // 
            g->DrawString("Controls: Arrow Keys or WASD | Space to Pause | R to Restart",
                gcnew Drawing::Font("Arial", 10), Brushes::DarkGray,
                10, settings->Height - 30);

            // Окончание игры
            if (game->GameOver) 
            {
                String^ gameOverText = "GAME OVER - Press R to Restart";
                Drawing::Font^ font = gcnew Drawing::Font("Arial", 20);
                SizeF textSize = g->MeasureString(gameOverText, font);
                g->DrawString(gameOverText, font, Brushes::Red,
                    (settings->Width - textSize.Width) / 2, (settings->Height - textSize.Height) / 2);
            }
        }

        void OnKeyDown(Object^ sender, KeyEventArgs^ e) 
        {
            // Начать заново
            if (game->GameOver && e->KeyCode == Keys::R) 
            {
                game->Restart();
                gameTimer->Start();
                return;
            }

            // Выбор управления
            switch (e->KeyCode) 
            {
            case Keys::Up:
            case Keys::W:
                game->SetDirection(Direction::Up);
                break;
            case Keys::Down:
            case Keys::S:
                game->SetDirection(Direction::Down);
                break;
            case Keys::Left:
            case Keys::A:
                game->SetDirection(Direction::Left);
                break;
            case Keys::Right:
            case Keys::D:
                game->SetDirection(Direction::Right);
                break;
            case Keys::Space:
                // Пауза
                if (gameTimer->Enabled)
                    gameTimer->Stop();
                else if (!game->GameOver)
                    gameTimer->Start();
                break;
            }
        }
    };
}