
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

    _autoLoad = new BoxAutoLoad(this);
    _layout->addWidget(_autoLoad);

    _info = new BoxInfo(this);
    _layout->addWidget(_info);

    _rank = new BoxRank(this);
    _layout->addWidget(_rank);

    _btnWinner = createPushButton(this, " Generate", "Will create top 8 image from data", ":/icons/generate", 80, std::bind(&PageWinner::onGenerateClicked, this));
    _layout->addWidget(_btnWinner);

    _layout->addStretch();
}

void PageWinner::updateAllInfos()
{
    this->_info->updateAllInfos();
    this->_rank->updateAllInfos();
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
    if (this->_rank->getTeamSelected() == 0) { // Solo
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
