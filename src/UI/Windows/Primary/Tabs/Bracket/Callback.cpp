
#include "UI/Windows/Primary.hpp"
#include "Logic/Logic.hpp"
#include "UI/Windows/Common/Notification.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace GNCApp::UI::Windows
{

static QString openWindowPlayerBracket(QString title, PageBracket *parent, bool buttonEnabled, QString playerName)
{
    auto dataWinner = Data::Winner::getInstance();
    QString ret;

    Tools::Window *window =  new PlayerBracket(title, parent);
    auto button = addWindowButtonValidate(window);
    dynamic_cast<PlayerBracket *>(window)->setupInfo(button, buttonEnabled, playerName);
    addWindowButtonCancel(window);

    (*window)();
    if (window->hasValidate()) {
        ret = dynamic_cast<PlayerBracket *>(window)->getNameString();
    }

    delete window;
    return ret;
}


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
    if (this->_areaList->count() == 0)
        return;

    return;

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
    if (this->_areaList->count() == 0)
        return;

    Data::Seeding *dataSeeding = Data::Seeding::getInstance();

    QString ret = openWindowPlayerBracket("Player Modification", this, true, QString::fromStdString(dataSeeding->getPlayer(this->_areaIndex).getName()));
    if (!ret.isEmpty()) {
        dataSeeding->atPlayer(this->_areaIndex).setName(ret.toStdString());
        this->_areaList->item(this->_areaIndex)->setText(ret);
    }
}

void PageBracket::onMove(int indexSrc, int indexDest)
{
    Data::Seeding *dataSeeding = Data::Seeding::getInstance();
    dataSeeding->move(indexSrc, indexDest);

    this->_areaList->item(indexSrc)->setText(QString::fromStdString(dataSeeding->getPlayer(indexSrc).getName()));
    this->_areaList->item(indexDest)->setText(QString::fromStdString(dataSeeding->getPlayer(indexDest).getName()));
    this->_areaIndex = indexDest;
    this->_areaList->setCurrentRow(indexDest);
}

void PageBracket::onUpClicked()
{
    if (this->_areaList->count() == 0)
        return;
    if (this->_areaIndex <= 0)
        return;

    onMove(this->_areaIndex, this->_areaIndex - 1);
}

void PageBracket::onDownClicked()
{
    if (this->_areaList->count() == 0)
        return;
    if (this->_areaIndex >= this->_areaList->count() - 1)
        return;

    onMove(this->_areaIndex, this->_areaIndex + 1);
}

void PageBracket::onAddClicked()
{
    if (this->_areaList->count() >= PLAYER_LIMIT)
        return;

    Data::Seeding *dataSeeding = Data::Seeding::getInstance();

    QString ret = openWindowPlayerBracket("New Player", this, false, "");

    dataSeeding->addPlayer(ret.toStdString(), 0.0f);
    this->_areaList->addItem(ret);
    this->_areaIndex = this->_areaList->count() - 1;
    this->_areaList->setCurrentRow(this->_areaIndex);
}

void PageBracket::onRemoveClicked()
{
    if (this->_areaList->count() == 0)
        return;

    Data::Seeding *dataSeeding = Data::Seeding::getInstance();
    dataSeeding->removePlayer(this->_areaIndex);
    this->_areaList->takeItem(this->_areaIndex);
    this->_areaIndex = this->_areaList->currentRow();
}

void PageBracket::onOutputEdited(const QString &str)
{
    Data::Seeding::getInstance()->setOutputPath(str.toStdString());
}

void PageBracket::onEditionEdited(int value)
{
    Data::Seeding::getInstance()->setEdition(value);
}

void PageBracket::onGenerateClicked()
{
    Logic::createBracketFile();
    Notification::openGeneration(this);
}

}
