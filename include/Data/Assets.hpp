
#pragma once

#include <iostream>
#include <map>
#include <QString>
#include <QFontDatabase>
#include "Utils.hpp"

namespace GNCApp::Data
{

    #define PATH_ASSETS_FONTS   "assets/Fonts/"

class Assets : public Utils::Singleton<Assets>
{
    public:
        ~Assets() = default;

        QString getFont(std::string fontName);

    private:
        friend class Utils::Singleton<Assets>;
        Assets();

        std::map<QString, int> _fonts;
};

}
