
#include "Utils.hpp"
#include <ctime>
#include <sstream>
#include <vector>

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Utils
{

std::string getTimeFormat(std::string format)
{
    std::time_t now = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now), format.c_str());
    return oss.str();
}

std::string stringToUpper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](uint8_t c) {
        return std::toupper(c);
    });
    return str;
}

std::string getCompleteName(std::string name, json &tags)
{
    name = stringToUpper(name);
    for (auto &[key, value] : tags.items()) {
        auto vec = value.get<std::vector<std::string>>();
        for (auto &player : vec) {
            if (name == player) {
                name = key + " | " + name;
                return name;
            }
        }
    }
    return name;
}

std::string getFullPath(std::string path)
{
    return SDL_GetBasePath() + std::string(path);
}

}
