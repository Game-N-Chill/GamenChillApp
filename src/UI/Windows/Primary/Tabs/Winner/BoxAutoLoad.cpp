
#include "UI/Windows/Primary.hpp"
#include "Logic/Logic.hpp"

namespace GNCApp::UI::Windows
{

BoxAutoLoad::BoxAutoLoad(QWidget *parent) :
    QWidget(parent)
{
    _box = new Tools::FGroupBox("Auto Loader", this);

    _btnLoad = createPushButton(this, " Load", "When clicked will load all infos from path excel file", ":/icons/load", 80, std::bind(&BoxAutoLoad::onLoadClicked, this));
    _btnLoad->setEnabled(false);
    _browserFile = new Tools::FileBrowser(this, _btnLoad);
    connect(_browserFile->getLineEdit(), &QLineEdit::textChanged, this, &BoxAutoLoad::onPathEdited);

    _box->addRow("Excel Path : ", _browserFile);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

void BoxAutoLoad::onPathEdited(const QString &str)
{
    if (QFile::exists(str) && str.contains(EXCEL_FILE_EXT)) {
        this->_btnLoad->setEnabled(true);
    } else {
        this->_btnLoad->setEnabled(false);
    }
}

void BoxAutoLoad::onLoadClicked()
{
    Logic::loadExcelFile(this->_browserFile->getLineEdit()->text().toStdString());
    dynamic_cast<PageWinner *>(this->parentWidget())->updateAllInfos();
}

}
