
#include "UI/Windows/PlayerSettings.hpp"

namespace Generator::UI::Windows
{

PlayerSolo::PlayerSolo(const QString &title, QWidget *parent) :
    Window(title, parent)
{
    setMinimumSize(350, 150);
    this->_info = new PlayerInfo("Player 1", this);
    this->_layout->addWidget(this->_info);
}

}
