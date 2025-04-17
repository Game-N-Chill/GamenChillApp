
#pragma once

#include "Generator/Generator.hpp"
#include <iostream>

namespace MKTG::Command
{

enum Result
{
    CONTINUE,
    SUCCESS,
    FAILURE
};

class ICommand
{
    public:
        virtual ~ICommand() = default;

        virtual Result run(MKTG::Generator &gen, std::string args) = 0;
        virtual std::string getCommand() const = 0;
};

typedef std::shared_ptr<ICommand> SharedICommand;

} // namespace MKTG
