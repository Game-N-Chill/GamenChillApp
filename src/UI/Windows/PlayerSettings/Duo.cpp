
#include "UI/Windows/PlayerSettings.hpp"

namespace Generator::UI::Windows
{

PlayerDuo::PlayerDuo(const QString &title, QWidget *parent) :
    Window(title, parent)
{
    setMinimumSize(350, 130);

    this->_teamLabel = new QLabel("Team Name :", this);
    this->_team = new QLineEdit(this);
    this->_infoFirst = new PlayerInfo("Player 1", this);
    this->_infoSecond = new PlayerInfo("Player 2", this);
    this->_layout->addWidget(this->_teamLabel);
    this->_layout->addWidget(this->_team);
    this->_layout->addWidget(this->_infoFirst);
    this->_layout->addWidget(this->_infoSecond);
}

}
