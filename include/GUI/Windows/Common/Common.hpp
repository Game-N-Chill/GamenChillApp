
#pragma once

    #include <QWidget>
    #include <functional>
    #include "GUI/Tools/Window.hpp"

namespace GNCApp::GUI::Windows
{

QPushButton *createPushButton(QWidget *parent, QString title, QString toolTip = "", QString iconPath = "", int width = 0, std::function<void()> func = nullptr);

QPushButton *addWindowButtonValidate(Tools::Window *window);
QPushButton *addWindowButtonCancel(Tools::Window *window);
QPushButton *addWindowButtonOpen(Tools::Window *window, std::function<void()> callback = nullptr);

} // namespace GNCApp
