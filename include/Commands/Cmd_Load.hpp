
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_LOAD           "load"

class Load : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::string args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
