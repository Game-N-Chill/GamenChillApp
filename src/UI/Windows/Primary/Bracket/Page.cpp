
#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI::Windows
{

PageBracket::PageBracket(QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout(this);

    this->_layout->addWidget(new QLabel("Brackets generator here"));
}

}
