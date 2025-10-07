
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/Common/Notification.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace GNCApp::UI::Windows
{

//  MENUS
// *****************************************************************************

void Primary::createMenus()
{
    auto fileMenu = menuBar()->addMenu("&File");

    // Quit action
    QAction *quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &Primary::onQuit);

    fileMenu->addAction(quitAction);
}

//  CALLBACK
// *****************************************************************************

void Primary::onQuit()
{
    // Ask confirmation before quitting
    auto reply = QMessageBox::question(
        this, "Quit", "Do you really want to quit?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        qApp->quit();
    }
}

}
