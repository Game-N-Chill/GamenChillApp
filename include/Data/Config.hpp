
#pragma once

#include <iostream>

#include "Utils.hpp"

namespace GNCApp::Data
{

    #define DATA_WINNER_CONFIG_PATH             "data/config.json"

    #define DATA_WINNER_CONFIG_INDEX_THEME      "theme"

class Config : public Utils::Singleton<Config>
{
    public:
        ~Config();

        std::string getTheme() const;
        void setTheme(std::string theme);

        void save();

    private:
        friend class Utils::Singleton<Config>;
        Config();

        json _json;
};

}
