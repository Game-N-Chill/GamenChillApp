
#include "UI/Windows/Primary.hpp"
#include "Logic/Logic.hpp"

namespace GNCApp::UI::Windows
{

BoxLoadExcel::BoxLoadExcel(QWidget *parent) :
    QWidget(parent)
{
    _box = new Tools::FGroupBox("Excel Loader", this);

    _btnLoad = createPushButton(this, " Load", "When clicked will load all infos from path excel file", ":/icons/load", 80, std::bind(&BoxLoadExcel::onLoadClicked, this));
    _btnLoad->setEnabled(false);
    _browserFile = new Tools::FileBrowser(this, _btnLoad);
    connect(_browserFile->getLineEdit(), &QLineEdit::textChanged, this, &BoxLoadExcel::onPathEdited);

    _box->addRow("Excel Path : ", _browserFile);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    _layout->addStretch();
    setLayout(_layout);
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

void BoxLoadExcel::onPathEdited(const QString &str)
{
    if (QFile::exists(str) && str.contains(EXCEL_FILE_EXT)) {
        this->_btnLoad->setEnabled(true);
    } else {
        this->_btnLoad->setEnabled(false);
    }
}

void BoxLoadExcel::onLoadClicked()
{
    Logic::loadExcelFile(this->_browserFile->getLineEdit()->text().toStdString());

    auto tabSolo = dynamic_cast<TabSolo *>(this->parentWidget());
    if (tabSolo != nullptr) {
        tabSolo->updateInfo();
    }
}

}
