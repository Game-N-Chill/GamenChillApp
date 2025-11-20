
#include "GUI.hpp"
#include <QDebug>
#include <QStyleFactory>

#if defined(_WIN32)
#include <Windows.h>
#endif

int main(int ac, char **av)
{
    QApplication app(ac, av);
    GNCApp::Data::loadData();
    GNCApp::GUI::Windows::Primary windowPrimary;
    windowPrimary.lockSize();
    windowPrimary.show();
    int ret = app.exec();
    GNCApp::Data::unloadData();
    return ret;
}

#if defined(_WIN32)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    return main(__argc, __argv);
}

#endif
