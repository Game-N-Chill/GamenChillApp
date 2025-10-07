
#pragma once

#include <iostream>
#include <list>
#include <thread>
#include "Utils.hpp"

namespace GNCApp::Logic
{

#define DO_PROGRESS_TASK        (*Logic::ProgressTask::getInstance())++

class ProgressTask : public Utils::Singleton<ProgressTask>
{
    public:
        ~ProgressTask() = default;

        void addTask(std::string str);
        ProgressTask &operator<<(std::string str);

        std::string getTaskName() const;
        std::string operator*() const;

        int getTaskValue() const;
        int operator!() const;

        void progress();
        ProgressTask &operator++(int);

        void reset();
        void operator~();


        static void loadTaskWinner();
        static void loadTaskBracket();

    private:
        friend class Utils::Singleton<ProgressTask>;
        ProgressTask();

        std::list<std::string> _list;
        std::list<std::string>::iterator _it;
        size_t _pos;
};

}
