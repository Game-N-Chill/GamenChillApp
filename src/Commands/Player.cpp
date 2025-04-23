
#include "MKTG.hpp"

namespace MKTG::Command
{
// player <solo/duo> <rank> <index> <character> <name>
Result Player::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 6) {
        throw std::runtime_error("not enough arguments");
    }

    std::string team = Utils::stringToUpper(args[1]);
    size_t rank = std::atoi(args[2].c_str());
    size_t index = std::atoi(args[3].c_str());
    std::string character = args[4];
    std::string name = args[5];

    if (team == "SOLO") {
        gen.setSoloInfo(rank, character, name);
    } else if (team == "DUO") {
        gen.setDuoInfo(rank, index, character, name);
    } else {
        throw std::runtime_error("can't find team name: " + team);
    }

    return Result::CONTINUE;
}

std::string Player::getCommand() const
{
    return COMMAND_PLAYER;
}

} // namespace MKTG::Command
