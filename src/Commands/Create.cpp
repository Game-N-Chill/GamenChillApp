
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Create::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    std::string team = Utils::stringToUpper(args[1]);
    if (team == "SOLO") {
        gen.createSolo();
    } else if (team == "DUO") {
        gen.createDuo();
    } else {
        throw std::runtime_error("can't find team name: " + team);
    }
    return Result::CONTINUE;
}

std::string Create::getCommand() const
{
    return COMMAND_CREATE;
}

} // namespace MKTG::Command
