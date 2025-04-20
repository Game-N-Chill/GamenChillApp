
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_URL           "url"

class Url : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::vector<std::string> &args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
