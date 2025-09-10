
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/PlayerSettings.hpp"

namespace Generator::UI::Windows
{

PageWinner::PageWinner(QWidget *parent) :
    QWidget(parent)
{
    _layout = new QVBoxLayout(this);

    _autoLoad = new BoxAutoLoad(this);
    _layout->addWidget(_autoLoad);

    _info = new BoxInfo(this);
    _layout->addWidget(_info);

    _rank = new BoxRank(this);
    _layout->addWidget(_rank);

    _btnWinner = new QPushButton("Generate", this);
    _btnWinner->setFixedWidth(80);
    connect(_btnWinner, &QPushButton::clicked, this, &PageWinner::onGenerateClicked);
    _layout->addWidget(_btnWinner);
}

BoxAutoLoad::BoxAutoLoad(QWidget *parent) :
    QWidget(parent)
{
    _box = new Tools::FGroupBox("Auto Loader", this);

    _btnLoad = new QPushButton("Load", this);
    _btnLoad->setFixedWidth(60);
    connect(_btnLoad, &QToolButton::clicked, this, &BoxAutoLoad::onLoadClicked);
    _browserFile = new Tools::FileBrowser(this, _btnLoad);

    _box->addRow("Excel Path : ", _browserFile);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}

BoxInfo::BoxInfo(QWidget *parent) :
    QWidget(parent)
{
    _box = new Tools::HGroupBox("Information", this);

    _layoutLeft = new QFormLayout;
    _layoutRight = new QFormLayout;

    _title = new QLineEdit(this);
    _subtitle = new QLineEdit(this);

    _date = new QDateEdit(this);
    _date->setDisplayFormat("dd/MM/yyyy");
    _date->setCalendarPopup(true);
    _date->setDate(QDate::currentDate());

    _playerCount = new QSpinBox(this);
    _playerCount->setRange(1, 48);
    _playerCount->setValue(16);

    _background = new QComboBox(this);
    _background->addItem("Circuit Mario");
    _background->addItem("Chateau de Peach");

    _output = new Tools::DirBrowser(this);

    _layoutLeft->addRow("Title : ", _title);
    _layoutLeft->addRow("SubTitle : ", _subtitle);
    _layoutLeft->addRow("Date : ", _date);
    _layoutLeft->addRow("Player Count : ", _playerCount);
    _layoutRight->addRow("Background : ", _background);
    _layoutRight->addRow("Output : ", _output);
    _box->addLayout(_layoutLeft);
    _box->addLayout(_layoutRight);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}

BoxRank::BoxRank(QWidget *parent) :
    QWidget(parent)
{
    _box = new Tools::VGroupBox("Players Rank", this);

    _team = new QComboBox(this);
    _team->addItem("Solo");
    _team->addItem("Duo");
    _box->addWidget(_team);

    _layoutBox = new Tools::HGroupBox("", this);
    _layoutLeft = new QVBoxLayout;
    _layoutRight = new QVBoxLayout;
    QLayout *currLayout = _layoutLeft;
    for (size_t i = 0; i <  _playerLabel.size(); i++) {
        if (i < 4) {
            currLayout = _layoutLeft;
        } else {
            currLayout = _layoutRight;
        }

        QString pos = QString::number(i + 1);

        _playerBox[i] = new Tools::HGroupBox("N°" + pos + " - Team Name", this);
        for (size_t j = 0; j < _playerLabel[i].size(); j++) {
            _playerLabel[i][j] = new QLabel("Player " + pos + " (Mario)");
            _playerBox[i]->addWidget(_playerLabel[i][j]);
        }
        _playerButton[i] = new QToolButton(this);
        _playerButton[i]->setText("...");
        connect(_playerButton[i], &QToolButton::clicked, this, &BoxRank::onPlayerClicked);
        _playerBox[i]->addWidget(_playerButton[i]);

        currLayout->addWidget(_playerBox[i]);
    }
    _layoutBox->addLayout(_layoutLeft);
    _layoutBox->addLayout(_layoutRight);
    _box->addWidget(_layoutBox);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}


void PageWinner::onGenerateClicked()
{
    std::cout << "generate clicked" << std::endl;
}

void BoxAutoLoad::onLoadClicked()
{
    std::cout << "load clicked" << std::endl;
}

void BoxRank::onPlayerClicked()
{
    Tools::Window *window = nullptr;

    if (this->_team->currentIndex() == 0) { // Solo
        window = new PlayerSolo("Player Settings", this);
    } else { // Duo
        window = new PlayerDuo("Player Settings", this);
    }

    (*window)();

    if (window->hasValidate()) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "Cancel" << std::endl;
    }

    delete window;
}

}
