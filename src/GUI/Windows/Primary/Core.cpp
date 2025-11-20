
#include "GUI/Windows/Primary.hpp"
#include "GUI/Windows/Common/Notification.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace GNCApp::GUI::Windows
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
    this->_tabs->addTab(this->_pageWinner, "Top 8");

    this->_pageBracket = new PageBracket(this->_central);
    this->_tabs->addTab(this->_pageBracket, "Bracket");

    this->_layout->addWidget(this->_tabs);

    createMenus();
    loadConfig();
}

Primary::~Primary()
{
}

void Primary::lockSize()
{
    adjustSize();
    setMinimumSize(size());
}

void Primary::loadConfig()
{
    auto dataConfig = Data::Config::getInstance();

    std::string theme = dataConfig->getTheme();
    setTheme(theme);

    if (theme.empty()) {
        theme = "Default";
    }
    for (auto &action : this->_menuTheme->actions()) {
        if (theme.find(action->text().toStdString()) != std::string::npos) {
            action->setChecked(true);
            break;
        }
    }
}


void Primary::setTheme(const char *path)
{
    setTheme(QString(path));
}

void Primary::setTheme(std::string path)
{
    setTheme(QString::fromStdString(path));
}

void Primary::setTheme(QString path)
{
    auto dataConfig = Data::Config::getInstance();

    if (path.isEmpty()) {
        qApp->setStyleSheet("");
        dataConfig->setTheme("");
        return;
    }

    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
        dataConfig->setTheme(path.toStdString());
    } else {
        qApp->setStyleSheet("");
        dataConfig->setTheme("");
    }
}

} // namespace MKTG
