
#include "MKTG.hpp"

namespace MKTG::Command
{

Result SubTitle::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    gen.setSubtitle(args[1]);
    return Result::CONTINUE;
}

std::string SubTitle::getCommand() const
{
    return COMMAND_SUBTITLE;
}

} // namespace MKTG::Command
