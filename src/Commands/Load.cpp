
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Load::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Load::getCommand() const
{
    return COMMAND_LOAD;
}

} // namespace MKTG::Command
