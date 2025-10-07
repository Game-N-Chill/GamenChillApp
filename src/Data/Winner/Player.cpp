
#include "Data/Winner.hpp"
#include "Data/Dictionary/Dictionary.hpp"

namespace GNCApp::Data
{

Winner::Player::Player()
{
    setName(DATA_WINNER_PLAYER_DEFAULT_NAME);
    setCharacter(DATA_WINNER_PLAYER_DEFAULT_CHARACTER);
    parseSkins();
}


void Winner::Player::setName(std::string name)
{
    this->_name = name;
}

std::string Winner::Player::getName() const
{
    return this->_name;
}


void Winner::Player::setCharacter(size_t index)
{
    try {
        this->_character = Data::DictCharacter::getInstance()->find(index);
        parseSkins();
    } catch (std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Winner::Player::setCharacter(std::string str)
{
    try {
        this->_character = Data::DictCharacter::getInstance()->find(str);
        parseSkins();
    } catch (std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
    }
}

Character Winner::Player::getCharacter() const
{
    return this->_character;
}



void Winner::Player::setSkin(std::string name)
{
    if (name.empty()) {
        randomizeSkin();
        return;
    }

    this->_index = 0;
    size_t tempIndex = 0;
    for (auto it = this->_skins.begin(); it != this->_skins.end(); it++, tempIndex++) {
        if (*it == name) {
            this->_index = tempIndex;
            return;
        }
    }
}

void Winner::Player::setSkin(size_t index)
{
    if (index < this->_skins.size()) {
        this->_index = index;
    }
}

std::string Winner::Player::getSkin() const
{
    auto it = this->_skins.begin();
    std::advance(it, this->_index);
    return *it;
}

std::list<std::string> Winner::Player::getSkinList() const
{
    return this->_skins;
}

void Winner::Player::randomizeSkin()
{
    Utils::Randomizer rand;
    this->_index = rand.GetRandom(this->_skins.size());
}

void Winner::Player::parseSkins()
{
    this->_skins.clear();
    this->_index = 0;

    std::string pathDir = this->_character.path;
    if (!std::filesystem::is_directory(pathDir)) {
        std::cerr << "ERROR: " << pathDir << " is not a directory, can't setup skins" << std::endl;
        return;
    }

    // index 0 is always for default
    this->_skins.push_back(DATA_WINNER_PLAYER_DEFAULT_SKIN);
    for (const auto &entry : std::filesystem::recursive_directory_iterator(pathDir)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            std::string name = path.substr(pathDir.size() + 1, path.size() - (pathDir.size() + 1) - 4);

            if (name != DATA_WINNER_PLAYER_DEFAULT_SKIN) {
                this->_skins.push_back(name);
            }
        }
    }
}


void Winner::Player::print(std::ostream &flux) const
{
    flux << "Name: " << this->_name << std::endl;
    flux << "Character: " << this->_character << std::endl;
    flux << "Skin: " << this->getSkin() << std::endl;
}

}
