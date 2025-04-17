
#include "MKTG.hpp"
#include <regex>

namespace MKTG::Command
{

Result Date::run(MKTG::Generator &gen, std::string args)
{
    std::regex regex("[0-9][0-9]\\/[0-9][0-9]\\/[0-9][0-9][0-9][0-9]");
    std::smatch match;

    if (!std::regex_match(args, match, regex)) {
        std::cerr << "ERROR: date must on format XX/XX/XXXX" << std::endl;
        return Result::CONTINUE;
    }

    gen.setDate(args);
    return Result::CONTINUE;
}

std::string Date::getCommand() const
{
    return COMMAND_DATE;
}

} // namespace MKTG::Command
