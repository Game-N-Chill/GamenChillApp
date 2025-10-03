
#pragma once

    #include <QWidget>
    #include <functional>
    #include "UI/Tools/Window.hpp"

namespace GNCApp::UI::Windows
{

QPushButton *createPushButton(QWidget *parent, QString title, QString toolTip = "", QString iconPath = "", int width = 0, std::function<void()> func = nullptr);

QPushButton *addWindowButtonValidate(Tools::Window *window);
QPushButton *addWindowButtonCancel(Tools::Window *window);
QPushButton *addWindowButtonOpenDir(Tools::Window *window);

void callbackOpenDirectory();

void openWindowUpdate(QWidget *parent);
void openWindowNotificationGeneration(QWidget *parent);

} // namespace GNCApp
