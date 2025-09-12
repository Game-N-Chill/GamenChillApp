
#include "Logic.hpp"

namespace Generator::Logic
{

template<size_t N>
static void createWinnerShared(std::string path, const std::array<Data::Team<N>, PLAYER_GRAPH_COUNT> &array)
{
    if (path.empty()) {
        throw std::runtime_error("can't open file: " + path);
    }
    Render::Canva canva(path);
    Data::Winner *dataWinner = Data::Winner::getInstance();

    canva.getImage("background")->load(dataWinner->getBackground().path);
    canva.getText("title")->load(dataWinner->getTitle());
    canva.getText("titleOutline")->load(dataWinner->getTitle());
    canva.getText("subtitle")->load(dataWinner->getSubtitle());
    canva.getText("subtitleOutline")->load(dataWinner->getSubtitle());
    canva.getText("date")->load(dataWinner->getDate() + " - " + std::to_string(dataWinner->getPlayerCount()) + " Participants");
    canva.getText("dateOutline")->load(dataWinner->getDate() + " - " + std::to_string(dataWinner->getPlayerCount()) + " Participants");

    for (size_t i = 0; i < array.size(); i++) {
        Data::Team<N> team = array[i];

        if (N > 1) {
            canva.getText(std::to_string(i + 1) + '_' + "Team")->load(team.name);
        }

        std::string name;
        for (size_t j = 0; j < team.players.size(); j++) {
            canva.getImage(std::to_string(i + 1) + '_' + std::to_string(j + 1) + '_' + "Character")->load(team.players[j].getCharacter().path + '\\' + team.players[j].getSkin() + ".png");
            name += team.players[j].getName();
            if (j < team.players.size() - 1) {
                name += " - ";
            }
        }
        canva.getText(std::to_string(i + 1) + '_' + "Name")->load(name);
    }

    std::vector<std::string> vec = canva.getOrder();
    for (auto &obj : vec) {
        canva.draw(obj);
    }
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
