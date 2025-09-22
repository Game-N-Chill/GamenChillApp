
#include "UI/Tools/Randomizer.hpp"
#include <QFileDialog>

namespace GNCApp::UI::Tools
{

Randomizer::Randomizer(const std::list<std::string> &list, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    _comboBox = new QComboBox(this);
    for (auto &it : list) {
        _comboBox->addItem(QString::fromStdString(it));
    }

    _toolBtn = new QToolButton(this);
    _toolBtn->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

    layout->addWidget(_comboBox);
    layout->addWidget(_toolBtn);

    connect(_toolBtn, &QToolButton::clicked, this, &Randomizer::onClicked);
}

QComboBox *Randomizer::getComboBox()
{
    return _comboBox;
}

void Randomizer::randomize()
{
    Utils::Randomizer randomizer;
    _comboBox->setCurrentIndex(randomizer.GetRandom(_comboBox->count()));
}

void Randomizer::onClicked()
{
    randomize();
}

} // namespace GNCApp::UI
