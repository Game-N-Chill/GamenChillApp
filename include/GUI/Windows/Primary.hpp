
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

#include "GUI/Tools/GroupBox.hpp"
#include "GUI/Tools/Browser.hpp"
#include "GUI/Tools/Randomizer.hpp"

#include "Shared.hpp"
#include "GUI/Windows/Common/Common.hpp"
#include "GUI/Windows/Secondary/PlayerSettings.hpp"
#include "GUI/Windows/Secondary/PlayerBracket.hpp"

namespace GNCApp::GUI::Windows
{
    #define PLAYER_LIMIT            48

//  WINNER DATA STRUCTURE
// *****************************************************************************

class BoxLoadExcel : public QWidget
{
    Q_OBJECT

    public:
        BoxLoadExcel(QWidget *parent);

        void onPathEdited(const QString &str);
        void onLoadClicked();

    private:
        QVBoxLayout *_layout;
        Tools::FGroupBox *_box;
        Tools::FileBrowser *_browserFile;
        QPushButton *_btnLoad;

};

class BoxLoadWeb : public QWidget
{
    Q_OBJECT

    public:
        BoxLoadWeb(QWidget *parent);

        void onPathEdited(const QString &str);
        void onLoadClicked();

    private:
        QVBoxLayout *_layout;
        Tools::HGroupBox *_box;
        QLineEdit *_apiKey;
        QLineEdit *_tournamentID;
        QPushButton *_btnLoad;

};

class BoxInfo : public QWidget
{
    Q_OBJECT

    public:
        BoxInfo(QWidget *parent);

        void updateInfo();

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
        BoxRank(int teamSize, QWidget *parent);

        void updateInfo();

        void onTeamChanged(int index);
        void onPlayerClicked(int index, bool checked);

        template<size_t N>
        void setTeamInfo(int index, GNCApp::Data::Winner::Team<N> team);
        void openPlayerSoloWindow(int index);
        void openPlayerDuoWindow(int index);

    private:
        int _teamSize;

        QVBoxLayout *_layout;
        Tools::HGroupBox *_box;
        QVBoxLayout *_layoutLeft;
        QVBoxLayout *_layoutRight;
        std::array<Tools::HGroupBox *, PLAYER_GRAPH_COUNT> _playerBox;
        std::array<QLabel *, PLAYER_GRAPH_COUNT> _playerLabel;
        std::array<QToolButton *, PLAYER_GRAPH_COUNT> _playerButton;
};

class TabSolo : public QWidget
{
    Q_OBJECT

    public:
        TabSolo(QWidget *parent, BoxInfo *info);

        void updateInfo();

    private:
        BoxInfo *_ptrInfo;
        QVBoxLayout *_layout;

        BoxLoadExcel *_loadExcel;
        BoxRank *_rank;
};

class TabDuo : public QWidget
{
    Q_OBJECT

    public:
        TabDuo(QWidget *parent, BoxInfo *info);

        void updateInfo();

    private:
        BoxInfo *_ptrInfo;
        QVBoxLayout *_layout;

        BoxLoadWeb *_loadWeb;
        BoxRank *_rank;
};

class PageWinner : public QWidget
{
    Q_OBJECT

    public:
        PageWinner(QWidget *parent);

        void onGenerateClicked();
        void callbackOpenDir();

        void updateInfo();

    private:
        QVBoxLayout *_layout;

        BoxInfo *_info;
        QTabWidget *_tabs;
        TabSolo *_tabSolo;
        TabDuo *_tabDuo;

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

    private slots:
        void onTabWinner();
        void onTabBracket();
        void onTheme(QAction *action);
        void onVersion();
        void onUpdate();
        void onQuit();

    private:
        void createMenus();
        void createMenuTheme();

        void loadConfig();
        void setTheme(const char *path);
        void setTheme(std::string path);
        void setTheme(QString path);

        QWidget *_central;
        QVBoxLayout *_layout;
        QTabWidget *_tabs;

        PageWinner *_pageWinner;
        PageBracket *_pageBracket;

        QMenu *_menuFile;
        QMenu *_menuTheme;
};

} // namespace MKTG
