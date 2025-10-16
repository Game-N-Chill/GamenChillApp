
#include "UI/Windows/Primary.hpp"
#include "Logic/Logic.hpp"
#include "UI/Windows/Common/ProgressBar.hpp"
#include "UI/Windows/Common/Notification.hpp"
#include <QDesktopServices>

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


void PageBracket::onLoadClicked()
{
    auto vec = Logic::loadPlayerFile(this->_browserFile->getLineEdit()->text().toStdString());

    for (auto &it : vec) {
        addPlayer(it);
    }
}

void PageBracket::onLoadEdited(const QString &str)
{
    if (QFile::exists(str)) {
        this->_btnLoad->setEnabled(true);
    } else {
        this->_btnLoad->setEnabled(false);
    }
}

void PageBracket::onSortClicked()
{
    if (this->_areaList->count() == 0)
        return;

    ProgressBar::open("Bracket Generation", &Logic::ProgressTask::loadTaskSeeding, &Logic::fetchSeeding, 10, this);

    this->_areaList->clear();
    for (size_t i = 0; i < Data::Seeding::getInstance()->getSize(); i++) {
        this->_areaList->addItem(getListItemName(i));
    }
}

void PageBracket::onModifyClicked()
{
    if (this->_areaList->count() == 0)
        return;

    Data::Seeding *dataSeeding = Data::Seeding::getInstance();

    QString ret = openWindowPlayerBracket("Player Modification", this, true, QString::fromStdString(dataSeeding->getPlayer(this->_areaIndex).getName()));
    if (!ret.isEmpty()) {
        dataSeeding->atPlayer(this->_areaIndex).setName(ret.toStdString());
        this->_areaList->item(this->_areaIndex)->setText(getListItemName(this->_areaIndex));
    }
}

void PageBracket::onMove(int indexSrc, int indexDest)
{
    Data::Seeding *dataSeeding = Data::Seeding::getInstance();
    dataSeeding->move(indexSrc, indexDest);

    this->_areaList->item(indexSrc)->setText(getListItemName(indexSrc));
    this->_areaList->item(indexDest)->setText(getListItemName(indexDest));
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

void PageBracket::addPlayer(std::string player)
{
    try {
        Data::Seeding::getInstance()->addPlayer(player);
        this->_areaIndex = this->_areaList->count();
        this->_areaList->addItem(getListItemName(this->_areaIndex));
        this->_areaList->setCurrentRow(this->_areaIndex);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void PageBracket::onAddClicked()
{
    if (this->_areaList->count() >= PLAYER_LIMIT)
        return;

    QString ret = openWindowPlayerBracket("New Player", this, false, "");
    addPlayer(ret.toStdString());
}

void PageBracket::onRemoveClicked()
{
    if (this->_areaList->count() == 0)
        return;

    Data::Seeding *dataSeeding = Data::Seeding::getInstance();
    dataSeeding->removePlayer(this->_areaIndex);
    this->_areaList->takeItem(this->_areaIndex);
    this->_areaIndex = this->_areaList->currentRow();

    for (size_t i = this->_areaIndex; i < this->_areaList->count(); i++) {
        this->_areaList->item(i)->setText(getListItemName(i));
    }
}

void PageBracket::onOutputEdited(const QString &str)
{
    Data::Seeding::getInstance()->setOutputPath(str.toStdString());
}

void PageBracket::onNumberEdited(int value)
{
    Data::Seeding::getInstance()->setNumber(value);
}

void PageBracket::onEditionChanged(int id, bool checked)
{
    if (!checked)
        return;

    if (id == this->_editionList.size() - 1) {
        this->_editionCustom->setEnabled(true);
        Data::Seeding::getInstance()->setEdition(this->_editionCustom->text().toStdString());
    } else {
        this->_editionCustom->setEnabled(false);
        Data::Seeding::getInstance()->setEdition(this->_edition->button(id)->text().toStdString());
    }
}

void PageBracket::onEditionCustomEdited(const QString &str)
{
    Data::Seeding::getInstance()->setEdition(str.toStdString());
}

void PageBracket::onGenerateClicked()
{
    ProgressBar::open("Bracket Generation", &Logic::ProgressTask::loadTaskBracket, &Logic::createBracketFile, 10, this);
    Notification::openGeneration(this, "Excel file succesfully generated", std::bind(&PageBracket::callbackOpenFile, this));
}

void PageBracket::callbackOpenFile()
{
    QString path = QString::fromStdString(Data::Seeding::getInstance()->getOutputPath());
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

}
