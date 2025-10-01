
#include "UI/Windows/Primary.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace GNCApp::UI::Windows
{

void PageBracket::onListItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    this->_areaIndex = this->_areaList->row(current);
}

void PageBracket::onListItemSelected(QListWidgetItem *item)
{
    onModifyClicked();
}


void PageBracket::onSortClicked()
{
    try {
        std::string path = Utils::getTempDir() + '/' + GNCAPP_TEMP_DIR + '/' + PROTON_API_FILE_NAME;

        Utils::Request req;
        req.SetOpt(CURLOPT_USERAGENT, "Mozilla/5.0");
        // req.SetHeader({"x-pm-appversion: web-drive@5.2.0+bdf7a938"});
        req.Download("https://onedrive.live.com/personal/8e2ad450607c91c5/_layouts/15/download.aspx?UniqueId=16486d8b%2Dfae0%2D4b61%2D8a6c%2Dc060c066edff", path);
    } catch (const fs::filesystem_error &e) {
        std::cerr << "ERROR: filesystem: " << e.what() << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    Utils::Request req;

    req.Download(PROTON_API_URL, Utils::getTempDir() + '/' + PROTON_API_FILE_NAME);
}

void PageBracket::onModifyClicked()
{
    std::cout << "modifying element index " << this->_areaIndex << " = " << this->_areaList->item(this->_areaIndex)->text().toStdString() << std::endl;
}

void PageBracket::onUpClicked()
{

}

void PageBracket::onDownClicked()
{

}

void PageBracket::onAddClicked()
{

}

void PageBracket::onRemoveClicked()
{

}


}
