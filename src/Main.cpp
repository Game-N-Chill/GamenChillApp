
#include "GNCApp.hpp"
#include <QTimer>

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
    GNCApp::Data::loadData();

    GNCApp::UI::Windows::Primary windowPrimary;
    windowPrimary.lockSize();
    windowPrimary.show();
    windowPrimary.checkUpdate();

    return app.exec();
    return 0;
}
