
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Skin::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    std::string team = Utils::stringToUpper(args[1]);
    std::string name;
    size_t rank = 1;

    if (args.size() > 2) {
        name = args[2];
    }
    if (args.size() > 3) {
        rank = std::atoll(args[3].c_str());
    }

    if (team == "SOLO") {
        gen.getSoloInfo(rank)->players[0].setSkin(name);
    } else if (team == "DUO") {
        Duo duo = gen.getDuoInfo(rank);
        for (size_t i = 0; i < duo->players.size(); i++) {
            duo->players[i].setSkin(name);
        }
    } else {
        throw std::runtime_error("can't find team name: " + team);
    }

    return Result::CONTINUE;
}

std::string Skin::getCommand() const
{
    return COMMAND_SKIN;
}

} // namespace MKTG::Command
