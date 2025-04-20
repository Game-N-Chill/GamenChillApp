
#include "MKTG.hpp"

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

int doLogic()
{
    MKTG::Generator gen;
    MKTG::Command::Handler cmdHandler;
    std::string line;
    bool loop = true;

    printHeader(line);
    while (loop) {
        std::getline(std::cin, line);
        if (line.empty()) {
            printHeader(line);
            continue;
        }

        MKTG::Command::Result result = MKTG::Command::Result::CONTINUE;
        try {
            auto args = lineParser(line);
            result = cmdHandler[args[0]]->run(gen, args);
        } catch(const std::runtime_error &e) {
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
