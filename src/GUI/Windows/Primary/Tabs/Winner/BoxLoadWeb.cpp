
#include "GUI/Windows/Primary.hpp"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

namespace GNCApp::GUI::Windows
{

BoxLoadWeb::BoxLoadWeb(QWidget *parent) :
    QWidget(parent)
{
    _box = new Tools::HGroupBox("Web Loader", this);

    QFormLayout *formLayout = new QFormLayout();
    _apiKey = new QLineEdit(this);
    formLayout->addRow("API Key: ", _apiKey);
    _tournamentID = new QLineEdit(this);
    formLayout->addRow("Tournament ID: ", _tournamentID);
    _box->addLayout(formLayout);

    _btnLoad = createPushButton(this, " Load", "When clicked will load all infos from path excel file", ":/icons/load", 80, std::bind(&BoxLoadWeb::onLoadClicked, this));
    _box->addWidget(_btnLoad);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    _layout->addStretch();
    setLayout(_layout);
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

void BoxLoadWeb::onLoadClicked()
{
    try {
        Logic::loadWebFile(this->_apiKey->text().toStdString(), this->_tournamentID->text().toStdString());

        auto tabDuo = dynamic_cast<TabDuo *>(this->parentWidget());
        if (tabDuo != nullptr) {
            tabDuo->updateInfo();
        }
    } catch (std::runtime_error &e) {
        Error() << "ERROR: " << e.what() << GGL::end;
        return;
    } catch (json::exception &e) {
        Error() << "ERROR: " << e.what() << GGL::end;
        return;
    }
}

}
