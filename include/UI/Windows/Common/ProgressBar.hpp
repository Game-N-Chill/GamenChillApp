
#pragma once

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

#include "Logic/ProgressTask.hpp"
#include "UI/Tools/GroupBox.hpp"
#include "UI/Tools/Browser.hpp"
#include "UI/Tools/Window.hpp"
#include "UI/Tools/Randomizer.hpp"
#include "UI/Windows/Common/Shared.hpp"

namespace GNCApp::UI::Windows
{

class ProgressBar : public Tools::Window
{
    Q_OBJECT

    public:
        ProgressBar(const QString &title, int delay = 100, QWidget *parent = nullptr);
        ~ProgressBar() = default;

        void loop();

        static void open(const QString &title, std::function<void()> funcLoadTask, std::function<void()> funcLogicExec, int delay = 100, QWidget *parent = nullptr);

    private:
        QLabel *_label;
        QProgressBar *_progressBar;

        QTimer *_timer;

};

} // namespace GNCApp::UI::Windows
