
#include "Data/Player.hpp"
#include "Data/Dictionary/Dictionary.hpp"

namespace Generator::Data
{

Player::Player()
{
    setName(DATA_PLAYER_DEFAULT_NAME);
    setCharacter(DATA_PLAYER_DEFAULT_CHARACTER);
    parseSkins();
}


void Player::setName(std::string name)
{
    this->_name = name;
}

std::string Player::getName() const
{
    return this->_name;
}


void Player::setCharacter(size_t index)
{
    try {
        this->_character = Data::DictCharacter::getInstance()->find(index);
        parseSkins();
    } catch (std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Player::setCharacter(std::string str)
{
    try {
        this->_character = Data::DictCharacter::getInstance()->find(str);
        parseSkins();
    } catch (std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
    }
}

Character Player::getCharacter() const
{
    return this->_character;
}



void Player::setSkin(std::string name)
{
    if (name.empty()) {
        randomizeSkin();
        return;
    }

    this->_index = 0;
    for (size_t i = 0; i < this->_skins.size(); i++) {
        if (this->_skins[i] == name) {
            this->_index = i;
            break;
        }
    }
}

void Player::setSkin(size_t index)
{
    if (index < this->_skins.size()) {
        this->_index = index;
    }
}

std::string Player::getSkin() const
{
    return this->_skins[this->_index];
}

std::vector<std::string> Player::getSkinList() const
{
    return this->_skins;
}

void Player::randomizeSkin()
{
    Utils::Randomizer rand;
    this->_index = rand.GetRandom(this->_skins.size());
}

void Player::parseSkins()
{
    this->_skins.clear();
    this->_index = 0;

    std::string pathDir = this->_character.path;
    if (!std::filesystem::is_directory(pathDir)) {
        std::cerr << "ERROR: " << pathDir << " is not a directory, can't setup skins" << std::endl;
        return;
    }

    // index 0 is always for default
    this->_skins.push_back(DATA_PLAYER_DEFAULT_SKIN);
    for (const auto &entry : std::filesystem::recursive_directory_iterator(pathDir)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            std::string name = path.substr(pathDir.size() + 1, path.size() - (pathDir.size() + 1) - 4);

            if (name != DATA_PLAYER_DEFAULT_SKIN) {
                this->_skins.push_back(name);
            }
        }
    }
}


void Player::print(std::ostream &flux) const
{
    flux << "Name: " << this->_name << std::endl;
    flux << "Character: " << this->_character << std::endl;
    flux << "Skin: " << this->_skins[this->_index] << std::endl;
}

}
