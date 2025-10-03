
#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI::Windows
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
void BoxRank::setTeamInfo(int index, GNCApp::Data::Winner::Team<N> team)
{
    if (N == 1) {
        _playerBox[index]->setTitle("N°" + QString::number(index + 1));
    } else {
        _playerBox[index]->setTitle("N°" + QString::number(index + 1) + " - " + QString::fromStdString(*team));
    }

    for (size_t i = 0; i < _playerLabel[index].size(); i++) {
        if (i < N) {
            _playerLabel[index][i]->setText(QString::fromStdString(team[i].getName()) + " (" + QString::fromStdString(team[i].getCharacter().name) + " - " + QString::fromStdString(team[i].getSkin()) + ")");
        } else {
            _playerLabel[index][i]->setText("");
        }
    }
}

void BoxRank::openPlayerSoloWindow(int index)
{
    auto dataWinner = Data::Winner::getInstance();

    Tools::Window *window = new PlayerSolo(index, "Player Settings", this);
    addWindowButtonValidate(window);
    addWindowButtonCancel(window);

    (*window)();
    if (window->hasValidate()) {
        dataWinner->getTeamSolo(index) = dynamic_cast<PlayerSolo *>(window)->getData();
        setTeamInfo(index, dataWinner->getTeamSolo(index));
    }

    delete window;
}

void BoxRank::openPlayerDuoWindow(int index)
{
    auto dataWinner = Data::Winner::getInstance();

    Tools::Window *window =  new PlayerDuo(index, "Player Settings", this);
    addWindowButtonValidate(window);
    addWindowButtonCancel(window);

    (*window)();
    if (window->hasValidate()) {
        dataWinner->getTeamDuo(index) = dynamic_cast<PlayerDuo *>(window)->getData();
        setTeamInfo(index, dataWinner->getTeamDuo(index));
    }

    delete window;
}

int BoxRank::getTeamSelected()
{
    return this->_team->currentIndex();
}

}
