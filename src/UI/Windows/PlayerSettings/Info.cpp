
#include "UI/Windows/PlayerSettings.hpp"

namespace Generator::UI::Windows
{

PlayerInfo::PlayerInfo(const Data::Player &data, const QString &title, QWidget *parent) :
    QWidget(parent)
{
    auto dataWinner = Data::Winner::getInstance();
    this->_data = data;

    this->_box = new Tools::FGroupBox(title, this);

    this->_player = new QLineEdit(this);
    this->_player->setText(QString::fromStdString(this->_data.getName()));
    connect(this->_player, &QLineEdit::textEdited, this, &PlayerInfo::onNameEdited);

    this->_character = new QComboBox(this);
    for (auto &it : Data::DictCharacter::getInstance()->list()) {
        this->_character->addItem(QString::fromStdString(it));
    }
    this->_character->setCurrentText(QString::fromStdString(this->_data.getCharacter().name));
    connect(this->_character, &QComboBox::currentIndexChanged, this, &PlayerInfo::onCharacterChanged);

    this->_skins = new Tools::Randomizer(this->_data.getSkinList(), this);
    this->_skins->getComboBox()->setCurrentText(QString::fromStdString(this->_data.getSkin()));
    connect(this->_skins->getComboBox(), &QComboBox::currentIndexChanged, this, &PlayerInfo::onSkinChanged);

    this->_box->addRow("Name : ", this->_player);
    this->_box->addRow("Character : ", this->_character);
    this->_box->addRow("Skin : ", this->_skins);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}

Data::Player PlayerInfo::getData() const
{
    return this->_data;
}


void PlayerInfo::onNameEdited(const QString &str)
{
    this->_data.setName(str.toStdString());
}

void PlayerInfo::onCharacterChanged(int index)
{
    // Change character into local data so all skins are fetch
    this->_data.setCharacter(index);

    // Deleting current skin list and update it for the new character
    this->_skins->getComboBox()->clear();
    for (auto &it : this->_data.getSkinList()) {
        this->_skins->getComboBox()->addItem(QString::fromStdString(it));
    }
    this->_skins->getComboBox()->setCurrentIndex(0);
}

void PlayerInfo::onSkinChanged(int index)
{
    // Change character into local data so all skins are fetch
    this->_data.setSkin(index);
}


}
