
#include "UI/Windows/Primary.hpp"
#include "Logic.hpp"

namespace Generator::UI::Windows
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

    _btnWinner = new QPushButton("Generate", this);
    _btnWinner->setFixedWidth(80);
    connect(_btnWinner, &QPushButton::clicked, this, &PageWinner::onGenerateClicked);
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
}

}
