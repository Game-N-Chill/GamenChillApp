
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Load::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    std::string fileType = args[1].substr(args[1].size() - 4);
    if (fileType == "xlsx") {
        gen.LoadSolo(args[1]);
    } else if (fileType == "json") {
        gen.LoadDuo(args[1]);
    } else {
        throw std::runtime_error("can't load file type: " + fileType);
    }
    return Result::CONTINUE;
}

std::string Load::getCommand() const
{
    return COMMAND_LOAD;
}

} // namespace MKTG::Command
