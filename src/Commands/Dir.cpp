
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Dir::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Dir::getCommand() const
{
    return COMMAND_DIR;
}

} // namespace MKTG::Command
