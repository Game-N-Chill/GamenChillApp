
#include <sstream>

#include "Data/Dictionary/Character.hpp"
#include "Utils.hpp"

namespace GNCApp::Data
{

Character::Character()
{
    this->path = DATA_CHARACTER_DEFAULT_PATH;
    this->name = DATA_CHARACTER_DEFAULT_NAME;
}

Character::Character(std::string str)
{
    this->path = str;
    this->name = str.substr(str.find_last_of('/') + 1);
}

void Character::load(std::list<Character> &list)
{
    std::string path = Utils::getFullPath(PATH_CHARACTER_DIR);

    for (const auto &entry : std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_directory()) {
            std::string path = entry.path().string();
            list.push_back(Character(path));
        }
    }
}

bool Character::operator==(std::string key)
{
    return (name == key);
}

Character::operator std::string() const
{
    std::ostringstream oss;
    oss << this->name;
    return oss.str();
}

} // namespace GNCApp::Data

std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Character &character)
{
    flux << character.name;
    return flux;
}
