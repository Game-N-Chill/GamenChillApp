
#pragma once

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

#include "Shared.hpp"
#include "GUI/Tools/GroupBox.hpp"
#include "GUI/Tools/Browser.hpp"
#include "GUI/Tools/Window.hpp"
#include "GUI/Tools/Randomizer.hpp"
#include "GUI/Windows/Common/Common.hpp"

namespace GNCApp::GUI::Windows
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

} // namespace GNCApp::GUI::Windows
