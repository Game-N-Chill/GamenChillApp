
#pragma once

    #include <QWidget>
    #include "UI/Tools/Window.hpp"

namespace GNCApp::UI::Windows
{

void addWindowButtonValidate(Tools::Window *window);
void addWindowButtonCancel(Tools::Window *window);
void addWindowButtonOpenDir(Tools::Window *window);

void callbackOpenDirectory();

void openWindowUpdate(QWidget *parent);
void openWindowNotificationGeneration(QWidget *parent);

} // namespace GNCApp
