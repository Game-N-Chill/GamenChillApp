
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
#include "UI/Windows/Common/Shared.hpp"
#include "Data/Data.hpp"
#include "Utils.hpp"

namespace GNCApp::UI::Windows
{

    #define PATH_DEFAULT_ICON                   ":/icons/info"
    #define PATH_DEFAULT_NOTIFICATION_SOUND     "assets/Sounds/SE_SYS_BTN_OK.wav"

class Notification : public Tools::Window
{
    Q_OBJECT

    public:
        Notification(const QString &title, const QString &subtitle, QWidget *parent = nullptr, QString iconPath = PATH_DEFAULT_ICON, const QString &soundPath = PATH_DEFAULT_NOTIFICATION_SOUND);

        static bool openYesNo(const QString &title, const QString &subtitle, QWidget *parent, QString iconPath = PATH_DEFAULT_ICON, const QString &soundPath = PATH_DEFAULT_NOTIFICATION_SOUND);
        static void openInfo(const QString &title, const QString &subtitle, QWidget *parent, QString iconPath = PATH_DEFAULT_ICON, const QString &soundPath = PATH_DEFAULT_NOTIFICATION_SOUND);
        static void openDirectory(const QString &title, QWidget *parent = nullptr, std::function<void()> callback = nullptr, QString iconPath = PATH_DEFAULT_ICON, const QString &soundPath = PATH_DEFAULT_NOTIFICATION_SOUND);

    private:
        QHBoxLayout *_infoLayout;
        QLabel *_icon;
        QLabel *_text;
        QSoundEffect _sound;
};

}
