
#include "UI/Windows/Primary.hpp"

namespace Generator::UI::Windows
{

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

void BoxRank::updateAllInfos()
{
    Data::Winner *dataWinner = Data::Winner::getInstance();

    this->_team->setCurrentIndex(0);
    for (int i = 0; i < PLAYER_GRAPH_COUNT; i++) {
        setTeamInfo(i, dataWinner->getTeamSolo(i));
    }
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

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

// *****************************************************************************
//  LOGIC
// *****************************************************************************

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
            _playerLabel[index][i]->setText(QString::fromStdString(team.players[i].getName()) + " (" + QString::fromStdString(team.players[i].getCharacter().name) + " - " + QString::fromStdString(team.players[i].getSkin()) + ")");
        } else {
            _playerLabel[index][i]->setText("");
        }
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
