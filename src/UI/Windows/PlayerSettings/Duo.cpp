
#include "UI/Windows/PlayerSettings.hpp"

namespace Generator::UI::Windows
{

PlayerDuo::PlayerDuo(const int &index, const QString &title, QWidget *parent) :
    Window(title, parent)
{
    auto dataWinner = Data::Winner::getInstance();

    setMinimumSize(350, 130);

    this->_teamLabel = new QLabel("Team Name :", this);
    this->_team = new QLineEdit(this);
    this->_team->setText(QString::fromStdString(dataWinner->getTeamDuo(index).name));
    this->_infoFirst = new PlayerInfo(dataWinner->getTeamDuo(index).players[0], "Player 1", this);
    this->_infoSecond = new PlayerInfo(dataWinner->getTeamDuo(index).players[1], "Player 2", this);
    this->_layout->addWidget(this->_teamLabel);
    this->_layout->addWidget(this->_team);
    this->_layout->addWidget(this->_infoFirst);
    this->_layout->addWidget(this->_infoSecond);

    (*this)();
}

Data::Duo PlayerDuo::getData() const
{
    Data::Duo data;

    data.name = this->_team->text().toStdString();
    data.players[0] = this->_infoFirst->getData();
    data.players[1] = this->_infoSecond->getData();

    return data;
}

}
