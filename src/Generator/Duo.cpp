
#include "MKTG.hpp"

namespace MKTG
{

//  Team GETTER/SETTER
// *****************************************************************************

Duo Generator::getDuoInfo(size_t rank)
{
    return this->getTeamInfo<2>(rank, this->_duo);
}

void Generator::setDuoInfo(size_t rank, size_t index, std::string character, std::string name)
{
    this->setTeamInfo<2>(rank, index, character, name, this->_duo);
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

        team->rank = i;
        team->name = player[INDEX_TEAM];
        for (size_t j = 0; j < team->players.size(); j++) {
            team->players[j].character = player[INDEX_CHARACTER][j];
            team->players[j].name = player[INDEX_NAME][j];
            if (i == 1) {
                this->setDataLink(team->players[j].character);
            }
        }
    }
}

void Generator::createDuo()
{
    this->createImage<2>(CANVA_DUO_PATH, this->_duo);
}

} // namespace MKTG
