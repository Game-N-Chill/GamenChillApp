
#include "MKTG.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace MKTG::Command
{

Result Dir::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    if (!fs::is_directory(args[1])) {
        throw std::runtime_error("can't find directory " + args[1]);
    }
    gen.setImageDir(args[1]);
    return Result::CONTINUE;
}

std::string Dir::getCommand() const
{
    return COMMAND_DIR;
}

} // namespace MKTG::Command
