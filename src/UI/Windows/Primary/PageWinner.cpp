
#include <QOverload>

#include "UI/Windows/Primary.hpp"
#include "UI/Windows/PlayerSettings.hpp"
#include "Data/Data.hpp"

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
    auto dataWinner = Data::Winner::getInstance();

    _box = new Tools::HGroupBox("Information", this);

    _layoutLeft = new QFormLayout;
    _layoutRight = new QFormLayout;

    _title = new QLineEdit(this);
    _title->setText(QString::fromStdString(dataWinner->getTitle()));
    connect(_title, &QLineEdit::editingFinished, this, &BoxInfo::onTitleEdited);
    _subtitle = new QLineEdit(this);
    _subtitle->setText(QString::fromStdString(dataWinner->getSubtitle()));
    connect(_subtitle, &QLineEdit::editingFinished, this, &BoxInfo::onSubtitleEdited);

    _date = new QDateEdit(this);
    _date->setDisplayFormat("dd/MM/yyyy");
    _date->setCalendarPopup(true);
    _date->setDate(QDate::currentDate());
    connect(_date, &QDateEdit::dateChanged, this, &BoxInfo::onDateEdited);

    _playerCount = new QSpinBox(this);
    _playerCount->setRange(1, 48);
    _playerCount->setValue(static_cast<int>(dataWinner->getPlayerCount()));
    connect(_playerCount, &QSpinBox::valueChanged, this, &BoxInfo::onPlayerCountEdited);

    _background = new Tools::Randomizer(Data::DictBackground::getInstance()->list(), this);
    _background->getComboBox()->setCurrentText(QString::fromStdString(dataWinner->getBackground().get()));
    connect(this->_background->getComboBox(), &QComboBox::currentIndexChanged, this, &BoxInfo::onBackgroundChanged);

    _output = new Tools::DirBrowser(this);
    _output->getLineEdit()->setText(QString::fromStdString(dataWinner->getOutputDir()));
    connect(_output->getLineEdit(), &QLineEdit::editingFinished, this, &BoxInfo::onOutputDirEdited);

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
    auto dataWinner = Data::Winner::getInstance();

    _box = new Tools::VGroupBox("Players Rank", this);

    _team = new QComboBox(this);
    _team->addItem("Solo");
    _team->addItem("Duo");
    connect(_team, &QComboBox::currentIndexChanged, this, &BoxRank::onTeamChanged);
    _box->addWidget(_team);

    _layoutBox = new Tools::HGroupBox("", this);
    _layoutLeft = new QVBoxLayout;
    _layoutRight = new QVBoxLayout;
    QLayout *currLayout = _layoutLeft;
    for (int i = 0; i <  PLAYER_GRAPH_COUNT; i++) {
        if (i < 4) {
            currLayout = _layoutLeft;
        } else {
            currLayout = _layoutRight;
        }

        QString pos = QString::number(i + 1);

        _playerBox[i] = new Tools::HGroupBox("", this);
        for (int j = 0; j < _playerLabel[i].size(); j++) {
            _playerLabel[i][j] = new QLabel("");
            _playerBox[i]->addWidget(_playerLabel[i][j]);
        }
        _playerButton[i] = new QToolButton(this);
        _playerButton[i]->setText("...");
        connect(_playerButton[i], &QToolButton::clicked, this, [this, i](bool checked) {
            onPlayerClicked(i, checked);
        });
        _playerBox[i]->addWidget(_playerButton[i]);

        currLayout->addWidget(_playerBox[i]);

        setTeamInfo(i, dataWinner->getTeamSolo(i));
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


void BoxInfo::onTitleEdited(const QString &str)
{
    Data::Winner::getInstance()->setTitle(str.toStdString());
}

void BoxInfo::onSubtitleEdited(const QString &str)
{
    Data::Winner::getInstance()->setSubtitle(str.toStdString());
}

void BoxInfo::onDateEdited(const QDate &date)
{
    Data::Winner::getInstance()->setDate(date.toString().toStdString());
}

void BoxInfo::onPlayerCountEdited(int value)
{
    Data::Winner::getInstance()->setPlayerCount(value);
}

void BoxInfo::onBackgroundChanged(int index)
{
    Data::Winner::getInstance()->setBackground(index);
}

void BoxInfo::onOutputDirEdited(const QString &str)
{
    Data::Winner::getInstance()->setOutputDir(str.toStdString());
}


template<size_t N>
void BoxRank::setTeamInfo(int index, Generator::Data::Team<N> team)
{
    if (N == 1) {
        _playerBox[index]->setTitle("N°" + QString::number(index + 1));
    } else {
        _playerBox[index]->setTitle("N°" + QString::number(index + 1) + " - " + QString::fromStdString(team.name));
    }

    for (size_t i = 0; i < _playerLabel[index].size(); i++) {
        if (i < N) {
            _playerLabel[index][i]->setText(QString::fromStdString(team.players[i].getName()) + " (" + QString::fromStdString(team.players[i].getSkin()) + ")");
        } else {
            _playerLabel[index][i]->setText("");
        }
    }
}

void BoxRank::onTeamChanged(int index)
{
    auto dataWinner = Data::Winner::getInstance();

    for (int i = 0; i <  PLAYER_GRAPH_COUNT; i++) {
        if (index == 0) { // Solo
            setTeamInfo(i, dataWinner->getTeamSolo(i));
        } else { // Duo
            setTeamInfo(i, dataWinner->getTeamDuo(i));
        }
    }
}

void BoxRank::onPlayerClicked(int index, bool checked)
{
    if (this->_team->currentIndex() == 0) { // Solo
        openPlayerSoloWindow(index);
    } else { // Duo
        openPlayerDuoWindow(index);
    }
}

void BoxRank::openPlayerSoloWindow(int index)
{
    auto dataWinner = Data::Winner::getInstance();

    Windows::PlayerSolo window(index, "Player Settings", this);
    window();

    if (window.hasValidate()) {
        dataWinner->getTeamSolo(index) = window.getData();
        setTeamInfo(index, window.getData());
    }
}

void BoxRank::openPlayerDuoWindow(int index)
{
    auto dataWinner = Data::Winner::getInstance();

    Windows::PlayerDuo window(index, "Player Settings", this);
    window();

    if (window.hasValidate()) {
        dataWinner->getTeamDuo(index) = window.getData();
        setTeamInfo(index, window.getData());
    }
}


}
