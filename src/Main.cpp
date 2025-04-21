
#include "MKTG.hpp"
#include <csignal>

#if defined(_WIN32)
#include <Windows.h>
#endif

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
