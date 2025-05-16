
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Help::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    std::ifstream file(Utils::getFullPath(PATH_HELP));
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
    return Result::CONTINUE;
}

std::string Help::getCommand() const
{
    return COMMAND_HELP;
}

} // namespace MKTG::Command
