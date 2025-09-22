
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/Notification.hpp"
#include "Update/Update.hpp"

namespace GNCApp::UI::Windows
{

Primary::Primary(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Mario Kart Top Generator");
    setMinimumWidth(800);

    this->_central = new QWidget(this);
    this->setCentralWidget(this->_central);
    this->_layout = new QVBoxLayout(this->_central);
    this->_tabs = new QTabWidget(this);

    this->_pageWinner = new PageWinner(this->_central);
    this->_tabs->addTab(this->_pageWinner, "Winner");

    this->_pageBracket = new PageBracket(this->_central);
    this->_tabs->addTab(this->_pageBracket, "Bracket");

    this->_layout->addWidget(this->_tabs);
}

Primary::~Primary()
{
}

void Primary::lockSize()
{
    adjustSize();
    setFixedSize(size());
}

void Primary::checkUpdate()
{
    GNCApp::Update::Manager updateManager(GNCAPP_API_URL);
    if (updateManager.needsUpdate()) {
        Notification updateWindow("Update", "An update has been found, do you want to install it ?", PATH_DEFAULT_NOTIFICATION_SOUND, this, WINDOW_TOOL_BUTTON_VALIDATE | WINDOW_TOOL_BUTTON_CANCEL);
        if (updateWindow.hasValidate()) {
            Utils::createProcess(std::filesystem::current_path().string() + '/' + GNCAPP_NAME + "_Updater.exe");
        }
    }
}

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

} // namespace MKTG
