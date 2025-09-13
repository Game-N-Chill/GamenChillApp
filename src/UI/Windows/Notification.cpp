
#include "UI/Windows/Notification.hpp"

namespace Generator::UI::Windows
{

Notification::Notification(const QString &title, const QString &subtitle, QWidget *parent) :
    Window(title, parent, WINDOW_TOOL_BUTTON_VALIDATE)
{
    setWindowTitle(title);

    this->_infoLayout = new QHBoxLayout;

    this->_icon = new QLabel(this);
    this->_icon->setPixmap(style()->standardPixmap(QStyle::SP_MessageBoxInformation).scaled(32, 32));
    this->_text = new QLabel(subtitle, this);

    this->_infoLayout->addWidget(this->_icon);
    this->_infoLayout->addWidget(this->_text);
    this->_layout->addLayout(this->_infoLayout);

    _sound.setSource(QUrl::fromLocalFile("C:\\Users\\hugor\\GitHub\\Asso\\AssetsGenerator\\Assets\\Sounds\\SE_SYS_BTN_OK.wav"));
    _sound.setVolume(0.8f);
    _sound.play();

    (*this)();
}

}
