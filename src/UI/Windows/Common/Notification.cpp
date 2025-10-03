
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

void Notification::openUpdate(QWidget *parent)
{
    Tools::Window *window = new Notification("Update", "An update has been found, do you want to install it ?", PATH_DEFAULT_NOTIFICATION_SOUND, parent);

    addWindowButtonValidate(window);
    addWindowButtonCancel(window);

    (*window)();
    if (window->hasValidate()) {
        Utils::createProcess(std::filesystem::current_path().string() + '/' + GNCAPP_NAME + "_Updater.exe");
    }

    delete window;
}

void Notification::openGeneration(QWidget *parent)
{
    Tools::Window *window = new Notification("Game'n Chill App Notification", "Winner image generation done", PATH_DEFAULT_NOTIFICATION_SOUND, parent);

    addWindowButtonOpenDir(window);
    addWindowButtonValidate(window);

    (*window)();

    delete window;
}

}
