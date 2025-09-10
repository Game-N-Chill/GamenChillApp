
#include "UI/Windows/PlayerSettings.hpp"

namespace Generator::UI::Windows
{

PlayerInfo::PlayerInfo(const QString &title, QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout;

    _box = new Tools::FGroupBox(title, this);

    this->_player = new QLineEdit(this);

    this->_character = new QComboBox(this);
    this->_character->addItem("Mario");
    this->_character->addItem("Luigi");
    this->_character->addItem("Peach");
    this->_character->addItem("Daisy");

    this->_skins = new QComboBox(this);
    this->_skins->addItem("default");
    this->_skins->addItem("Fire");
    this->_skins->addItem("Ice");
    this->_skins->addItem("Helico");

    this->_box->addRow("Name : ", this->_player);
    this->_box->addRow("Character : ", this->_character);
    this->_box->addRow("Skin : ", this->_skins);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}

}
