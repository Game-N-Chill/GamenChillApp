
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Player::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 4) {
        throw std::runtime_error("not enough arguments");
    }

    size_t rank = std::atoi(args[1].c_str());
    std::string character = args[2];
    std::string name = args[3];
    gen.setPlayerInfo(rank, character, name);

    return Result::CONTINUE;
}

std::string Player::getCommand() const
{
    return COMMAND_PLAYER;
}

} // namespace MKTG::Command
