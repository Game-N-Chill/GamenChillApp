
#include "Shared/Data/Seeding.hpp"
#include <algorithm>
#include <limits>

namespace GNCApp::Data
{

Seeding::Seeding()
{
    this->_pathOutput =  GGL::getFullPath(DATA_BRACKET_DEFAULT_OUTPUT_DIR);
    this->_number = 1;
    this->_edition = "150cc";
}

std::string Seeding::getOutputPath() const
{
    return this->_pathOutput;
}

void Seeding::setOutputPath(std::string path)
{
    this->_pathOutput = path;
}

size_t Seeding::getNumber() const
{
    return this->_number;
}

void Seeding::setNumber(size_t value)
{
    this->_number = value;
}


std::string Seeding::getEdition() const
{
    return "Edition " + this->_edition;
}

void Seeding::setEdition(std::string value)
{
    this->_edition = value;
}


static void genericAddPlayer(std::list<Seeding::Player> &list, const Seeding::Player &player, size_t pos)
{
    for (auto &it : list) {
        if (it == player) {
            throw std::runtime_error("player already in list");
        }
    }

    if (pos >= list.size()) {
        list.push_back(player);
    } else {
        auto it = list.begin();
        std::advance(it, pos);
        list.insert(it, player);
    }
}

void Seeding::addPlayer(size_t pos)
{
    genericAddPlayer(this->_list, Player(), pos);
}

void Seeding::addPlayer(const Player &player, size_t pos)
{
    genericAddPlayer(this->_list, player, pos);
}

void Seeding::addPlayer(std::string name, double seeding, size_t pos)
{
    genericAddPlayer(this->_list, Player(name, seeding), pos);
}

void Seeding::removePlayer(size_t index)
{
    if (index >= this->_list.size()) {
        throw std::out_of_range(std::string(__func__) + ": index out of range (" + std::to_string(index) + ")");
    }

    auto it = this->_list.begin();
    std::advance(it, index);
    this->_list.erase(it);
}

void Seeding::removePlayer(std::string name)
{
    this->_list.remove_if([=](Player player){
        return player == name;
    });
}

void Seeding::removePlayer(const Player &player)
{
    this->_list.remove(player);
}

void Seeding::clear()
{
    this->_list.clear();
}

Seeding::Player Seeding::getPlayer(size_t index) const
{
    if (index >= this->_list.size()) {
        throw std::out_of_range(std::string(__func__) + ": index out of range (" + std::to_string(index) + ")");
    }

    auto it = this->_list.begin();
    std::advance(it, index);
    return *it;
}

Seeding::Player Seeding::getPlayer(std::string name) const
{
    auto it = std::find(this->_list.begin(), this->_list.end(), name);
    if (it == this->_list.end()) {
        throw std::out_of_range(std::string(__func__) + ": can't find player: " + name);
    } else {
        return *it;
    }
}

Seeding::Player &Seeding::atPlayer(size_t index)
{
    if (index >= this->_list.size()) {
        throw std::out_of_range(std::string(__func__) + ": index out of range (" + std::to_string(index) + ")");
    }

    auto it = this->_list.begin();
    std::advance(it, index);
    return *it;
}

Seeding::Player &Seeding::atPlayer(std::string name)
{
    auto it = std::find(this->_list.begin(), this->_list.end(), name);
    if (it == this->_list.end()) {
        throw std::out_of_range(std::string(__func__) + ": can't find player: " + name);
    } else {
        return *it;
    }
}

Seeding::Player &Seeding::operator[](size_t index)
{
    return atPlayer(index);
}

Seeding::Player &Seeding::operator[](std::string name)
{
    return atPlayer(name);
}

size_t Seeding::getSize() const
{
    return this->_list.size();
}

void Seeding::move(int indexSrc, int indexDest)
{
    try {
        Player playerSrc = getPlayer(indexSrc);
        Player playerDest = getPlayer(indexDest);
        this->atPlayer(indexSrc) = playerDest;
        this->atPlayer(indexDest) = playerSrc;
    } catch (std::out_of_range &e) {
        Error() << e.what() << GGL::end;
    }
}

void Seeding::sort(const std::map<std::string, double> &map)
{
    for (auto it = this->_list.begin(); it != this->_list.end(); it++) {
        std::string name = it->getName();

        auto itMap = map.find( GGL::stringToLower(name));
        if (itMap != map.end()) {
            it->setSeeding(itMap->second);
            Log() << "found player " << itMap->first << ", seeding: " << itMap->second << GGL::end;
        }
    }

    this->_list.sort(std::less<Player>());
}

}
