
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_SUBTITLE           "subtitle"

class SubTitle : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::vector<std::string> &args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
