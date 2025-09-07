
#include "MKTG.hpp"
#include <csignal>

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QWidget>

static void signalCatcher(int exitcode)
{
    exit(EXIT_SUCCESS);
}

static void preLoad()
{
    // Shows color on windows terminal
    #if defined(_WIN32)
        SetConsoleOutputCP(CP_UTF8);
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif

    if (!TTF_Init())
        throw std::runtime_error(SDL_GetError());

    std::signal(SIGINT, signalCatcher);
    std::signal(SIGTERM, signalCatcher);

    MKTG::Updater updater(MKTG_API_URL);
    if (updater.needsUpdate()) {
        int result = MessageBoxA(nullptr, "An update is available, do you want to install it ?", "Confirmation", MB_YESNO | MB_ICONQUESTION);
        if (result == IDYES) {
            Utils::createProcess(std::filesystem::current_path().string() + "\\MarioKartTopGenerator_Updater.exe");
        }
    }
}

int main(int ac, char **av)
{
    try {
        preLoad();
    } catch (std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    doLogic();
    return EXIT_SUCCESS;
}

/*

int main(int ac, char **av)
{
    QApplication app(ac, av);

    // Main window
    QMainWindow window;
    window.setWindowTitle("My Qt Widgets App");

    // Central widget + layout
    QWidget *central = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    // Button
    QPushButton *button = new QPushButton("Select Folder");
    layout->addWidget(button);

    // Checkbox
    QCheckBox *check = new QCheckBox("Enable Option");
    layout->addWidget(check);

    // Connect button action
    QObject::connect(button, &QPushButton::clicked, [&]() {
        QString folder = QFileDialog::getExistingDirectory(&window, "Select a folder");
        if (!folder.isEmpty()) {
            QMessageBox::information(&window, "Folder Selected", folder);
        }
    });

    // Set layout and show
    central->setLayout(layout);
    window.setCentralWidget(central);
    window.resize(400, 200);
    window.show();

    return app.exec();
}

*/
