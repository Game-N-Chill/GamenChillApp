
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Player::run(MKTG::Generator &gen, std::string args)
{
    return Result::CONTINUE;
}

std::string Player::getCommand() const
{
    return COMMAND_PLAYER;
}

} // namespace MKTG::Command
