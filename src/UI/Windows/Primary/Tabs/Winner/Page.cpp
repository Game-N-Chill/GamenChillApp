
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/Common/Notification.hpp"
#include "Logic/Logic.hpp"

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
}

void PageWinner::updateAllInfos()
{
    this->_info->updateAllInfos();
    this->_rank->updateAllInfos();
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

void PageWinner::onGenerateClicked()
{
    if (this->_rank->getTeamSelected() == 0) { // Solo
        Logic::createWinnerSoloImage();
    } else { // Duo
        Logic::createWinnerDuoImage();
    }

    Notification::openGeneration(this);
}

}
