
#include "UI/Windows/Primary.hpp"
#include <QHeaderView>

namespace GNCApp::UI::Windows
{

PageBracket::PageBracket(QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout(this);

    this->_box = new Tools::HGroupBox("Information", this);
    this->_layoutLeft = new QVBoxLayout;
    this->_layoutRight = new QVBoxLayout;

    this->_areaList = new QListWidget(this);
    for (int i = 1; i <= 50; i++) {
        this->_areaList->addItem(QString("line %1").arg(i));
    }
    this->_areaList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_areaList->setMaximumHeight(300);

    this->_buttonAdd = new QPushButton("Add", this);
    this->_buttonAdd->setIcon(QIcon(":/icon/add.png"));
    this->_buttonRemove = new QPushButton("Remove", this);
    this->_buttonRemove->setIcon(QIcon(":/icon/remove.png"));
    this->_buttonModify = new QPushButton("Modify", this);
    this->_buttonModify->setIcon(QIcon(":/icon/modify.png"));

    this->_layoutLeft->addWidget(this->_areaList);
    this->_layoutRight->addWidget(this->_buttonAdd);
    this->_layoutRight->addWidget(this->_buttonRemove);
    this->_layoutRight->addWidget(this->_buttonModify);
    this->_box->addLayout(this->_layoutLeft);
    this->_box->addLayout(this->_layoutRight);

    this->_layout->addWidget(this->_box);
}

}
