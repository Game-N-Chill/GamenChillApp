
#pragma once

#include <iostream>
#include <GoGuLib.hpp>

namespace GNCApp::Data
{

    #define DATA_WINNER_CONFIG_PATH             "data/config.json"

    #define DATA_WINNER_CONFIG_INDEX_THEME      "theme"

class Config : public GGL::Singleton<Config>
{
    public:
        ~Config();

        std::string getTheme() const;
        void setTheme(std::string theme);

        void save();

    private:
        friend class  GGL::Singleton<Config>;
        Config();

        json _json;
};

}
