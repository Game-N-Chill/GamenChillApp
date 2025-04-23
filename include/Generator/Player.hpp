
#pragma once

#include <iostream>

namespace MKTG
{


struct Player
{
    std::string character;
    std::string name;
};

template<size_t N>
struct Team
{
    std::array<Player, N> players;
    std::size_t rank;
    std::string name;

    Team(size_t rank)
    {
        this->rank = rank;
        for (size_t i = 0; i < N; i++) {
            this->players[i].character = "Mario";
            this->players[i].name = "Player";
        }
    }
};

template<size_t N>
using SharedTeam = std::shared_ptr<Team<N>>;

typedef SharedTeam<1>   Solo;
typedef SharedTeam<2>   Duo;

} // namespace MKTG

template<size_t N>
std::ostream &operator<<(std::ostream &flux, MKTG::Team<N> &team)
{
    if (N == 1) {
        flux << std::left << "-- Joueur  #" << std::setw(4) << team.rank << std::setw(22) << team.players[0].character << team.players[0].name << std::endl;
    } else {
        flux << std::left << "-- Team #" << std::setw(3) << team.rank << std::endl;
        for (size_t i = 0; i < N; i++) {
            std::cout << std::left << std::setw(15) << " -- Joueur" << std::setw(22) << team.players[i].character << team.players[i].name << std::endl;
        }
    }
    return flux;
}
