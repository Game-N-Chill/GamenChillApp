
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/Common/Notification.hpp"
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

    createMenus();
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

} // namespace MKTG
