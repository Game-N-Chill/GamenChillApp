
#pragma once

#include <iostream>
#include <map>
#include <QString>
#include <QFontDatabase>
#include "Utils.hpp"

namespace Generator::Data
{

    #define PREFIX_FONTS      ":/Fonts/"

class Assets : public Utils::Singleton<Assets>
{
    public:
        ~Assets() = default;

        QString getFont(QString fontName);

    private:
        friend class Utils::Singleton<Assets>;
        Assets();

        std::map<QString, int> _fonts;
};

}
