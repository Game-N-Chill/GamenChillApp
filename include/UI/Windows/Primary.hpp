
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

#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#include <OpenXLSX.hpp>
#pragma warning(pop)

#include "UI/Tools/GroupBox.hpp"
#include "UI/Tools/Browser.hpp"
#include "UI/Tools/Randomizer.hpp"

#include "UI/Windows/Common/Shared.hpp"
#include "UI/Windows/Secondary/PlayerSettings.hpp"
#include "Data/Data.hpp"

namespace GNCApp::UI::Windows
{

    #define EXCEL_CELL_TITLE        "C2"
    #define EXCEL_CELL_SUBTITLE     "D7"
    #define EXCEL_CELL_DATE         "I7"
    #define EXCEL_LINE_FIRST        15
    #define EXCEL_COL_CHARACTER     "H"
    #define EXCEL_COL_PLAYER        "I"

    #define DATE_FORMAT             "dd/MM/yyyy"

    // https://drive.proton.me/urls/B4QRBAC9N4#jLPHFgdDzc1b
    // #define PROTON_API_URL              "https://drive.proton.me/api/drive/urls/B4QRBAC9N4/files/yxbGyegyGjpPqOWlOhjc4DMVgKRpDlkYyRp-2sh3WnZ23hH0ygld66DroA5PoBGYg3qvWBBaWKmCUG5AdLJLPg==?FromBlockIndex=1&PageSize=50"
    #define PROTON_API_URL              "https://1drv.ms/x/c/8e2ad450607c91c5/EYttSBbg-mFLimzAYMBm7f8BGWBCNxbc0jiQRK8PWEmrkw"
    #define PROTON_API_FILE_NAME        "seeding.xlsx"

//  WINNER DATA STRUCTURE
// *****************************************************************************

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
        void setTeamInfo(int index, GNCApp::Data::Team<N> team);
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

        void onListItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
        void onListItemSelected(QListWidgetItem *item);


        void onSortClicked();
        void onModifyClicked();
        void onUpClicked();
        void onDownClicked();
        void onAddClicked();
        void onRemoveClicked();

    private:
        QVBoxLayout *_layout;

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
