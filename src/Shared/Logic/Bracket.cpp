
#include "Shared.hpp"
#include <string>

namespace GNCApp::Logic
{

std::vector<std::string> loadPlayerFile(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("can't open file at path: " + path);

    std::vector<std::string> vec;
    std::string buf;
    while (std::getline(file, buf)) {
        vec.push_back(buf);
    }

    return vec;
}


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
    path.insert(path.find_last_of('.'), "__" +  GGL::getTimeFormat("%d_%m_%Y__%H_%M_%S"));
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
        Error() << "Could not copy file: " << e.what() << '\n';
        return;
    }
    DO_PROGRESS_TASK;

    OpenXLSX::XLDocument file;
    file.open(path);
    if (!file.isOpen()) {
        Logic::ProgressTask::getInstance()->reset();
        Error() << "ERROR: file at " << path << " can't be open" << GGL::end;
        return;
    }

    std::string sheetName = file.workbook().worksheetNames()[0];
    OpenXLSX::XLWorksheet sheet = file.workbook().worksheet(sheetName);

    try {
        sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_TITLE)).value() = "RIFIFI sur le Circuit #" + std::to_string(dataSeeding->getNumber());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        Error() << "WARNING: cell format is incorrect (" << e.what() << ")" << GGL::end;
    }

    try {
        sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_SUBTITLE)).value() = dataSeeding->getEdition();
    } catch (const OpenXLSX::XLValueTypeError &e) {
        Error() << "WARNING: cell format is incorrect (" << e.what() << ")" << GGL::end;
    }

    try {
        sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_DATE)).value() =  GGL::getTimeFormat("%d/%m/%Y");
    } catch (const OpenXLSX::XLValueTypeError &e) {
        Error() << "WARNING: cell format is incorrect (" << e.what() << ")" << GGL::end;
    }
    DO_PROGRESS_TASK;

    for (size_t i = 0; i < size; i++) {
        try {
            sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_SEEDING + std::to_string(EXCEL_LINE_FIRST + i))).value() = dataSeeding->getPlayer(i).getName();
            sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_PRESENCE + std::to_string(EXCEL_LINE_FIRST + i))).value() = 1;
        } catch (const OpenXLSX::XLValueTypeError &e) {
            Error() << "WARNING: cell format is incorrect (" << e.what() << ")" << GGL::end;
        }
    }
    DO_PROGRESS_TASK;

    file.save();
    DO_PROGRESS_TASK;
    file.close();
}

}
