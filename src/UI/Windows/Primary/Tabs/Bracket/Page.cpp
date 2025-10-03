
#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI::Windows
{

static QPushButton *createButton(PageBracket *parent, QString title, QString iconPath, int width, void (PageBracket::*func)())
{
    QPushButton *button = new QPushButton(title, parent);
    button->setIcon(QIcon(iconPath));
    button->setMinimumWidth(width);
    parent->connect(button, &QPushButton::clicked, parent, func);
    return button;
}

PageBracket::PageBracket(QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout(this);

    auto dataSeeding = Data::Seeding::getInstance();
    this->_areaList = new QListWidget(this);
    for (size_t i = 0; i < dataSeeding->getSize(); i++) {
        this->_areaList->addItem(QString::fromStdString(dataSeeding->getPlayer(i).getName()));
    }
    this->_areaList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_areaList->setMaximumHeight(300);
    connect(this->_areaList, &QListWidget::itemActivated, this, &PageBracket::onListItemSelected);
    connect(this->_areaList, &QListWidget::currentItemChanged, this, &PageBracket::onListItemChanged);
    this->_areaIndex = 0;

    this->_layoutButtons = new QHBoxLayout;
    this->_layoutLeft = new QHBoxLayout;
    this->_layoutRight = new QHBoxLayout;

    this->_buttonSort =     createButton(this, " Sort",     ":/icons/sort",     80, &PageBracket::onSortClicked);
    this->_buttonModify =   createButton(this, " Modify",   ":/icons/modify",   80, &PageBracket::onModifyClicked);
    this->_buttonUp =       createButton(this, "",          ":/icons/up",       1,  &PageBracket::onUpClicked);
    this->_buttonDown =     createButton(this, "",          ":/icons/down",     1,  &PageBracket::onDownClicked);
    this->_buttonAdd =      createButton(this, " Add",      ":/icons/add",      80, &PageBracket::onAddClicked);
    this->_buttonRemove =   createButton(this, " Remove",   ":/icons/remove",   80, &PageBracket::onRemoveClicked);

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
