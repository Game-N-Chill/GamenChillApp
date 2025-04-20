
#pragma once

#include "Interface.hpp"

namespace MKTG::Command
{

    #define COMMAND_DATE           "date"

class Date : public ICommand
{
    public:
        Result run(MKTG::Generator &gen, std::vector<std::string> &args);
        std::string getCommand() const;
};

} // namespace MKTG::Command
