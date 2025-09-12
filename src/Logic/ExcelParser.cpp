
#include "Logic.hpp"

namespace Generator
{

void loadExcelFile(std::string path)
{
    if (path.empty()) {
        std::cerr
        return;
    }
}

}



void Generator::LoadSolo(std::string excelPath, std::string sheetName)
{
    if (excelPath.empty()) {
        return;
    }

    OpenXLSX::XLDocument file;
    file.open(excelPath);
    if (!file.isOpen()) {
        std::cerr << "ERROR: file " << excelPath << "can't be open" << std::endl;
        return;
    }

    if (sheetName.empty()) {
        sheetName = file.workbook().worksheetNames()[0];
    }
    OpenXLSX::XLWorksheet sheet = file.workbook().worksheet(sheetName);

    try {
        OpenXLSX::XLCell cellTitle = sheet.cell(OpenXLSX::XLCellReference(CELL_TITLE));
        this->setTitle(cellTitle.value().get<std::string>());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: title format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        OpenXLSX::XLCell cellSubTitle = sheet.cell(OpenXLSX::XLCellReference(CELL_SUBTITLE));
        this->setSubtitle(cellSubTitle.value().get<std::string>());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: subtitle format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        OpenXLSX::XLCell cellDate = sheet.cell(OpenXLSX::XLCellReference(CELL_DATE));
        std::string date = cellDate.value().get<std::string>();
        if (date.empty()) {
            this->setDate(Utils::getTimeFormat("%d/%m/%Y"));
        } else {
            this->setDate(date);
        }
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: date format is incorrect (" << e.what() << ")" << std::endl;
    }

    size_t count = 0;
    for (int i = 0; i < 48; i++) {
        OpenXLSX::XLCell cellName = sheet.cell(OpenXLSX::XLCellReference(COL_PLAYER + std::to_string(LINE_FIRST + i)));
        std::string name = cellName.value().get<std::string>();

        if (name.empty()) {
            break;
        }

        if (i < 8) {
            std::string character = sheet.cell(OpenXLSX::XLCellReference(COL_CHARACTER + std::to_string(LINE_FIRST + i))).value().get<std::string>();
            this->setSoloInfo(i + 1, character, name);
        }

        if (name != "-") {
            count++;
        }
    }
    this->setPlayerCount(count);

    file.close();
}
