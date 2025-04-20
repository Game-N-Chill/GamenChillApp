
#include "MKTG.hpp"
#include <regex>

namespace MKTG::Command
{

Result Date::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    std::regex regex("[0-9][0-9]\\/[0-9][0-9]\\/[0-9][0-9][0-9][0-9]");
    std::smatch match;

    if (!std::regex_match(args[1], match, regex)) {
        throw std::runtime_error("date must on format XX/XX/XXXX");
    }

    gen.setDate(args[1]);
    return Result::CONTINUE;
}

std::string Date::getCommand() const
{
    return COMMAND_DATE;
}

} // namespace MKTG::Command
