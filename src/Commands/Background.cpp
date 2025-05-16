
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Background::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() > 1) {
        gen.setBackground(args[1]);
    } else {
        gen.setBackground();
    }
    return Result::CONTINUE;
}

std::string Background::getCommand() const
{
    return COMMAND_BACKGROUND;
}

} // namespace MKTG::Command
