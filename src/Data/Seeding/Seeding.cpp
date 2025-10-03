
#include "Data/Seeding.hpp"
#include <algorithm>

namespace GNCApp::Data
{

static void genericAddPlayer(std::list<Seeding::Player> &list, const Seeding::Player &player, size_t pos)
{
    for (auto &it : list) {
        if (it == player) {
            return;
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

void Seeding::addPlayer(std::string name, float seeding, size_t pos)
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
        std::cerr << e.what() << std::endl;
    }
}

void Seeding::sort()
{
    this->_list.sort(std::greater<Player>());
}


void Seeding::loadFromFile()
{
    clear();
    addPlayer("Batefimbi", 0.8f);
    addPlayer("GoGu", 1.0f);
    addPlayer("Supnyus", 0.5f);
    addPlayer("Bastien", 0.6f);
    addPlayer("fnzéibvze_12", 0.04f);
    addPlayer("fnzéibvzedazfza_18", 0.03f);
    addPlayer("fnzéibvzedazfzadazdaz_24", 0.2f);
    addPlayer("fnzéibvzedazfzadazdazdazdazdz_32", 0.01f);
    addPlayer("dazfazfzafnzéibvzedazfzadazdazdazdazdz_41", 0.001f);
    addPlayer("dazfazfzafnzéibvzedazfzadazdazdazdacvzejhbhezbuezzdz_55", 0.0001f);
    sort();
}


}
