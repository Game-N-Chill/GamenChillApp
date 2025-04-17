
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_CREATE           "create"

class Create : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::string args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
