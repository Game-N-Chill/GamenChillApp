
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Url::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("ERROR: not enough arguments");
    }

    gen.setDiscordUrl(args[1]);
    return Result::CONTINUE;
}

std::string Url::getCommand() const
{
    return COMMAND_URL;
}

} // namespace MKTG::Command
