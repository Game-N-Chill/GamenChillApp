
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
#include <QButtonGroup>
#include <QRadioButton>
#include <QScrollArea>
#include <QListWidget>
#include <QStringList>

#include "UI/Tools/GroupBox.hpp"
#include "UI/Tools/Browser.hpp"
#include "UI/Tools/Randomizer.hpp"

#include "UI/Windows/Common/Shared.hpp"
#include "UI/Windows/Secondary/PlayerSettings.hpp"
#include "UI/Windows/Secondary/PlayerBracket.hpp"
#include "Data/Data.hpp"
#include "Utils.hpp"

namespace GNCApp::UI::Windows
{
    #define DATE_FORMAT             "dd/MM/yyyy"

    #define PLAYER_LIMIT            48

//  WINNER DATA STRUCTURE
// *****************************************************************************

class BoxAutoLoad : public QWidget
{
    Q_OBJECT

    public:
        BoxAutoLoad(QWidget *parent);

        void onPathEdited(const QString &str);
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

        void updateAllInfos();

        void onTitleEdited(const QString &str);
        void onSubtitleEdited(const QString &str);
        void onDateEdited(const QDate &date);
        void onPlayerCountEdited(int value);
        void onGameChanged(int id, bool checked);
        void onBackgroundChanged(int index);
        void onOutputDirEdited(const QString &str);

    private:
        QVBoxLayout *_layout;
        Tools::HGroupBox *_box;
        QFormLayout *_layoutLeft;
        QFormLayout *_layoutRight;
        QLineEdit *_title;
        QLineEdit *_subtitle;
        QDateEdit *_date;
        QSpinBox *_playerCount;
        QButtonGroup *_games;
        Tools::Randomizer *_background;
        Tools::DirBrowser *_output;
};

class BoxRank : public QWidget
{
    Q_OBJECT

    public:
        BoxRank(QWidget *parent);

        void updateAllInfos();

        void onTeamChanged(int index);
        void onPlayerClicked(int index, bool checked);

        template<size_t N>
        void setTeamInfo(int index, GNCApp::Data::Winner::Team<N> team);
        void openPlayerSoloWindow(int index);
        void openPlayerDuoWindow(int index);

        int getTeamSelected();

    private:
        QVBoxLayout *_layout;
        Tools::VGroupBox *_box;
        QComboBox *_team;
        Tools::HGroupBox *_layoutBox;
        QVBoxLayout *_layoutLeft;
        QVBoxLayout *_layoutRight;
        std::array<Tools::HGroupBox *, PLAYER_GRAPH_COUNT> _playerBox;
        std::array<std::array<QLabel *, 2>, PLAYER_GRAPH_COUNT> _playerLabel;
        std::array<QToolButton *, PLAYER_GRAPH_COUNT> _playerButton;
};

class PageWinner : public QWidget
{
    Q_OBJECT

    public:
        PageWinner(QWidget *parent);

        void onGenerateClicked();
        void callbackOpenDir();

        void updateAllInfos();

    private:
        QVBoxLayout *_layout;

        BoxAutoLoad *_autoLoad;
        BoxInfo *_info;
        BoxRank *_rank;

        QPushButton *_btnWinner;
};

//  BRACKET DATA STRUCTURE
// *****************************************************************************

class PageBracket : public QWidget
{
    Q_OBJECT

    public:
        PageBracket(QWidget *parent);

    private:
        void onListItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
        void onListItemSelected(QListWidgetItem *item);
        QString getListItemName(size_t index);

        void onLoadClicked();
        void onLoadEdited(const QString &str);
        void onSortClicked();
        void onModifyClicked();
        void onUpClicked();
        void onDownClicked();
        void onAddClicked();
        void onRemoveClicked();
        void onOutputEdited(const QString &str);
        void onNumberEdited(int value);
        void onEditionChanged(int id, bool checked);
        void onEditionCustomEdited(const QString &str);
        void onGenerateClicked();

        void onMove(int indexSrc, int indexDest);
        void addPlayer(std::string player);

        void createBoxAutoLoad();
        void createBoxSeeding();
        void createBoxInfo();

        void callbackOpenFile();

        QVBoxLayout *_layout;

        Tools::FGroupBox *_boxAutoLoad;
        Tools::FileBrowser *_browserFile;
        QPushButton *_btnLoad;

        Tools::VGroupBox *_boxSeeding;
        QListWidget *_areaList;
        size_t _areaIndex;
        QHBoxLayout *_layoutButtons;
        QHBoxLayout *_layoutLeft;
        QHBoxLayout *_layoutRight;
        QPushButton *_buttonSort;
        QPushButton *_buttonModify;
        QPushButton *_buttonUp;
        QPushButton *_buttonDown;
        QPushButton *_buttonAdd;
        QPushButton *_buttonRemove;

        Tools::FGroupBox *_boxInfo;
        Tools::DirBrowser *_output;
        QSpinBox *_number;
        QVBoxLayout *_editionLayout;
        QStringList _editionList;
        QButtonGroup *_edition;
        QLineEdit *_editionCustom;

        QPushButton *_buttonGenerator;
};

//  CORE DATA STRUCTURE
// *****************************************************************************

class Primary : public QMainWindow
{
    Q_OBJECT

    public:
        Primary(QWidget *parent = nullptr);
        ~Primary();

        void lockSize();
        void checkUpdate();

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
