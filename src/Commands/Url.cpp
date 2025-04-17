
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Url::run(MKTG::Generator &gen, std::string args)
{
    gen.setDiscordUrl(args);
    return Result::CONTINUE;
}

std::string Url::getCommand() const
{
    return COMMAND_URL;
}

} // namespace MKTG::Command
