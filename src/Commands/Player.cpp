
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Player::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 4) {
        throw std::runtime_error("not enough arguments");
    }

    std::cout << "not implemented yet :(" << std::endl;
    return Result::CONTINUE;
}

std::string Player::getCommand() const
{
    return COMMAND_PLAYER;
}

} // namespace MKTG::Command
