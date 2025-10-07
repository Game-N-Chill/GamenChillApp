
#include "UI/Windows/Secondary/PlayerBracket.hpp"

namespace GNCApp::UI::Windows
{

PlayerBracket::PlayerBracket(const QString &title, QWidget *parent) :
    Window(title, parent)
{
    setMinimumSize(350, 50);

    this->_label = new QLabel("Player Name:");
    this->_line = new QLineEdit(this);
    connect(_line, &QLineEdit::textChanged, this, &PlayerBracket::onLineEdited);
    this->_btnPtr = nullptr;

    this->_layout->addWidget(this->_label);
    this->_layout->addWidget(this->_line);
}

QString PlayerBracket::getNameString() const
{
    return this->_line->text();
}

void PlayerBracket::onLineEdited()
{
    if (this->_btnPtr == nullptr)
        return;

    if (_line->text().isEmpty()) {
        this->_btnPtr->setEnabled(false);
    } else {
        this->_btnPtr->setEnabled(true);
    }
}

void PlayerBracket::setupInfo(QPushButton *buttonPtr, bool buttonEnabled, QString playerName)
{
    this->_btnPtr = buttonPtr;
    this->_btnPtr->setEnabled(buttonEnabled);
    this->_line->setText(playerName);
}

} // namespace GNCApp::UI::Windows
