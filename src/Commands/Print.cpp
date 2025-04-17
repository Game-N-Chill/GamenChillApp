
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Print::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Print::getCommand() const
{
    return COMMAND_PRINT;
}

} // namespace MKTG::Command
