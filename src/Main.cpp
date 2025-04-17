
#include "MKTG.hpp"
#include <csignal>

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

static void signalCatcher(int exitcode)
{
    exit(EXIT_SUCCESS);
}

static void printHeader(std::string &line)
{
    line.clear();
    std::cout << "$> ";
}

static std::array<std::string, 2> parseLine(std::string line)
{
    std::array<std::string, 2> array;

    size_t pos = line.find_first_of(' ');
    array[0] = line.substr(0, pos);
    if (pos != std::string::npos) {
        while (pos < line.size() && line[pos] == ' ') {
            pos++;
        }
        array[1] = line.substr(pos);
    }

    return array;
}

int main(int ac, char **av)
{
    preLoad();

    MKTG::Generator gen;
    MKTG::Command::Handler cmdHandler;
    std::string line;
    int exitCode = EXIT_SUCCESS;
    bool loop = true;

    std::signal(SIGINT, signalCatcher);
    std::signal(SIGTERM, signalCatcher);

    printHeader(line);
    while (loop) {
        std::getline(std::cin, line);
        if (line.empty()) {
            printHeader(line);
            continue;
        }

        MKTG::Command::Result result = MKTG::Command::Result::CONTINUE;
        try {
            auto args = parseLine(line);
            result = cmdHandler[args[0]]->run(gen, args[1]);
        } catch(const std::out_of_range &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }

        switch (result) {
            case MKTG::Command::Result::CONTINUE:
                printHeader(line);
                break;
            case MKTG::Command::Result::SUCCESS:
            case MKTG::Command::Result::FAILURE:
                loop = false;
                break;
        }
    }

    return EXIT_SUCCESS;
}
