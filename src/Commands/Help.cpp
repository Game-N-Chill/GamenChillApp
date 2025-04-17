
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Help::run(MKTG::Generator &gen, std::string args)
{
    std::cout << args << std::endl;
    return Result::CONTINUE;
}

std::string Help::getCommand() const
{
    return COMMAND_HELP;
}

} // namespace MKTG::Command
