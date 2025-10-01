
#include "UI/Windows/Secondary/PlayerSettings.hpp"

namespace GNCApp::UI::Windows
{

PlayerSolo::PlayerSolo(const int &index, const QString &title, QWidget *parent) :
    Window(title, parent)
{
    auto dataWinner = Data::Winner::getInstance();

    setMinimumSize(350, 150);
    this->_info = new PlayerInfo(dataWinner->getTeamSolo(index).players[0], "Player 1", this);
    this->_layout->addWidget(this->_info);
}

Data::Solo PlayerSolo::getData() const
{
    Data::Solo data;

    data.players[0] = this->_info->getData();

    return data;
}

}
