
#include <QString>
#include <QDesktopServices>
#include <QUrl>

#include "UI/Windows/Shared.hpp"
#include "UI/Windows/Notification.hpp"
#include "Data/Data.hpp"
#include "Update/Update.hpp"

namespace GNCApp::UI::Windows
{

static QPushButton *createButton(Tools::Window *window, QString title, QString iconPath, int minWidth)
{
    QPushButton *button = new QPushButton(title, window);

    if (!iconPath.isEmpty()) {
        button->setIcon(QIcon(iconPath));
    }
    if (minWidth > 0) {
        button->setMinimumWidth(minWidth);
    }

    window->addButton(button);
    return button;
}

void addWindowButtonValidate(Tools::Window *window)
{
    QPushButton *button = createButton(window, " OK", ":/icons/validate", 80);
    window->connect(button, &QPushButton::clicked, window, &QDialog::accept);
}

void addWindowButtonCancel(Tools::Window *window)
{
    QPushButton *button = createButton(window, " Cancel", ":/icons/remove", 80);
    window->connect(button, &QPushButton::clicked, window, &QDialog::reject);
}

void addWindowButtonOpenDir(Tools::Window *window)
{
    QPushButton *button = createButton(window, " Open", ":/icons/dir", 80);
    window->connect(button, &QPushButton::clicked, window, &callbackOpenDirectory);
}


void callbackOpenDirectory()
{
    QString path = QString::fromStdString(Data::Winner::getInstance()->getOutputDir());
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}


void openWindowUpdate(QWidget *parent)
{
    Tools::Window *updateWindow = new Notification("Update", "An update has been found, do you want to install it ?", PATH_DEFAULT_NOTIFICATION_SOUND, parent);

    addWindowButtonValidate(updateWindow);
    addWindowButtonCancel(updateWindow);

    (*updateWindow)();
    if (updateWindow->hasValidate()) {
        Utils::createProcess(std::filesystem::current_path().string() + '/' + GNCAPP_NAME + "_Updater.exe");
    }
}

void openWindowNotificationGeneration(QWidget *parent)
{
    Tools::Window *updateWindow = new Notification("Game'n Chill App Notification", "Winner image generation done", PATH_DEFAULT_NOTIFICATION_SOUND, parent);

    addWindowButtonOpenDir(updateWindow);
    addWindowButtonValidate(updateWindow);

    (*updateWindow)();
}

}
