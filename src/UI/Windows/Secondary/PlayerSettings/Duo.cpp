
#include "UI/Windows/Secondary/PlayerSettings.hpp"

namespace GNCApp::UI::Windows
{

PlayerDuo::PlayerDuo(const int &index, const QString &title, QWidget *parent) :
    Window(title, parent)
{
    auto dataWinner = Data::Winner::getInstance();

    setMinimumSize(350, 130);

    this->_teamLabel = new QLabel("Team Name :", this);
    this->_team = new QLineEdit(this);
    this->_team->setText(QString::fromStdString(*dataWinner->getTeamDuo(index)));
    this->_infoFirst = new PlayerInfo(dataWinner->getTeamDuo(index)[0], "Player 1", this);
    this->_infoSecond = new PlayerInfo(dataWinner->getTeamDuo(index)[1], "Player 2", this);
    this->_layout->addWidget(this->_teamLabel);
    this->_layout->addWidget(this->_team);
    this->_layout->addWidget(this->_infoFirst);
    this->_layout->addWidget(this->_infoSecond);
}

Data::Winner::Duo PlayerDuo::getData() const
{
    Data::Winner::Duo data;

    *data = this->_team->text().toStdString();
    data[0] = this->_infoFirst->getData();
    data[1] = this->_infoSecond->getData();

    return data;
}

}
