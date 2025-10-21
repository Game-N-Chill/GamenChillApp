
#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI::Windows
{

void PageBracket::createBoxAutoLoad()
{
    this->_boxAutoLoad = new Tools::FGroupBox("Auto Loader", this);

    this->_btnLoad = createPushButton(this, " Load", "When clicked will load all infos from path file", ":/icons/load", 80, std::bind(&PageBracket::onLoadClicked, this));
    this->_btnLoad->setEnabled(false);
    this->_browserFile = new Tools::FileBrowser(this, this->_btnLoad);
    connect(this->_browserFile->getLineEdit(), &QLineEdit::textChanged, this, &PageBracket::onLoadEdited);

    this->_boxAutoLoad->addRow("Player List Path : ", _browserFile);
}

void PageBracket::createBoxSeeding()
{
    auto dataSeeding = Data::Seeding::getInstance();

    this->_boxSeeding = new Tools::VGroupBox("Seeding", this);

    this->_areaList = new QListWidget(this);
    for (size_t i = 0; i < dataSeeding->getSize(); i++) {
        this->_areaList->addItem(getListItemName(i));
    }
    this->_areaList->setCurrentRow(0);
    this->_areaList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_areaList->setFixedHeight(300);
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

    this->_boxSeeding->addWidget(this->_areaList);
    this->_boxSeeding->addLayout(this->_layoutButtons);
}

void PageBracket::createBoxInfo()
{
    auto dataSeeding = Data::Seeding::getInstance();

    this->_boxInfo = new Tools::FGroupBox("Information", this);

    this->_output = new Tools::DirBrowser(this);
    this->_output->getLineEdit()->setText(QString::fromStdString(dataSeeding->getOutputPath()));
    connect(this->_output->getLineEdit(), &QLineEdit::textChanged, this, &PageBracket::onOutputEdited);

    this->_number = new QSpinBox(this);
    this->_number->setRange(1, 999);
    this->_number->setValue(dataSeeding->getNumber());
    connect(this->_number, &QSpinBox::valueChanged, this, &PageBracket::onNumberEdited);

    this->_editionLayout = new QVBoxLayout;
    this->_editionList = {
        "150cc",
        "200cc",
        "Miroir",
        "Bataille",
        "Autres:"
    };
    this->_edition = new QButtonGroup(this);
    this->_edition->setExclusive(true);
    for (int i = 0; i < this->_editionList.size(); i++) {
        QRadioButton *radio = new QRadioButton(this->_editionList[i]);
        this->_editionLayout->addWidget(radio);
        this->_edition->addButton(radio, i);
        if (i == 0) {
            radio->setChecked(true);
        }
    }
    connect(this->_edition, &QButtonGroup::idToggled, this, &PageBracket::onEditionChanged);
    this->_editionCustom = new QLineEdit(this);
    this->_editionCustom->setEnabled(false);
    connect(this->_output->getLineEdit(), &QLineEdit::textChanged, this, &PageBracket::onEditionCustomEdited);

    this->_boxInfo->addRow("Output directory:", this->_output);
    this->_boxInfo->addRow("Edition Number:", this->_number);
    this->_boxInfo->addRow("Edition Particularity:", this->_editionLayout);
    this->_boxInfo->addRow("", this->_editionCustom);
}


PageBracket::PageBracket(QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout(this);

    createBoxAutoLoad();
    createBoxSeeding();
    createBoxInfo();
    this->_buttonGenerator = createPushButton(this, " Generate", "Will generate excel file with player list setup", ":/icons/generate", 100, std::bind(&PageBracket::onGenerateClicked, this));

    this->_layout->addWidget(this->_boxAutoLoad);
    this->_layout->addWidget(this->_boxSeeding);
    this->_layout->addWidget(this->_boxInfo);
    this->_layout->addWidget(this->_buttonGenerator);
    this->_layout->addStretch();
}

QString PageBracket::getListItemName(size_t index)
{
    std::string str = "#";
    if (index + 1 < 10)
        str += "0";
    str += std::to_string(index + 1);
    str += '\t';
    str += Data::Seeding::getInstance()->getPlayer(index).getName();
    return QString::fromStdString(str);
}

}
