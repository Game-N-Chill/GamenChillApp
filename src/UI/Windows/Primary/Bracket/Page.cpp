
#include "UI/Windows/Primary.hpp"
#include <QHeaderView>

namespace GNCApp::UI::Windows
{

PageBracket::PageBracket(QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout(this);

    this->_areaList = new QListWidget(this);
    for (int i = 1; i <= 48; i++) {
        this->_areaList->addItem(QString("line %1").arg(i));
    }
    this->_areaList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_areaList->setMaximumHeight(300);

    this->_layoutButtons = new QHBoxLayout;
    this->_layoutLeft = new QHBoxLayout;
    this->_layoutRight = new QHBoxLayout;

    this->_buttonSort = new QPushButton(" Sort", this);
    this->_buttonSort->setIcon(QIcon(":/icons/sort"));
    this->_buttonSort->setMinimumWidth(80);
    this->_buttonModify = new QPushButton(" Modify", this);
    this->_buttonModify->setIcon(QIcon(":/icons/modify"));
    this->_buttonModify->setMinimumWidth(80);
    this->_buttonUp = new QPushButton(this);
    this->_buttonUp->setIcon(QIcon(":/icons/up"));
    this->_buttonDown = new QPushButton(this);
    this->_buttonDown->setIcon(QIcon(":/icons/down"));
    this->_buttonAdd = new QPushButton(" Add", this);
    this->_buttonAdd->setIcon(QIcon(":/icons/add"));
    this->_buttonAdd->setMinimumWidth(80);
    this->_buttonRemove = new QPushButton(" Remove", this);
    this->_buttonRemove->setIcon(QIcon(":/icons/remove"));
    this->_buttonRemove->setMinimumWidth(80);

    this->_layoutLeft->addWidget(this->_buttonSort);
    this->_layoutLeft->addWidget(this->_buttonModify);
    this->_layoutLeft->addWidget(this->_buttonUp);
    this->_layoutLeft->addWidget(this->_buttonDown);
    this->_layoutLeft->addStretch();
    this->_layoutRight->addStretch();
    this->_layoutRight->addWidget(this->_buttonAdd);
    this->_layoutRight->addWidget(this->_buttonRemove);

    QWidget *leftWidget = new QWidget;
    leftWidget->setLayout(this->_layoutLeft);
    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(this->_layoutRight);
    this->_layoutButtons->addWidget(leftWidget);
    this->_layoutButtons->addWidget(rightWidget);

    this->_layout->addWidget(this->_areaList);
    this->_layout->addLayout(this->_layoutButtons);
    this->_layout->addStretch();
}

}
