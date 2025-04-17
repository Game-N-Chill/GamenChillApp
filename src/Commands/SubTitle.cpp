
#include "MKTG.hpp"

namespace MKTG::Command
{

Result SubTitle::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string SubTitle::getCommand() const
{
    return COMMAND_SUBTITLE;
}

} // namespace MKTG::Command
