
#include "MKTG.hpp"
#include <algorithm>

namespace MKTG
{

//  Team GETTER/SETTER
// *****************************************************************************

Solo Generator::getSoloInfo(size_t rank)
{
    return this->getTeamInfo<1>(rank, this->_solo);
}

void Generator::setSoloInfo(size_t rank, std::string character, std::string name)
{
    this->setTeamInfo<1>(rank, "", 0, character, name, this->_solo);
}

void Generator::printSolo()
{
    size_t len = 0;

    for (size_t i = 1; i <= this->_solo.size(); i++) {
        Solo team = getSoloInfo(i);
        std::string skin = team->players[0].getSkin();
        if (skin != CHARACTER_DEFAULT_NAME) {
            len = std::max<size_t>(len, team->players[0].character.size() + skin.size() + 3); // +3 for space and parenthesis
        } else {
            len = std::max<size_t>(len, team->players[0].character.size());
        }
    }
    len += 2;

    for (size_t i = 1; i <= this->_solo.size(); i++) {
        Solo team = getSoloInfo(i);

        std::string character = team->players[0].character;
        if (team->players[0].getSkin() != CHARACTER_DEFAULT_NAME) {
            character += " (" + team->players[0].getSkin() + ')';
        }
        std::cout << std::left << "-- Player  #" << std::setw(4) << team->rank << std::setw(len) << character << team->players[0].name << std::endl;
    }
}

//  Image Creation
// *****************************************************************************

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

void Generator::createSolo()
{
    this->createImage<1>(CANVA_SOLO_PATH, this->_solo);
}

} // namespace MKTG
