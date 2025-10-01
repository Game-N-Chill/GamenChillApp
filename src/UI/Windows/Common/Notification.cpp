
#include "UI/Windows/Common/Notification.hpp"

namespace GNCApp::UI::Windows
{

Notification::Notification(const QString &title, const QString &subtitle, const QString &soundPath, QWidget *parent) :
    Window(title, parent)
{
    this->_infoLayout = new QHBoxLayout;

    QPixmap pix(":/icons/info");
    pix = pix.scaled(QSize(32, 32), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    this->_icon = new QLabel(this);
    this->_icon->setPixmap(pix);
    this->_text = new QLabel(subtitle, this);

    this->_infoLayout->addWidget(this->_icon);
    this->_infoLayout->addWidget(this->_text);
    this->_layout->addLayout(this->_infoLayout);

    _sound.setSource(QUrl::fromLocalFile(soundPath));
    _sound.setVolume(0.8f);
    _sound.play();
}

}
