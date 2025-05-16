
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Team::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 7) {
        throw std::runtime_error("not enough arguments");
    }

    size_t rank = std::atoi(args[1].c_str());
    std::string name = args[2];
    std::string character_01 = args[3];
    std::string player_01 = args[4];
    std::string character_02 = args[5];
    std::string player_02 = args[6];

    gen.setDuoInfo(rank, name, character_01, player_01, character_02, player_02);
    return Result::CONTINUE;
}

std::string Team::getCommand() const
{
    return COMMAND_TEAM;
}

} // namespace MKTG::Command
