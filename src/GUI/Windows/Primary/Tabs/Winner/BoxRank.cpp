
#include "GUI/Windows/Primary.hpp"

namespace GNCApp::GUI::Windows
{

BoxRank::BoxRank(int teamSize, QWidget *parent) :
    QWidget(parent)
{
    _teamSize = teamSize;

    auto dataWinner = Data::Winner::getInstance();

    _box = new Tools::HGroupBox("Players Rank", this);

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
        _playerLabel[i] = new QLabel("");
        _playerBox[i]->addWidget(_playerLabel[i]);
        // for (int j = 0; j < _playerLabel[i].size(); j++) {
        //     _playerLabel[i][j] = new QLabel("");
        //     _playerBox[i]->addWidget(_playerLabel[i][j]);
        // }
        _playerButton[i] = new QToolButton(this);
        _playerButton[i]->setText("...");
        connect(_playerButton[i], &QToolButton::clicked, this, [this, i](bool checked) {
            onPlayerClicked(i, checked);
        });
        _playerBox[i]->addWidget(_playerButton[i]);

        currLayout->addWidget(_playerBox[i]);
    }
    _box->addLayout(_layoutLeft);
    _box->addLayout(_layoutRight);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    _layout->addStretch();
    setLayout(_layout);

    updateInfo();
}

void BoxRank::updateInfo()
{
    Data::Winner *dataWinner = Data::Winner::getInstance();

    for (int i = 0; i < PLAYER_GRAPH_COUNT; i++) {
        if (_teamSize == 1) {
            setTeamInfo(i, dataWinner->getTeamSolo(i));
        } else {
            setTeamInfo(i, dataWinner->getTeamDuo(i));
        }
    }
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

void BoxRank::onPlayerClicked(int index, bool checked)
{
    if (this->_teamSize == 1) { // Solo
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

    QString str = "";
    for (size_t i = 0; i < N; i++) {
        str += QString::fromStdString(team[i].getName()) + " (" + QString::fromStdString(team[i].getCharacter().name) + " - " + QString::fromStdString(team[i].getSkin()) + ")";

        if (i < N - 1) {
            str += '\n';
        }

        // if (i < N) {
        //     _playerLabel[index][i]->setText(QString::fromStdString(team[i].getName()) + " (" + QString::fromStdString(team[i].getCharacter().name) + " - " + QString::fromStdString(team[i].getSkin()) + ")");
        // } else {
        //     _playerLabel[index][i]->setText("");
        // }
    }
    _playerLabel[index]->setText(str);
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

}
