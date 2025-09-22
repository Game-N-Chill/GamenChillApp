
#pragma once

#include <iostream>
#include <filesystem>
#include <vector>

#include "Utils.hpp"
#include "Data/Dictionary/Character.hpp"

namespace GNCApp::Data
{

    #define PATH_CHARACTERS_DIR             "Assets\\Images\\Characters\\"

    #define DATA_PLAYER_DEFAULT_NAME        "Player"
    #define DATA_PLAYER_DEFAULT_CHARACTER   "Mario"
    #define DATA_PLAYER_DEFAULT_SKIN        "default"
    #define DATA_TEAM_DEFAULT_NAME          "Team"

class Player
{
    public:
        Player();
        ~Player() = default;

        void setName(std::string name);
        std::string getName() const;

        void setCharacter(size_t index);
        void setCharacter(std::string character);
        Character getCharacter() const;

        void setSkin(std::string name);
        void setSkin(size_t index);
        std::string getSkin() const;
        std::list<std::string> getSkinList() const;
        void parseSkins();
        void randomizeSkin();

        void print(std::ostream &flux = std::cout) const;

    private:
        std::string _name;
        Character _character;

        std::list<std::string> _skins;
        size_t _index;
};

template<size_t N>
struct Team
{
    std::string name;
    std::array<Player, N> players;

    Team()
    {
        this->name = "Team";
        for (size_t i = 0; i < N; i++) {
            this->players[i].setCharacter("Mario");
            this->players[i].setName("Player");
            this->players[i].parseSkins();
        }
    }

    void print(std::ostream &flux = std::cout) const
    {
        flux << "Name: " << this->name << std::endl;
        for (size_t i = 0; i < N; i++) {
            flux << "Player " << i + 1 << ": " << std::endl;
            this->players[i].print(flux);
        }
    }
};

template<size_t N>
using SharedTeam = std::shared_ptr<Team<N>>;

typedef Team<1>         Solo;
typedef Team<2>         Duo;

typedef SharedTeam<1>   SharedSolo;
typedef SharedTeam<2>   SharedDuo;

} // namespace MKTG

template<size_t N>
std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Team<N> team)
{
    team.print(flux);
    return flux;
}
