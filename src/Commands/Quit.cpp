
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Quit::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    return Result::SUCCESS;
}

std::string Quit::getCommand() const
{
    return COMMAND_QUIT;
}

} // namespace MKTG::Command
