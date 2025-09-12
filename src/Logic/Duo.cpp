
#include "MKTG.hpp"
#include <algorithm>

namespace MKTG
{

//  Team GETTER/SETTER
// *****************************************************************************

Duo Generator::getDuoInfo(size_t rank)
{
    return this->getTeamInfo<2>(rank, this->_duo);
}

void Generator::setDuoInfo(size_t rank, std::string name, std::string character_01, std::string player_01, std::string character_02, std::string player_02)
{
    this->setTeamInfo<2>(rank, name, 0, character_01, player_01, this->_duo);
    this->setTeamInfo<2>(rank, name, 1, character_02, player_02, this->_duo);
}

void Generator::printDuo()
{
    size_t len = 0;
    for (size_t i = 1; i <= this->_duo.size(); i++) {
        Duo team = getDuoInfo(i);
        for (size_t j = 0; j < team->players.size(); j++) {
            std::string skin = team->players[j].getSkin();
            if (skin != CHARACTER_DEFAULT_NAME) {
                len = std::max<size_t>(len, team->players[j].character.size() + skin.size() + 3); // +3 for space and parenthesis
            } else {
                len = std::max<size_t>(len, team->players[j].character.size());
            }
        }
    }
    len += 2;

    for (size_t i = 1; i <= this->_duo.size(); i++) {
        Duo team = getDuoInfo(i);
        std::cout << std::left << "-- Team #" << std::setw(3) << team->rank << '(' << team->name << ')' << std::endl;
        for (size_t j = 0; j < team->players.size(); j++) {
            std::string character = team->players[j].character;
            if (team->players[j].getSkin() != CHARACTER_DEFAULT_NAME) {
                character += " (" + team->players[j].getSkin() + ')';
            }
            std::cout << std::left << " -- " << std::setw(len) << character << team->players[j].name << std::endl;
        }
    }
}

//  Image Creation
// *****************************************************************************

void Generator::LoadDuo(std::string jsonPath)
{
    if (jsonPath.empty()) {
        return;
    }

    json data;
    std::ifstream file(jsonPath);
    file >> data;
    file.close();

    this->setTitle(data[INDEX_TITLE]);
    this->setSubtitle(data[INDEX_SUBTITLE]);
    this->setDate(data[INDEX_DATE]);
    this->setPlayerCount(data[INDEX_COUNT]);

    json players = data[INDEX_PLAYERS];
    size_t i = 0;
    for (auto &player : players) {
        Duo &team = this->_duo[i];
        i++;

        setDuoInfo(
            i,
            player[INDEX_TEAM],
            player[INDEX_CHARACTER][0],
            player[INDEX_NAME][0],
            player[INDEX_CHARACTER][1],
            player[INDEX_NAME][1]
        );
    }
}

void Generator::createDuo()
{
    this->createImage<2>(CANVA_DUO_PATH, this->_duo);
}

} // namespace MKTG
