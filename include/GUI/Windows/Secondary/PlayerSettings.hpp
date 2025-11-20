
#pragma once

#include <iostream>
#include <memory>
#include <array>

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QToolButton>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>

#include "Shared.hpp"
#include "GUI/Tools/GroupBox.hpp"
#include "GUI/Tools/Browser.hpp"
#include "GUI/Tools/Window.hpp"
#include "GUI/Tools/Randomizer.hpp"
#include "GUI/Windows/Common/Common.hpp"

namespace GNCApp::GUI::Windows
{

class PlayerInfo : public QWidget
{
    Q_OBJECT

    public:
        PlayerInfo(const Data::Winner::Player &data, const QString &title, QWidget *parent = nullptr);

        Data::Winner::Player getData() const;

        void onNameEdited(const QString &str);
        void onCharacterChanged(int index);
        void onSkinChanged(int index);

    private:
        QVBoxLayout *_layout;
        Tools::FGroupBox *_box;
        QLineEdit *_player;
        QComboBox *_character;
        Tools::Randomizer *_skins;

        Data::Winner::Player _data;
};

class PlayerSolo : public Tools::Window
{
    Q_OBJECT

    public:
        PlayerSolo(const int &index, const QString &title, QWidget *parent = nullptr);

        Data::Winner::Solo getData() const;

    private:
        PlayerInfo *_info;
};

class PlayerDuo : public Tools::Window
{
    Q_OBJECT

    public:
        PlayerDuo(const int &index, const QString &title, QWidget *parent = nullptr);

        Data::Winner::Duo getData() const;

    private:
        QLabel *_teamLabel;
        QLineEdit *_team;
        PlayerInfo *_infoFirst;
        PlayerInfo *_infoSecond;
};

}
