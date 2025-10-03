
#include "Logic/Logic.hpp"
#include "Data/Data.hpp"

namespace GNCApp::Logic
{

template<size_t N>
static void createWinnerShared(std::string path, const std::array<Data::Winner::Team<N>, PLAYER_GRAPH_COUNT> &array)
{
    if (path.empty()) {
        throw std::runtime_error("can't open file: " + path);
    }
    Canva canva(path);
    Data::Winner *dataWinner = Data::Winner::getInstance();

    canva.getImage("background").image.load(dataWinner->getBackground().path.c_str());
    canva.getText("title").str = dataWinner->getTitle().c_str();
    canva.getText("subtitle").str = dataWinner->getSubtitle().c_str();
    canva.getText("date").str = (dataWinner->getDate()).c_str();
    canva.getText("playerCount").str = (std::to_string(dataWinner->getPlayerCount()) + " Participants").c_str();

    for (size_t i = 0; i < array.size(); i++) {
        Data::Winner::Team<N> team = array[i];

        if (N > 1) {
            canva.getText(std::to_string(i + 1) + '_' + "Team").str = team.getName().c_str();
        }

        std::string name;
        for (size_t j = 0; j < N; j++) {
            canva.getImage(std::to_string(i + 1) + '_' + std::to_string(j + 1) + '_' + "Character").image.load((team.getPlayer(j).getCharacter().path + '/' + team.getPlayer(j).getSkin() + ".png").c_str());
            name += team.getPlayer(j).getName();
            if (j < N - 1) {
                name += " - ";
            }
        }
        canva.getText(std::to_string(i + 1) + '_' + "Name").str = name.c_str();
    }

    canva.draw();
    canva.save(dataWinner->getOutputDir(), Utils::getTimeFormat("%Y_%m_%d__%H_%M_%S"));
}

static std::string getCanvaPath(std::string pathFile)
{
    std::vector<std::string> map = {
        "MKWorld",
        "MK8"
    };

    return CANVA_PATH + map[Data::Winner::getInstance()->getGame()] + '/' + pathFile;
}

void createWinnerSoloImage()
{
    createWinnerShared(getCanvaPath(CANVA_SOLO_PATH), Data::Winner::getInstance()->getSolo());
}

void createWinnerDuoImage()
{
    createWinnerShared(getCanvaPath(CANVA_DUO_PATH), Data::Winner::getInstance()->getDuo());
}

}
