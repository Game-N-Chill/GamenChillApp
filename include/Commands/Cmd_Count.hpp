
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_COUNT           "count"

class Count : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::string args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
