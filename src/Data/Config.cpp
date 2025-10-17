
#include "Data/Config.hpp"
#include "Data/Dictionary/Dictionary.hpp"

namespace GNCApp::Data
{

Config::Config()
{
    std::ifstream file(DATA_WINNER_CONFIG_PATH);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("failed to open file ") + DATA_WINNER_CONFIG_PATH);
    }

    file >> this->_json;
    file.close();
}

Config::~Config()
{
    std::ofstream file(DATA_WINNER_CONFIG_PATH);
    if (!file.is_open()) {
        return;
    }

    file << std::setw(4) << this->_json << std::endl;
    file.close();
}

std::string Config::getTheme() const
{
    return this->_json[DATA_WINNER_CONFIG_INDEX_THEME];
}

void Config::setTheme(std::string theme)
{
    this->_json[DATA_WINNER_CONFIG_INDEX_THEME] = theme;
}


}
