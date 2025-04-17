
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Url::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Url::getCommand() const
{
    return COMMAND_URL;
}

} // namespace MKTG::Command
