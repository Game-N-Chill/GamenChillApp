
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/Common/ProgressBar.hpp"
#include "UI/Windows/Common/Notification.hpp"
#include "Logic/Logic.hpp"
#include <QDesktopServices>

namespace GNCApp::UI::Windows
{

// *****************************************************************************
//  CREATION
// *****************************************************************************

PageWinner::PageWinner(QWidget *parent) :
    QWidget(parent)
{
    _layout = new QVBoxLayout(this);

    _info = new BoxInfo(this);
    _layout->addWidget(_info);

    _tabs = new QTabWidget(this);
    _tabSolo = new TabSolo(this, _info);
    _tabs->addTab(_tabSolo, "Solo");
    _tabDuo = new TabDuo(this, _info);
    _tabs->addTab(_tabDuo, "Duo");
    _layout->addWidget(_tabs);

    _btnWinner = createPushButton(this, " Generate", "Will create top 8 image from data", ":/icons/generate", 80, std::bind(&PageWinner::onGenerateClicked, this));
    _layout->addWidget(_btnWinner);

    _layout->addStretch();
}

void PageWinner::updateInfo()
{
    std::cout << __func__ << std::endl;
    this->_info->updateInfo();
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

void caca()
{
}

void PageWinner::onGenerateClicked()
{
    std::function<void()> func = nullptr;
    if (this->_tabs->currentIndex() == 0) { // Solo
        func = &Logic::createWinnerSoloImage;
    } else { // Duo
        func = &Logic::createWinnerDuoImage;
    }

    ProgressBar::open("Top 8 Generation", &Logic::ProgressTask::loadTaskWinner, func, 10, this);
    Notification::openDirectory("Winner image generation done", this, std::bind(&PageWinner::callbackOpenDir, this));
}

void PageWinner::callbackOpenDir()
{
    QString path = QString::fromStdString(Data::Winner::getInstance()->getOutputDir());
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

}
