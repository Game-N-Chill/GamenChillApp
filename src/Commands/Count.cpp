
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Count::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Count::getCommand() const
{
    return COMMAND_COUNT;
}

} // namespace MKTG::Command
