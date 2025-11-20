
#include "GUI/Windows/Primary.hpp"

namespace GNCApp::GUI::Windows
{

TabDuo::TabDuo(QWidget *parent, BoxInfo *info) :
    QWidget(parent)
{
    _ptrInfo = info;
    _layout = new QVBoxLayout(this);

    _loadWeb = new BoxLoadWeb(this);
    _layout->addWidget(_loadWeb);

    _rank = new BoxRank(2, this);
    _layout->addWidget(_rank);

    _layout->addStretch();
}

void TabDuo::updateInfo()
{
    _rank->updateInfo();
    _ptrInfo->updateInfo();
}

} // namespace GNCApp::GUI::Window
