
#include "Logic/Logic.hpp"
#include "Data/Data.hpp"

namespace Generator::Logic
{

template<size_t N>
static void createWinnerShared(std::string path, const std::array<Data::Team<N>, PLAYER_GRAPH_COUNT> &array)
{
    if (path.empty()) {
        throw std::runtime_error("can't open file: " + path);
    }
    Canva canva(path);
    Data::Winner *dataWinner = Data::Winner::getInstance();

    canva.getImage("background").image.load(dataWinner->getBackground().path.c_str());
    canva.getText("title").str = dataWinner->getTitle().c_str();
    // canva.getText("titleOutline").str = dataWinner->getTitle();
    canva.getText("subtitle").str = dataWinner->getSubtitle().c_str();
    // canva.getText("subtitleOutline").str = dataWinner->getSubtitle();
    canva.getText("date").str = (dataWinner->getDate() + " - " + std::to_string(dataWinner->getPlayerCount()) + " Participants").c_str();
    // canva.getText("dateOutline").str = dataWinner->getDate() + " - " + std::to_string(dataWinner->getPlayerCount()) + " Participants";

    for (size_t i = 0; i < array.size(); i++) {
        Data::Team<N> team = array[i];

        if (N > 1) {
            canva.getText(std::to_string(i + 1) + '_' + "Team").str = team.name.c_str();
        }

        std::string name;
        for (size_t j = 0; j < team.players.size(); j++) {
            canva.getImage(std::to_string(i + 1) + '_' + std::to_string(j + 1) + '_' + "Character").image.load((team.players[j].getCharacter().path + '\\' + team.players[j].getSkin() + ".png").c_str());
            name += team.players[j].getName();
            if (j < team.players.size() - 1) {
                name += " - ";
            }
        }
        canva.getText(std::to_string(i + 1) + '_' + "Name").str = name.c_str();
    }

    canva.draw();
    canva.save(dataWinner->getOutputDir(), Utils::getTimeFormat("%Y_%m_%d__%H_%M_%S"));
}

void createWinnerSoloImage()
{
    createWinnerShared(CANVA_SOLO_PATH, Data::Winner::getInstance()->getSolo());
}

void createWinnerDuoImage()
{
    createWinnerShared(CANVA_DUO_PATH, Data::Winner::getInstance()->getDuo());
}

}
