
#include "MKTG.hpp"
#include <csignal>

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
    MKTG::Generator gen("Assets\\Rififi #40 bracket.xlsx");
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

    // cmdHandler[COMMAND_HELP]->run(MKTG::Generator &gen, std::string args);

    // gen.setDataLink("Daisy");
    // std::cout << gen.getDataCharacter() << std::endl;
    // std::cout << gen.getDataTrack() << std::endl;
    // gen.createImage();

    return EXIT_SUCCESS;
}
