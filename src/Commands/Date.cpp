
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Date::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Date::getCommand() const
{
    return COMMAND_DATE;
}

} // namespace MKTG::Command
