
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

#include "UI/Tools/GroupBox.hpp"
#include "UI/Tools/Browser.hpp"
#include "UI/Tools/Window.hpp"

namespace Generator::UI::Windows
{

class PlayerInfo : public QWidget
{
    Q_OBJECT

    public:
        PlayerInfo(const QString &title, QWidget *parent = nullptr);

    private:
        QVBoxLayout *_layout;
        Tools::FGroupBox *_box;
        QLineEdit *_player;
        QComboBox *_character;
        QComboBox *_skins;
};

class PlayerSolo : public Tools::Window
{
    Q_OBJECT

    public:
        PlayerSolo(const QString &title, QWidget *parent = nullptr);

    private:
        PlayerInfo *_info;
};

class PlayerDuo : public Tools::Window
{
    Q_OBJECT

    public:
        PlayerDuo(const QString &title, QWidget *parent = nullptr);

    private:
        QLabel *_teamLabel;
        QLineEdit *_team;
        PlayerInfo *_infoFirst;
        PlayerInfo *_infoSecond;
};

}
