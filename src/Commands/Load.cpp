
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Load::run(MKTG::Generator &gen, std::string args)
{
    for (auto it = args.begin(); it != args.end(); it++) {
        if (*it == '"') {
            it = args.erase(it);
            if (it == args.end()) {
                break;
            }
        }
    }

    gen.Load(args);
    return Result::CONTINUE;
}

std::string Load::getCommand() const
{
    return COMMAND_LOAD;
}

} // namespace MKTG::Command
