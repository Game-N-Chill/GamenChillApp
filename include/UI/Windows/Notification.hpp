
#pragma once

#include <iostream>
#include <memory>
#include <array>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSoundEffect>

#include "UI/Tools/GroupBox.hpp"
#include "UI/Tools/Browser.hpp"
#include "UI/Tools/Window.hpp"
#include "UI/Tools/Randomizer.hpp"
#include "Data/Data.hpp"

namespace Generator::UI::Windows
{

class Notification : public Tools::Window
{
    Q_OBJECT

    public:
        Notification(const QString &title, const QString &subtitle, QWidget *parent = nullptr);

    private:
        QHBoxLayout *_infoLayout;
        QLabel *_icon;
        QLabel *_text;
        QSoundEffect _sound;
};

}
