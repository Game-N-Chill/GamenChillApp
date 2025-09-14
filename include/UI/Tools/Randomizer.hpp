
#pragma once

#include <list>

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QToolButton>

#include "Data/Data.hpp"

namespace GNCApp::UI::Tools
{

class Randomizer : public QWidget
{
    Q_OBJECT

    public:
        Randomizer(const std::list<std::string> &list, QWidget *parent = nullptr);

        QComboBox *getComboBox();

        void randomize();

    protected:
        QComboBox *_comboBox;
        QToolButton *_toolBtn;

    private slots:
        void onClicked();
};

} // namespace GNCApp::UI
