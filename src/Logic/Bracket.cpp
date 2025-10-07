
#include "Logic/Logic.hpp"
#include "Data/Data.hpp"

namespace GNCApp::Logic
{

static std::string getTemplateFilePath(size_t size)
{
    std::string path = EXCEL_FILE_PATH;
    if (size > 32)
        path += "48";
    else if (size > 24)
        path += "32";
    else if (size > 16)
        path += "24";
    else
        path += "16";
    path += EXCEL_FILE_EXT;
    return path;
}

static std::string getFilePath(std::string path, std::string pathTemplate)
{
    path += pathTemplate.substr(pathTemplate.find_last_of('/'));
    path.insert(path.find_last_of('.'), "__" + Utils::getTimeFormat("%d_%m_%Y__%H_%M_%S"));
    return path;
}

void createBracketFile()
{
    Data::Seeding *dataSeeding = Data::Seeding::getInstance();
    std::string pathTemplate = getTemplateFilePath(dataSeeding->getSize());
    std::string path = getFilePath(dataSeeding->getOutputPath(), pathTemplate);
    size_t size = dataSeeding->getSize();

    try {
        std::filesystem::copy_file(pathTemplate, path, std::filesystem::copy_options::overwrite_existing);
    } catch (std::filesystem::filesystem_error &e) {
        RESET_PROGRESS_TASK;
        std::cerr << "Could not copy file: " << e.what() << '\n';
        return;
    }
    DO_PROGRESS_TASK;

    OpenXLSX::XLDocument file;
    file.open(path);
    if (!file.isOpen()) {
        Logic::ProgressTask::getInstance()->reset();
        std::cerr << "ERROR: file at " << path << " can't be open" << std::endl;
        return;
    }

    std::string sheetName = file.workbook().worksheetNames()[0];
    OpenXLSX::XLWorksheet sheet = file.workbook().worksheet(sheetName);

    try {
        sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_TITLE)).value() = "RIFIFI sur le Circuit #" + std::to_string(dataSeeding->getNumber());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: cell format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_SUBTITLE)).value() = dataSeeding->getEdition();
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: cell format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_DATE)).value() = Utils::getTimeFormat("%d/%m/%Y");
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: cell format is incorrect (" << e.what() << ")" << std::endl;
    }
    DO_PROGRESS_TASK;

    for (size_t i = 0; i < size; i++) {
        try {
            sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_SEEDING + std::to_string(EXCEL_LINE_FIRST + i))).value() = dataSeeding->getPlayer(i).getName();
            sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_PRESENCE + std::to_string(EXCEL_LINE_FIRST + i))).value() = 1;
        } catch (const OpenXLSX::XLValueTypeError &e) {
            std::cerr << "WARNING: cell format is incorrect (" << e.what() << ")" << std::endl;
        }
    }
    DO_PROGRESS_TASK;

    file.save();
    DO_PROGRESS_TASK;
    file.close();
}

}
