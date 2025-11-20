
#pragma once

#include <iostream>
#include <map>
#include <QString>
#include <QFontDatabase>
#include <GoGuLib.hpp>

namespace GNCApp::Data
{

    #define PATH_ASSETS_FONTS   "assets/Fonts/"

class Assets : public  GGL::Singleton<Assets>
{
    public:
        ~Assets() = default;

        QString getFont(std::string fontName);

    private:
        friend class  GGL::Singleton<Assets>;
        Assets();

        std::map<QString, int> _fonts;
};

}
