
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Version::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    std::cout << "MarioKartTopGenerator " << MKTG_VERSION << std::endl;
    return Result::CONTINUE;
}

std::string Version::getCommand() const
{
    return COMMAND_VERSION;
}

} // namespace MKTG::Command
