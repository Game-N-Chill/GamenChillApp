
#include "GUI/Windows/Common/Notification.hpp"

namespace GNCApp::GUI::Windows
{

Notification::Notification(const QString &title, const QString &subtitle, QWidget *parent, QString iconPath, const QString &soundPath) :
    Window(title, parent)
{
    this->setMinimumSize(250, 125);
    this->_infoLayout = new QHBoxLayout;

    QPixmap pix(iconPath);
    pix = pix.scaled(QSize(32, 32), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    this->_icon = new QLabel(this);
    this->_icon->setPixmap(pix);
    this->_text = new QLabel(subtitle, this);

    this->_infoLayout->addWidget(this->_icon);
    this->_infoLayout->addWidget(this->_text);
    this->_infoLayout->addStretch();
    this->_layout->addLayout(this->_infoLayout);

    _sound.setSource(QUrl::fromLocalFile(soundPath));
    _sound.setVolume(0.8f);
    _sound.play();
}

bool Notification::openYesNo(const QString &title, const QString &subtitle, QWidget *parent, QString iconPath, const QString &soundPath)
{
    Tools::Window *window = new Notification(title, subtitle, parent, iconPath, soundPath);

    addWindowButtonValidate(window);
    addWindowButtonCancel(window);

    (*window)();
    bool ret = window->hasValidate();

    delete window;
    return ret;
}

void Notification::openInfo(const QString &title, const QString &subtitle, QWidget *parent, QString iconPath, const QString &soundPath)
{
    Tools::Window *window = new Notification(title, subtitle, parent, iconPath, soundPath);

    addWindowButtonValidate(window);

    (*window)();

    delete window;
}

void Notification::openDirectory(const QString &title, QWidget *parent, std::function<void()> callback, QString iconPath, const QString &soundPath)
{
    Tools::Window *window = new Notification("Game'n Chill App Notification", title, parent, iconPath, soundPath);

    addWindowButtonOpen(window, callback);
    addWindowButtonValidate(window);

    (*window)();

    delete window;
}

}
