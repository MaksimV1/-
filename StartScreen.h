#pragma once
#include "GameSettings.h"

namespace SnakeGame 
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class StartScreen : public System::Windows::Forms::Form 
    {
    private:
        // Компоненты пользовательского интерфейса
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::Label^ mapSizeLabel;
        System::Windows::Forms::ComboBox^ mapSizeComboBox;
        System::Windows::Forms::Label^ speedLabel;
        System::Windows::Forms::TrackBar^ speedTrackBar;
        System::Windows::Forms::Label^ speedValueLabel;
        System::Windows::Forms::Label^ mapTypeLabel;
        System::Windows::Forms::ComboBox^ mapTypeComboBox;
        System::Windows::Forms::Label^ densityLabel;
        System::Windows::Forms::TrackBar^ densityTrackBar;
        System::Windows::Forms::Label^ densityValueLabel;
        System::Windows::Forms::Label^ controlsLabel;
        System::Windows::Forms::ComboBox^ controlsComboBox;
        System::Windows::Forms::Button^ startButton;
        System::ComponentModel::Container^ components;

        // Настройки
        GameSettings^ settings;

    public:
        StartScreen() 
        {
            // Стартовый экран
            InitializeComponent();
            settings = gcnew GameSettings();
            UpdateSpeedLabel();
            UpdateDensityLabel();
        }

        property GameSettings^ Settings 
        {
            GameSettings^ get() { return settings; }
        }

    protected:
        ~StartScreen() 
        {
            if (components) 
            {
                delete components;
            }
        }

    private:
        void InitializeComponent() 
        {
            this->components = gcnew System::ComponentModel::Container();
            this->titleLabel = gcnew System::Windows::Forms::Label();
            this->mapSizeLabel = gcnew System::Windows::Forms::Label();
            this->mapSizeComboBox = gcnew System::Windows::Forms::ComboBox();
            this->speedLabel = gcnew System::Windows::Forms::Label();
            this->speedTrackBar = gcnew System::Windows::Forms::TrackBar();
            this->speedValueLabel = gcnew System::Windows::Forms::Label();
            this->mapTypeLabel = gcnew System::Windows::Forms::Label();
            this->mapTypeComboBox = gcnew System::Windows::Forms::ComboBox();
            this->densityLabel = gcnew System::Windows::Forms::Label();
            this->densityTrackBar = gcnew System::Windows::Forms::TrackBar();
            this->densityValueLabel = gcnew System::Windows::Forms::Label();
            this->controlsLabel = gcnew System::Windows::Forms::Label();
            this->controlsComboBox = gcnew System::Windows::Forms::ComboBox();
            this->startButton = gcnew System::Windows::Forms::Button();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->speedTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->densityTrackBar))->BeginInit();
            this->SuspendLayout();

            // Заголовок
            this->titleLabel->AutoSize = true;
            this->titleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->titleLabel->Location = System::Drawing::Point(100, 20);
            this->titleLabel->Name = L"titleLabel";
            this->titleLabel->Size = System::Drawing::Size(200, 30);
            this->titleLabel->TabIndex = 0;
            this->titleLabel->Text = L"Snake Game";
            this->titleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // Размер карты
            this->mapSizeLabel->AutoSize = true;
            this->mapSizeLabel->Location = System::Drawing::Point(50, 80);
            this->mapSizeLabel->Name = L"mapSizeLabel";
            this->mapSizeLabel->Size = System::Drawing::Size(100, 20);
            this->mapSizeLabel->TabIndex = 1;
            this->mapSizeLabel->Text = L"Map Size:";

            this->mapSizeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->mapSizeComboBox->FormattingEnabled = true;
            this->mapSizeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) 
            {
                L"Small (400x400)",
                    L"Medium (600x600)",
                    L"Large (800x800)"
            });
            this->mapSizeComboBox->Location = System::Drawing::Point(160, 80);
            this->mapSizeComboBox->Name = L"mapSizeComboBox";
            this->mapSizeComboBox->Size = System::Drawing::Size(180, 24);
            this->mapSizeComboBox->TabIndex = 2;
            this->mapSizeComboBox->SelectedIndex = 1; // Default to Medium
            this->mapSizeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &StartScreen::MapSizeComboBox_SelectedIndexChanged);

            // Скорость игры
            this->speedLabel->AutoSize = true;
            this->speedLabel->Location = System::Drawing::Point(50, 120);
            this->speedLabel->Name = L"speedLabel";
            this->speedLabel->Size = System::Drawing::Size(100, 20);
            this->speedLabel->TabIndex = 3;
            this->speedLabel->Text = L"Game Speed:";

            this->speedTrackBar->Location = System::Drawing::Point(160, 120);
            this->speedTrackBar->Name = L"speedTrackBar";
            this->speedTrackBar->Size = System::Drawing::Size(180, 45);
            this->speedTrackBar->TabIndex = 4;
            this->speedTrackBar->Minimum = 1;
            this->speedTrackBar->Maximum = 10;
            this->speedTrackBar->Value = 5; // Default value
            this->speedTrackBar->TickStyle = System::Windows::Forms::TickStyle::Both;
            this->speedTrackBar->ValueChanged += gcnew System::EventHandler(this, &StartScreen::SpeedTrackBar_ValueChanged);

            this->speedValueLabel->AutoSize = true;
            this->speedValueLabel->Location = System::Drawing::Point(350, 120);
            this->speedValueLabel->Name = L"speedValueLabel";
            this->speedValueLabel->Size = System::Drawing::Size(50, 20);
            this->speedValueLabel->TabIndex = 5;
            this->speedValueLabel->Text = L"Normal";

            // Тип карты
            this->mapTypeLabel->AutoSize = true;
            this->mapTypeLabel->Location = System::Drawing::Point(50, 170);
            this->mapTypeLabel->Name = L"mapTypeLabel";
            this->mapTypeLabel->Size = System::Drawing::Size(100, 20);
            this->mapTypeLabel->TabIndex = 6;
            this->mapTypeLabel->Text = L"Map Type:";

            this->mapTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->mapTypeComboBox->FormattingEnabled = true;
            this->mapTypeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) 
            {
                L"Classic",
                    L"Random",
                    L"Maze",
                    L"Islands"
            });
            this->mapTypeComboBox->Location = System::Drawing::Point(160, 170);
            this->mapTypeComboBox->Name = L"mapTypeComboBox";
            this->mapTypeComboBox->Size = System::Drawing::Size(180, 24);
            this->mapTypeComboBox->TabIndex = 7;
            this->mapTypeComboBox->SelectedIndex = 0; // Default to Classic
            this->mapTypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &StartScreen::MapTypeComboBox_SelectedIndexChanged);

            // Количество препятствий
            this->densityLabel->AutoSize = true;
            this->densityLabel->Location = System::Drawing::Point(50, 220);
            this->densityLabel->Name = L"densityLabel";
            this->densityLabel->Size = System::Drawing::Size(100, 20);
            this->densityLabel->TabIndex = 8;
            this->densityLabel->Text = L"Wall Density:";

            this->densityTrackBar->Location = System::Drawing::Point(160, 220);
            this->densityTrackBar->Name = L"densityTrackBar";
            this->densityTrackBar->Size = System::Drawing::Size(180, 45);
            this->densityTrackBar->TabIndex = 9;
            this->densityTrackBar->Minimum = 1;
            this->densityTrackBar->Maximum = 10;
            this->densityTrackBar->Value = 5; // Default value
            this->densityTrackBar->TickStyle = System::Windows::Forms::TickStyle::Both;
            this->densityTrackBar->ValueChanged += gcnew System::EventHandler(this, &StartScreen::DensityTrackBar_ValueChanged);

            this->densityValueLabel->AutoSize = true;
            this->densityValueLabel->Location = System::Drawing::Point(350, 220);
            this->densityValueLabel->Name = L"densityValueLabel";
            this->densityValueLabel->Size = System::Drawing::Size(50, 20);
            this->densityValueLabel->TabIndex = 10;
            this->densityValueLabel->Text = L"Medium";

            this->controlsLabel->AutoSize = true;
            this->controlsLabel->Location = System::Drawing::Point(50, 270);
            this->controlsLabel->Name = L"controlsLabel";
            this->controlsLabel->Size = System::Drawing::Size(100, 20);
            this->controlsLabel->TabIndex = 11;
            this->controlsLabel->Text = L"Controls:";

            // Управление
            this->controlsComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->controlsComboBox->FormattingEnabled = true;
            this->controlsComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) 
            {
                L"Arrow Keys",
                    L"WASD"
            });
            this->controlsComboBox->Location = System::Drawing::Point(160, 270);
            this->controlsComboBox->Name = L"controlsComboBox";
            this->controlsComboBox->Size = System::Drawing::Size(180, 24);
            this->controlsComboBox->TabIndex = 12;
            this->controlsComboBox->SelectedIndex = 0; // Default to Arrow Keys

            // Начать игру
            this->startButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->startButton->Location = System::Drawing::Point(150, 320);
            this->startButton->Name = L"startButton";
            this->startButton->Size = System::Drawing::Size(100, 40);
            this->startButton->TabIndex = 13;
            this->startButton->Text = L"Start Game";
            this->startButton->UseVisualStyleBackColor = true;
            this->startButton->Click += gcnew System::EventHandler(this, &StartScreen::StartButton_Click);

            // Стартовый экран
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(400, 390);
            this->Controls->Add(this->titleLabel);
            this->Controls->Add(this->mapSizeLabel);
            this->Controls->Add(this->mapSizeComboBox);
            this->Controls->Add(this->speedLabel);
            this->Controls->Add(this->speedTrackBar);
            this->Controls->Add(this->speedValueLabel);
            this->Controls->Add(this->mapTypeLabel);
            this->Controls->Add(this->mapTypeComboBox);
            this->Controls->Add(this->densityLabel);
            this->Controls->Add(this->densityTrackBar);
            this->Controls->Add(this->densityValueLabel);
            this->Controls->Add(this->controlsLabel);
            this->Controls->Add(this->controlsComboBox);
            this->Controls->Add(this->startButton);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->Name = L"StartScreen";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Snake Game - Settings";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->speedTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->densityTrackBar))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void MapSizeComboBox_SelectedIndexChanged(Object^ sender, EventArgs^ e) 
        {
            switch (mapSizeComboBox->SelectedIndex) 
            {
            case 0: // Маленькая
                settings->Width = 400;
                settings->Height = 400;
                break;
            case 1: // Средняя
                settings->Width = 600;
                settings->Height = 600;
                break;
            case 2: // Большая
                settings->Width = 800;
                settings->Height = 800;
                break;
            }
        }

        void SpeedTrackBar_ValueChanged(Object^ sender, EventArgs^ e) 
        {
            settings->GameSpeed = 200 - (speedTrackBar->Value - 1) * 15;
            UpdateSpeedLabel();
        }

        void UpdateSpeedLabel() 
        {
            String^ speedText;

            if (speedTrackBar->Value <= 3)
                speedText = "Slow";
            else if (speedTrackBar->Value <= 7)
                speedText = "Normal";
            else
                speedText = "Fast";

            speedValueLabel->Text = speedText;
        }

        void MapTypeComboBox_SelectedIndexChanged(Object^ sender, EventArgs^ e) 
        {
            settings->MapType = (MapGenerationType)mapTypeComboBox->SelectedIndex;

            bool enableDensity = settings->MapType != MapGenerationType::Classic;
            densityLabel->Enabled = enableDensity;
            densityTrackBar->Enabled = enableDensity;
            densityValueLabel->Enabled = enableDensity;
        }

        void DensityTrackBar_ValueChanged(Object^ sender, EventArgs^ e) 
        {
            settings->ObstacleDensity = densityTrackBar->Value;
            UpdateDensityLabel();
        }

        void UpdateDensityLabel() {
            String^ densityText;

            if (densityTrackBar->Value <= 3)
                densityText = "Low";
            else if (densityTrackBar->Value <= 7)
                densityText = "Medium";
            else
                densityText = "High";

            densityValueLabel->Text = densityText;
        }

        void StartButton_Click(Object^ sender, EventArgs^ e) {
            settings->PreferredControls = (ControlScheme)controlsComboBox->SelectedIndex;

            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    };
}