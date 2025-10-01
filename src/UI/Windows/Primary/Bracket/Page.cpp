
#include "UI/Windows/Primary.hpp"
#include <QHeaderView>
#include <filesystem>

namespace fs = std::filesystem;
namespace GNCApp::UI::Windows
{

PageBracket::PageBracket(QWidget *parent) :
    QWidget(parent)
{
    this->_layout = new QVBoxLayout(this);

    this->_areaList = new QListWidget(this);
    for (int i = 1; i <= 48; i++) {
        this->_areaList->addItem(QString("line %1").arg(i));
    }
    this->_areaList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_areaList->setMaximumHeight(300);

    this->_layoutButtons = new QHBoxLayout;
    this->_layoutLeft = new QHBoxLayout;
    this->_layoutRight = new QHBoxLayout;

    this->_buttonSort = new QPushButton(" Sort", this);
    this->_buttonSort->setIcon(QIcon(":/icons/sort"));
    this->_buttonSort->setMinimumWidth(80);
    connect(this->_buttonSort, &QPushButton::clicked, this, &PageBracket::onSortClicked);
    this->_buttonModify = new QPushButton(" Modify", this);
    this->_buttonModify->setIcon(QIcon(":/icons/modify"));
    this->_buttonModify->setMinimumWidth(80);
    this->_buttonUp = new QPushButton(this);
    this->_buttonUp->setIcon(QIcon(":/icons/up"));
    this->_buttonDown = new QPushButton(this);
    this->_buttonDown->setIcon(QIcon(":/icons/down"));
    this->_buttonAdd = new QPushButton(" Add", this);
    this->_buttonAdd->setIcon(QIcon(":/icons/add"));
    this->_buttonAdd->setMinimumWidth(80);
    this->_buttonRemove = new QPushButton(" Remove", this);
    this->_buttonRemove->setIcon(QIcon(":/icons/remove"));
    this->_buttonRemove->setMinimumWidth(80);

    this->_layoutLeft->addWidget(this->_buttonSort);
    this->_layoutLeft->addWidget(this->_buttonModify);
    this->_layoutLeft->addWidget(this->_buttonUp);
    this->_layoutLeft->addWidget(this->_buttonDown);
    this->_layoutLeft->addStretch();
    this->_layoutRight->addStretch();
    this->_layoutRight->addWidget(this->_buttonAdd);
    this->_layoutRight->addWidget(this->_buttonRemove);

    QWidget *leftWidget = new QWidget;
    leftWidget->setLayout(this->_layoutLeft);
    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(this->_layoutRight);
    this->_layoutButtons->addWidget(leftWidget);
    this->_layoutButtons->addWidget(rightWidget);

    this->_layout->addWidget(this->_areaList);
    this->_layout->addLayout(this->_layoutButtons);
    this->_layout->addStretch();
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

}
