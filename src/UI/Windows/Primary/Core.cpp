
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/Notification.hpp"
#include "Update/Update.hpp"
#include <filesystem>

namespace fs = std::filesystem;
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
    try {
        GNCApp::Update::Manager updateManager(UPDATE_API_URL);
        if (updateManager.needsUpdate()) {
            openWindowUpdate(this);
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "ERROR: filesystem: " << e.what() << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
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
