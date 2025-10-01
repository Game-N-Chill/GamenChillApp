
#pragma once

#include <iostream>
#include <QApplication>
#include <QString>

#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI
{

void setAppTheme(const char *path);
void setAppTheme(std::string path);
void setAppTheme(QString path);

void createPrimaryWindow();

class App : public QApplication
{
    Q_OBJECT

    public:
        App(int ac, char **av);
        ~App();

    private:
        Windows::Primary _window;
};

} // namespace GNCApp::UI
