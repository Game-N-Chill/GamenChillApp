
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Count::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("ERROR: not enough arguments");
    }

    gen.setPlayerCount(std::atoi(args[1].c_str()));
    return Result::CONTINUE;
}

std::string Count::getCommand() const
{
    return COMMAND_COUNT;
}

} // namespace MKTG::Command
