
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_QUIT           "quit"

class Quit : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::string args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
