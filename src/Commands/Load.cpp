
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Load::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    gen.Load(args[1]);
    return Result::CONTINUE;
}

std::string Load::getCommand() const
{
    return COMMAND_LOAD;
}

} // namespace MKTG::Command
