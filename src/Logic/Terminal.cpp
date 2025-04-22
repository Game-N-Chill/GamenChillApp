
#include "MKTG.hpp"

static void printHeader(std::string &line)
{
    line.clear();
    std::cout << "$> ";
}

int doLogic()
{
    MKTG::Generator gen;
    MKTG::Command::Handler cmdHandler;
    std::string line;
    bool loop = true;

    std::cout << "====================[MARIO KART TOP GENERATOR]====================" << std::endl;
    std::cout << "try \'help\' command to list all available commands" << std::endl << std::endl;

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
        } catch (const std::runtime_error &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
        } catch (const std::out_of_range &e) {
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
