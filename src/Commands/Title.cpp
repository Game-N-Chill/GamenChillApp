
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Title::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Title::getCommand() const
{
    return COMMAND_TITLE;
}

} // namespace MKTG::Command
