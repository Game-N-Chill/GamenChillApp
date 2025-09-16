
#include "UI/Windows/Primary.hpp"

namespace GNCApp::UI::Windows
{

BoxInfo::BoxInfo(QWidget *parent) :
    QWidget(parent)
{
    auto dataWinner = Data::Winner::getInstance();

    _box = new Tools::HGroupBox("Information", this);

    _layoutLeft = new QFormLayout;
    _layoutRight = new QFormLayout;

    _title = new QLineEdit(this);
    _title->setText(QString::fromStdString(dataWinner->getTitle()));
    connect(_title, &QLineEdit::textEdited, this, &BoxInfo::onTitleEdited);
    _subtitle = new QLineEdit(this);
    _subtitle->setText(QString::fromStdString(dataWinner->getSubtitle()));
    connect(_subtitle, &QLineEdit::textEdited, this, &BoxInfo::onSubtitleEdited);

    _date = new QDateEdit(this);
    _date->setDisplayFormat(DATE_FORMAT);
    _date->setCalendarPopup(true);
    _date->setDate(QDate::currentDate());
    connect(_date, &QDateEdit::dateChanged, this, &BoxInfo::onDateEdited);

    _playerCount = new QSpinBox(this);
    _playerCount->setRange(1, 48);
    _playerCount->setValue(static_cast<int>(dataWinner->getPlayerCount()));
    connect(_playerCount, &QSpinBox::valueChanged, this, &BoxInfo::onPlayerCountEdited);

    QVBoxLayout *gamesLayout = new QVBoxLayout;
    QStringList gamesList = {"Mario Kart 8 Deluxe", "Mario Kart World"};
    _games = new QButtonGroup(this);
    _games->setExclusive(true);
    for (int i = 0; i < gamesList.size(); i++) {
        QRadioButton *radio = new QRadioButton(gamesList[i]);
        gamesLayout->addWidget(radio);
        _games->addButton(radio, i);
    }

    _background = new Tools::Randomizer(Data::DictBackground::getInstance()->list(), this);
    _background->getComboBox()->setCurrentText(QString::fromStdString(dataWinner->getBackground().get()));
    connect(this->_background->getComboBox(), &QComboBox::currentIndexChanged, this, &BoxInfo::onBackgroundChanged);

    _output = new Tools::DirBrowser(this);
    _output->getLineEdit()->setText(QString::fromStdString(dataWinner->getOutputDir()));
    connect(_output->getLineEdit(), &QLineEdit::textEdited, this, &BoxInfo::onOutputDirEdited);

    _layoutLeft->addRow("Title : ", _title);
    _layoutLeft->addRow("SubTitle : ", _subtitle);
    _layoutLeft->addRow("Date : ", _date);
    _layoutLeft->addRow("Player Count : ", _playerCount);
    _layoutRight->addRow("Game Selected : ", gamesLayout);
    _layoutRight->addRow("Background : ", _background);
    _layoutRight->addRow("Output : ", _output);
    _box->addLayout(_layoutLeft);
    _box->addLayout(_layoutRight);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(_box);
    setLayout(_layout);
}

void BoxInfo::updateAllInfos()
{
    Data::Winner *dataWinner = Data::Winner::getInstance();

    this->_title->setText(QString::fromStdString(dataWinner->getTitle()));
    this->_subtitle->setText(QString::fromStdString(dataWinner->getSubtitle()));
    this->_date->setDate(QDate::fromString(QString::fromStdString(dataWinner->getDate()), DATE_FORMAT));
    this->_playerCount->setValue(static_cast<int>(dataWinner->getPlayerCount()));
    this->_background->randomize();
}

// *****************************************************************************
//  CALLBACKS
// *****************************************************************************

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

}
