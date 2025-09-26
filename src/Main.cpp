
#include "GNCApp.hpp"
#include <QDebug>
#include <QStyleFactory>

#if defined(_WIN32)
#include <Windows.h>
#endif

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
}

int main(int ac, char **av)
{
    try {
        preLoad();
    } catch (std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    QApplication app(ac, av);

    QFile file("themes/Darkeum.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        app.setStyleSheet(styleSheet);
    }

    GNCApp::Data::loadData();

    GNCApp::UI::Windows::Primary windowPrimary;
    windowPrimary.lockSize();
    windowPrimary.show();
    windowPrimary.checkUpdate();

    return app.exec();
}

#if defined(_WIN32)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return main(__argc, __argv);
}

#endif
