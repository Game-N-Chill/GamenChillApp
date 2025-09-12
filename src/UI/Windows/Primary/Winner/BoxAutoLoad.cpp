
#include "UI/Windows/Primary.hpp"

namespace Generator::UI::Windows
{

BoxAutoLoad::BoxAutoLoad(QWidget *parent) :
    QWidget(parent)
{
    _box = new Tools::FGroupBox("Auto Loader", this);

    _btnLoad = new QPushButton("Load", this);
    _btnLoad->setFixedWidth(60);
    connect(_btnLoad, &QToolButton::clicked, this, &BoxAutoLoad::onLoadClicked);
    _browserFile = new Tools::FileBrowser(this, _btnLoad);

    _box->addRow("Excel Path : ", _browserFile);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

void BoxAutoLoad::onLoadClicked()
{
    std::string path = this->_browserFile->getLineEdit()->text().toStdString();
    if (path.empty()) {
        std::cerr << "ERROR: path empty" << std::endl;
        return;
    }

    OpenXLSX::XLDocument file;
    file.open(path);
    if (!file.isOpen()) {
        std::cerr << "ERROR: file at " << path << " can't be open" << std::endl;
        return;
    }


    Data::Winner *dataWinner = Data::Winner::getInstance();
    std::string sheetName = file.workbook().worksheetNames()[0];
    OpenXLSX::XLWorksheet sheet = file.workbook().worksheet(sheetName);

    try {
        OpenXLSX::XLCell cellTitle = sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_TITLE));
        dataWinner->setTitle(cellTitle.value().get<std::string>());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: title format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        OpenXLSX::XLCell cellSubTitle = sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_SUBTITLE));
        dataWinner->setSubtitle(cellSubTitle.value().get<std::string>());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: subtitle format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        OpenXLSX::XLCell cellDate = sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_DATE));
        std::string date = cellDate.value().get<std::string>();
        if (date.empty()) {
            dataWinner->setDate(Utils::getTimeFormat("%d/%m/%Y"));
        } else {
            dataWinner->setDate(date);
        }
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: date format is incorrect (" << e.what() << ")" << std::endl;
    }

    size_t count = 0;
    for (int i = 0; i < 48; i++) {
        OpenXLSX::XLCell cellName = sheet.cell(OpenXLSX::XLCellReference(EXCEL_COL_PLAYER + std::to_string(EXCEL_LINE_FIRST + i)));
        std::string name = cellName.value().get<std::string>();

        if (name.empty()) {
            break;
        }

        // register top 8
        if (i < 8) {
            Generator::Data::Solo &solo = dataWinner->getTeamSolo(i);

            std::string character = sheet.cell(OpenXLSX::XLCellReference(EXCEL_COL_CHARACTER + std::to_string(EXCEL_LINE_FIRST + i))).value().get<std::string>();
            solo.players[0].setName(name);
            solo.players[0].setCharacter(character);
        }

        if (name != "-") {
            count++;
        }
    }
    dataWinner->setPlayerCount(count);

    file.close();

    dynamic_cast<PageWinner *>(this->parentWidget())->updateAllInfos();
}

}
