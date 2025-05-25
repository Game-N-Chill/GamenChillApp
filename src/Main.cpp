
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
