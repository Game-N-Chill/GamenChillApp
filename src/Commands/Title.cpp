
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Title::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    gen.setTitle(args[1]);
    return Result::CONTINUE;
}

std::string Title::getCommand() const
{
    return COMMAND_TITLE;
}

} // namespace MKTG::Command
