
#include <QString>
#include <QDesktopServices>
#include <QUrl>

#include "UI/Windows/Common/Shared.hpp"
#include "UI/Windows/Common/Notification.hpp"
#include "Data/Data.hpp"

namespace GNCApp::UI::Windows
{

QPushButton *createPushButton(QWidget *parent, QString title, QString toolTip, QString iconPath, int width, std::function<void()> func)
{
    QPushButton *button = new QPushButton(title, parent);

    if (!toolTip.isEmpty())
        button->setToolTip(toolTip);
    if (!iconPath.isEmpty())
        button->setIcon(QIcon(iconPath));
    if (width > 0)
        button->setMinimumWidth(width);
    if (func != nullptr)
        parent->connect(button, &QPushButton::clicked, parent, func);
    return button;
}

static void callbackOpenDirectory()
{
    QString path = QString::fromStdString(Data::Winner::getInstance()->getOutputDir());
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

QPushButton *addWindowButtonValidate(Tools::Window *window)
{
    QPushButton *button = createPushButton(window, " OK", "", ":/icons/validate", 80, std::bind(&QDialog::accept, window));
    window->addButton(button);
    return button;
}

QPushButton *addWindowButtonCancel(Tools::Window *window)
{
    QPushButton *button = createPushButton(window, " Cancel", "", ":/icons/remove", 80, std::bind(&QDialog::reject, window));
    window->addButton(button);
    return button;
}

QPushButton *addWindowButtonOpenDir(Tools::Window *window)
{
    QPushButton *button = createPushButton(window, " Open", "", ":/icons/dir", 80, &callbackOpenDirectory);
    window->addButton(button);
    return button;
}

}
