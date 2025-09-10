
#include "UI/Windows/Primary.hpp"

namespace Generator::UI::Windows
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

//  PAGE WINNER
// *****************************************************************************

// void Primary::createPageWinner()
// {
//     this->_pageWinner = new QWidget(this);
//     this->_layoutWinner = new QVBoxLayout(this->_pageWinner);

//     createBoxAutoLoad();
//     createBoxInfo();
//     createBoxRank();

//     this->_btnWinner = new QPushButton("Generate", this);
//     this->_btnWinner->setFixedWidth(80);
//     this->_layoutWinner->addWidget(this->_btnWinner);

//     this->_tabs->addTab(this->_pageWinner, "Winner");
// }

// void Primary::createBoxAutoLoad()
// {
//     this->_boxAutoLoad = new Tools::FGroupBox("Auto Loader", this);

//     this->_btnLoad = new QPushButton("Load", this);
//     this->_btnLoad->setFixedWidth(60);
//     this->_browserFile = new Tools::Browser(this, this->_btnLoad);

//     this->_boxAutoLoad->add("Excel Path : ", this->_browserFile);
//     this->_layoutWinner->addWidget(this->_boxAutoLoad);
// }

// void Primary::createBoxInfo()
// {
//     this->_boxInfo = new Tools::FGroupBox("Information", this);

//     _title = new QLineEdit(this);
//     _title->setPlaceholderText("RIFIFI sur le Circuit #00");

//     _subtitle = new QLineEdit(this);
//     _subtitle->setPlaceholderText("Edition 150cc");

//     _date = new QDateEdit(this);
//     _date->setDisplayFormat("dd/MM/yyyy");
//     _date->setCalendarPopup(true);
//     _date->setDate(QDate::currentDate());

//     _playerCount = new QSpinBox(this);
//     _playerCount->setRange(1, 48);
//     _playerCount->setValue(16);

//     this->_boxInfo->add("Title : ", this->_title);
//     this->_boxInfo->add("SubTitle : ", this->_subtitle);
//     this->_boxInfo->add("Date : ", this->_date);
//     this->_boxInfo->add("Player Count : ", this->_playerCount);
//     this->_layoutWinner->addWidget(this->_boxInfo);
// }

// void Primary::createBoxRank()
// {
//     this->_boxPlayer = new Tools::FGroupBox("Players Rank", this);

//     _team = new QComboBox(this);
//     _team->addItem("Solo");
//     _team->addItem("Duo");
//     this->_boxPlayer->add("Team : ", this->_team);

//     for (size_t i = 0; i < 8; i++) {
//         QString pos = QString::number(i + 1);

//         this->_playerBox[i] = new Tools::HGroupBox("N°" + pos + " - Team Name", this);
//         this->_playerButton[i] = new QToolButton(this);
//         this->_playerButton[i]->setText("...");
//         this->_playerLabel[i] = new QLabel("Player " + pos + " (Mario)  |  Player " + QString::number(i + 9) + " (L.U.I.G.I.)");

//         this->_playerBox[i]->add(this->_playerLabel[i]);
//         this->_playerBox[i]->add(this->_playerButton[i]);
//         this->_boxPlayer->add("", this->_playerBox[i]);
//     }

//     this->_layoutWinner->addWidget(this->_boxPlayer);
// }

//  PAGE BRACKET
// *****************************************************************************

// void Primary::createPageBracket()
// {
//     this->_pageBracket = new QWidget(this);
//     this->_layoutBracket = new QVBoxLayout(this->_pageBracket);

//     this->_layoutBracket->addWidget(new QLabel("Brackets generator here"));

//     this->_tabs->addTab(this->_pageBracket, "Bracket");
// }

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
