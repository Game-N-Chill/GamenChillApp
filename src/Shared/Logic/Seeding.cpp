
#include "Shared.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace GNCApp::Logic
{

static bool downloadFile(std::string pathFile)
{
    try {
        GGL::Request req;
        req.SetOpt(CURLOPT_USERAGENT, "Mozilla/5.0");
        req.Download(SEEDING_URL, pathFile);
    } catch (const fs::filesystem_error &e) {
        Error() << "ERROR: filesystem: " << e.what() << GGL::end;
        return false;
    } catch (const std::runtime_error &e) {
        Error() << "ERROR: " << e.what() << GGL::end;
        return false;
    } catch (const std::exception &e) {
        Error() << "ERROR: " << e.what() << GGL::end;
        return false;
    }
    return true;
}

void fetchSeeding()
{
    std::string pathFile =  GGL::getTempDir() + '/' + GNCAPP_NAME + '/' + SEEDING_FILE_NAME;
    std::map<std::string, float> players;

    if (!downloadFile(pathFile)) {
        RESET_PROGRESS_TASK;
        return;
    }
    DO_PROGRESS_TASK;

    OpenXLSX::XLDocument file;
    file.open(pathFile);
    if (!file.isOpen()) {
        Error() << "ERROR: file at " << pathFile << " can't be open" << GGL::end;
        RESET_PROGRESS_TASK;
        return;
    }

    OpenXLSX::XLWorksheet sheet = file.workbook().worksheet(SEEDING_WORKSHEET);

    for (size_t i = 2; i < 1000; i++) {
        try {
            std::string name = sheet.cell(OpenXLSX::XLCellReference("A" + std::to_string(i))).value();
            float seeding = sheet.cell(OpenXLSX::XLCellReference("B" + std::to_string(i))).value();
            players[ GGL::stringToLower(name)] = seeding;
        } catch (const OpenXLSX::XLValueTypeError &e) {
            Error() << "WARNING: cell format is incorrect (" << e.what() << ")" << GGL::end;
            break;
        }
    }

    file.close();
    DO_PROGRESS_TASK;

    Data::Seeding::getInstance()->sort(players);
    DO_PROGRESS_TASK;
}

}
