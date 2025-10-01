
#include "Utils.hpp"
#include <sstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
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
    std::string fullPath = std::filesystem::current_path().string() + "/" + std::string(path);
    std::replace(fullPath.begin(), fullPath.end(), '\\', '/');
    return fullPath;
}

}
