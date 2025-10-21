
#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI::Windows
{

TabSolo::TabSolo(QWidget *parent, BoxInfo *info) :
    QWidget(parent)
{
    _ptrInfo = info;
    _layout = new QVBoxLayout(this);

    _loadExcel = new BoxLoadExcel(this);
    _layout->addWidget(_loadExcel);

    _rank = new BoxRank(1, this);
    _layout->addWidget(_rank);

    _layout->addStretch();
}

void TabSolo::updateInfo()
{
    _rank->updateInfo();
    _ptrInfo->updateInfo();
}

} // namespace GNCApp::UI::Window
