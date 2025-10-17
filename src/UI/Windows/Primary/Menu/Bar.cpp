
#include "UI/Windows/Primary.hpp"
#include "UI/Windows/Common/Notification.hpp"
#include "Update/Update.hpp"
#include <filesystem>
#include <QActionGroup>
#include <QStyleFactory>

namespace fs = std::filesystem;
namespace GNCApp::UI::Windows
{

//  MENUS
// *****************************************************************************

void Primary::createMenuTheme()
{
    this->_menuTheme = this->_menuFile->addMenu("Themes");

    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);

    QAction *actionDefault = this->_menuTheme->addAction("Default");
    actionDefault->setCheckable(true);
    group->addAction(actionDefault);
    for (auto &entry : fs::directory_iterator("./themes/")) {
        if (entry.is_regular_file()) {
            QString file = QString::fromStdString(entry.path().string());
            if (file.contains(".qss")) {
                file.remove(0, file.lastIndexOf('/') + 1).remove(file.indexOf('.'), file.size());

                QAction *action = this->_menuTheme->addAction(file);
                action->setCheckable(true);
                group->addAction(action);
            }
        }
    }

    connect(group, &QActionGroup::triggered, this, &Primary::onTheme);
}

void Primary::createMenus()
{
    this->_menuFile = menuBar()->addMenu("&File");

    QAction *actionWinner = this->_menuFile->addAction("Top 8");
    QAction *actionBracket = this->_menuFile->addAction("Bracket");
    this->_menuFile->addSeparator();
    createMenuTheme();
    this->_menuFile->addSeparator();
    QAction *actionVersion = this->_menuFile->addAction("Version");
    QAction *actionUpdate = this->_menuFile->addAction("Check update");
    this->_menuFile->addSeparator();
    QAction *actionQuit = this->_menuFile->addAction("Quit");

    connect(actionWinner, &QAction::triggered, this, &Primary::onTabWinner);
    connect(actionBracket, &QAction::triggered, this, &Primary::onTabBracket);
    connect(actionVersion, &QAction::triggered, this, &Primary::onVersion);
    connect(actionUpdate, &QAction::triggered, this, &Primary::onUpdate);
    connect(actionQuit, &QAction::triggered, this, &Primary::onQuit);
}

//  CALLBACK
// *****************************************************************************

void Primary::onTabWinner()
{
    this->_tabs->setCurrentIndex(0);
}

void Primary::onTabBracket()
{
    this->_tabs->setCurrentIndex(1);
}

void Primary::onTheme(QAction *action)
{
    if (action->text() == "Default") {
        setTheme("");
    } else {
        setTheme("./themes/" + action->text() + ".qss");
    }
}

void Primary::onVersion()
{
    Notification::openInfo("Game'n Chill Version", QString::fromStdString(std::string("Game'n Chill Application\nVersion ") + GNCAPP_VERSION), this, ":/icons/app");
}

void Primary::onUpdate()
{
    try {
        GNCApp::Update::Manager updateManager(UPDATE_API_URL);
        if (updateManager.needsUpdate()) {
            bool doUpdate = Notification::openYesNo("Game'n Chill Update", "An update has been found.\nDo you want to install it ?", this);
            if (doUpdate) {
                Utils::createProcess(std::filesystem::current_path().string() + '/' + GNCAPP_NAME + "_Updater.exe");
            }
        } else {
            Notification::openInfo("Game'n Chill Update", "No update found\nYour application is up to date", this);
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "ERROR: filesystem: " << e.what() << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}

void Primary::onQuit()
{
    bool needsQuitting = Notification::openYesNo("Game'n Chill Quit", "Do you want to quit ?", this);
    if (needsQuitting) {
        qApp->quit();
    }
}

}
