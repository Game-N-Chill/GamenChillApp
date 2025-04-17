
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Random::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Random::getCommand() const
{
    return COMMAND_RANDOM;
}

} // namespace MKTG::Command
