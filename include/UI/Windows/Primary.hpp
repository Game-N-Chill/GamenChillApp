
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

namespace Generator::UI::Windows
{

class BoxAutoLoad : public QWidget
{
    Q_OBJECT

    public:
        BoxAutoLoad(QWidget *parent);

        void onLoadClicked();

    private:
        QVBoxLayout *_layout;
        Tools::FGroupBox *_box;
        Tools::FileBrowser *_browserFile;
        QPushButton *_btnLoad;

};

class BoxInfo : public QWidget
{
    Q_OBJECT

    public:
        BoxInfo(QWidget *parent);

    private:
        QVBoxLayout *_layout;
        Tools::HGroupBox *_box;
        QFormLayout *_layoutLeft;
        QFormLayout *_layoutRight;
        QLineEdit *_title;
        QLineEdit *_subtitle;
        QDateEdit *_date;
        QSpinBox *_playerCount;
        QComboBox *_background;
        Tools::DirBrowser *_output;
};

class BoxRank : public QWidget
{
    Q_OBJECT

    public:
        BoxRank(QWidget *parent);

        void onPlayerClicked();

    private:
        QVBoxLayout *_layout;
        Tools::VGroupBox *_box;
        QComboBox *_team;
        Tools::HGroupBox *_layoutBox;
        QVBoxLayout *_layoutLeft;
        QVBoxLayout *_layoutRight;
        std::array<Tools::HGroupBox *, 8> _playerBox;
        std::array<std::array<QLabel *, 2>, 8> _playerLabel;
        std::array<QToolButton *, 8> _playerButton;
};

class PageWinner : public QWidget
{
    Q_OBJECT

    public:
        PageWinner(QWidget *parent);

        void onGenerateClicked();

    private:
        QVBoxLayout *_layout;

        BoxAutoLoad *_autoLoad;
        BoxInfo *_info;
        BoxRank *_rank;

        QPushButton *_btnWinner;
};

class PageBracket : public QWidget
{
    Q_OBJECT

    public:
        PageBracket(QWidget *parent);

    private:
        QVBoxLayout *_layout;
};

class Primary : public QMainWindow
{
    Q_OBJECT

    public:
        Primary(QWidget *parent = nullptr);
        ~Primary();

        void lockSize();

    private slots:
        void onQuit();

    private:
        void createMenus();

        QWidget *_central;
        QVBoxLayout *_layout;
        QTabWidget *_tabs;

        PageWinner *_pageWinner;
        PageBracket *_pageBracket;
};

} // namespace MKTG
