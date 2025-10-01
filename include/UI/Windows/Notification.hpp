
#pragma once

#include <iostream>
#include <memory>
#include <array>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSoundEffect>
#include <QPushButton>

#include "UI/Tools/GroupBox.hpp"
#include "UI/Tools/Browser.hpp"
#include "UI/Tools/Window.hpp"
#include "UI/Tools/Randomizer.hpp"
#include "UI/Windows/Shared.hpp"
#include "Data/Data.hpp"

namespace GNCApp::UI::Windows
{

    #define PATH_DEFAULT_NOTIFICATION_SOUND     "assets/Sounds/SE_SYS_BTN_OK.wav"

class Notification : public Tools::Window
{
    Q_OBJECT

    public:
        Notification(const QString &title, const QString &subtitle, const QString &soundPath = PATH_DEFAULT_NOTIFICATION_SOUND, QWidget *parent = nullptr);

        static void callbackOpenDirectory();

    private:
        QHBoxLayout *_infoLayout;
        QLabel *_icon;
        QLabel *_text;
        QSoundEffect _sound;
};

}
