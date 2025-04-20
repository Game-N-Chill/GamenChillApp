
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Create::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    gen.createImage();
    return Result::CONTINUE;
}

std::string Create::getCommand() const
{
    return COMMAND_CREATE;
}

} // namespace MKTG::Command
