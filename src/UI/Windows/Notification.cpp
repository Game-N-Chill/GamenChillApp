
#include "UI/Windows/Notification.hpp"

namespace GNCApp::UI::Windows
{

Notification::Notification(const QString &title, const QString &subtitle, const QString &soundPath, QWidget *parent, int buttons) :
    Window(title, parent, buttons)
{
    this->_infoLayout = new QHBoxLayout;

    this->_icon = new QLabel(this);
    this->_icon->setPixmap(style()->standardPixmap(QStyle::SP_MessageBoxInformation).scaled(32, 32));
    this->_text = new QLabel(subtitle, this);

    this->_infoLayout->addWidget(this->_icon);
    this->_infoLayout->addWidget(this->_text);
    this->_layout->addLayout(this->_infoLayout);

    _sound.setSource(QUrl::fromLocalFile(soundPath));
    _sound.setVolume(0.8f);
    _sound.play();

    (*this)();
}

}
