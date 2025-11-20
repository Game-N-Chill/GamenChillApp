
#include <QString>
#include <QDesktopServices>
#include <QUrl>

#include "GUI/Windows/Common/Common.hpp"
#include "GUI/Windows/Common/Notification.hpp"

namespace GNCApp::GUI::Windows
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

QPushButton *addWindowButtonOpen(Tools::Window *window, std::function<void()> callback)
{
    QPushButton *button = createPushButton(window, " Open", "", ":/icons/dir", 80, callback);
    window->addButton(button);
    return button;
}

}
