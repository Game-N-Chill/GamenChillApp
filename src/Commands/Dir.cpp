
#include "MKTG.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace MKTG::Command
{

Result Dir::run(MKTG::Generator &gen, std::string args)
{
    if (!fs::is_directory(args)) {
        std::cerr << "ERROR: can't find directory " << args << std::endl;
        return Result::CONTINUE;
    }
    gen.setImageDir(args);
    return Result::CONTINUE;
}

std::string Dir::getCommand() const
{
    return COMMAND_DIR;
}

} // namespace MKTG::Command
