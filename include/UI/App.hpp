
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

} // namespace GNCApp::UI
