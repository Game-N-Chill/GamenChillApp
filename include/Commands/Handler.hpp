
#pragma once

#include <iostream>
#include <map>

#include "Interface.hpp"
#include "Cmd_Help.hpp"
#include "Cmd_Version.hpp"
#include "Cmd_Quit.hpp"
#include "Cmd_List.hpp"

#include "Cmd_Title.hpp"
#include "Cmd_SubTitle.hpp"
#include "Cmd_Date.hpp"
#include "Cmd_Count.hpp"
#include "Cmd_Url.hpp"

#include "Cmd_Load.hpp"
#include "Cmd_Player.hpp"
#include "Cmd_Team.hpp"
#include "Cmd_Background.hpp"
#include "Cmd_Skin.hpp"
#include "Cmd_Print.hpp"

#include "Cmd_Dir.hpp"
#include "Cmd_Create.hpp"

namespace MKTG::Command
{

class Handler
{
    public:
        Handler()
        {
            addCommand<Help>();
            addCommand<Version>();
            addCommand<Quit>();
            addCommand<List>();

            addCommand<Title>();
            addCommand<SubTitle>();
            addCommand<Date>();
            addCommand<Count>();
            addCommand<Url>();

            addCommand<Load>();
            addCommand<Player>();
            addCommand<Team>();
            addCommand<Background>();
            addCommand<Skin>();
            addCommand<Print>();

            addCommand<Dir>();
            addCommand<Create>();
        }

        ~Handler() = default;

        template<typename T>
        void addCommand()
        {
            static_assert(std::is_base_of<ICommand, T>::value, "T must be a base of ICommand");
            this->_list.push_back(std::make_shared<T>());
        }

        std::shared_ptr<ICommand> findCommand(std::string cmd)
        {
            auto it = std::find_if(this->_list.begin(), this->_list.end(), [&](std::shared_ptr<ICommand> command) {
                return (command->getCommand() == cmd);
            });
            if (it == this->_list.end()) {
                throw std::out_of_range("can't find command " + cmd);
            }
            return *it;
        }

        std::shared_ptr<ICommand> operator[](std::string cmd)
        {
            return findCommand(cmd);
        }

    private:
        std::list<std::shared_ptr<ICommand>> _list;
};

} // namespace MKTG
