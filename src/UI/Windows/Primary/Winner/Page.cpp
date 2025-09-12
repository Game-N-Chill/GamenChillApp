
#include "UI/Windows/Primary.hpp"

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
    std::cout << "generate clicked" << std::endl;
}

}
