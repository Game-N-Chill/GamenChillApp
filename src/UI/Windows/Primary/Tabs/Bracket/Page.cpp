
#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI::Windows
{

// static QPushButton *createButton(PageBracket *parent, QString title, QString toolTip, QString iconPath, int width, void (PageBracket::*func)())
// {
//     QPushButton *button = new QPushButton(title, parent);
//     button->setToolTip(toolTip);
//     button->setIcon(QIcon(iconPath));
//     button->setMinimumWidth(width);
//     parent->connect(button, &QPushButton::clicked, parent, func);
//     return button;
// }

PageBracket::PageBracket(QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout(this);

    auto dataSeeding = Data::Seeding::getInstance();
    this->_areaList = new QListWidget(this);
    for (size_t i = 0; i < dataSeeding->getSize(); i++) {
        this->_areaList->addItem(QString::fromStdString(dataSeeding->getPlayer(i).getName()));
    }
    this->_areaList->setCurrentRow(0);
    this->_areaList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_areaList->setMaximumHeight(300);
    connect(this->_areaList, &QListWidget::itemActivated, this, &PageBracket::onListItemSelected);
    connect(this->_areaList, &QListWidget::currentItemChanged, this, &PageBracket::onListItemChanged);
    this->_areaIndex = 0;

    this->_layoutButtons = new QHBoxLayout;
    this->_layoutLeft = new QHBoxLayout;
    this->_layoutRight = new QHBoxLayout;

    this->_buttonSort =     createPushButton(this, " Sort",     "Will sort players by their seeding",           ":/icons/sort",     80, std::bind(&PageBracket::onSortClicked, this));
    this->_buttonModify =   createPushButton(this, " Modify",   "Will open a window to change selected player", ":/icons/modify",   80, std::bind(&PageBracket::onModifyClicked, this));
    this->_buttonUp =       createPushButton(this, "",          "Will move selected up from 1 step",            ":/icons/up",       1,  std::bind(&PageBracket::onUpClicked, this));
    this->_buttonDown =     createPushButton(this, "",          "Will move selected down from 1 step",          ":/icons/down",     1,  std::bind(&PageBracket::onDownClicked, this));
    this->_buttonAdd =      createPushButton(this, " Add",      "Will open a window to add a new player",       ":/icons/add",      80, std::bind(&PageBracket::onAddClicked, this));
    this->_buttonRemove =   createPushButton(this, " Remove",   "Will remove selected player",                  ":/icons/remove",   80, std::bind(&PageBracket::onRemoveClicked, this));

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

    this->_separator01 = new QFrame(this);
    this->_separator01->setFrameShape(QFrame::HLine);   // horizontal line
    this->_separator01->setFrameShadow(QFrame::Sunken); // or QFrame::Raised
    this->_outputLabel = new QLabel("Output directory:", this);
    this->_output = new Tools::DirBrowser(this);
    this->_output->getLineEdit()->setText(QString::fromStdString(dataSeeding->getOutputPath()));
    connect(this->_output->getLineEdit(), &QLineEdit::textChanged, this, &PageBracket::onOutputEdited);
    this->_editionLabel = new QLabel("Edition:", this);
    this->_edition = new QSpinBox(this);
    this->_edition->setRange(1, 999);
    this->_edition->setValue(dataSeeding->getEdition());
    connect(this->_edition, &QSpinBox::valueChanged, this, &PageBracket::onEditionEdited);

    this->_separator02 = new QFrame(this);
    this->_separator02->setFrameShape(QFrame::HLine);   // horizontal line
    this->_separator02->setFrameShadow(QFrame::Sunken); // or QFrame::Raised
    this->_buttonGenerator = createPushButton(this, " Generate", "Will generate excel file with player list setup", ":/icons/generate", 100, std::bind(&PageBracket::onGenerateClicked, this));

    this->_layout->addWidget(this->_areaList);
    this->_layout->addLayout(this->_layoutButtons);
    this->_layout->addWidget(this->_separator01);
    this->_layout->addWidget(this->_outputLabel);
    this->_layout->addWidget(this->_output);
    this->_layout->addWidget(this->_editionLabel);
    this->_layout->addWidget(this->_edition);
    this->_layout->addWidget(this->_separator02);
    this->_layout->addWidget(this->_buttonGenerator);
    this->_layout->addStretch();
}

}
