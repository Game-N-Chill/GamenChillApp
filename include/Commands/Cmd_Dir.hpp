
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_DIR           "dir"

class Dir : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::string args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
