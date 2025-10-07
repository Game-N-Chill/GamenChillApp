
#include "Logic/ProgressTask.hpp"

namespace GNCApp::Logic
{

ProgressTask::ProgressTask()
{
    reset();
}

void ProgressTask::addTask(std::string str)
{
    this->_list.push_back(str);
    if (this->_it == this->_list.end()) {
        this->_it = this->_list.begin();
    }
}

std::string ProgressTask::getTaskName() const
{
    if (this->_it == this->_list.end())
        return "Done !";
    return *_it;
}

int ProgressTask::getTaskValue() const
{
    if (this->_it == this->_list.end())
        return 100;
    return static_cast<int>(static_cast<float>(this->_pos) / static_cast<float>(this->_list.size()) * 100.0f);
}

void ProgressTask::progress()
{
    if (this->_it == this->_list.end())
        return;

    this->_it++;
    this->_pos++;
}

void ProgressTask::reset()
{
    this->_list.clear();
    this->_it = this->_list.end();
    this->_pos = 0;
}


std::string ProgressTask::operator*() const
{
    return this->getTaskName();
}

int ProgressTask::operator!() const
{
    return this->getTaskValue();
}

ProgressTask &ProgressTask::operator<<(std::string str)
{
    addTask(str);
    return *this;
}

ProgressTask &ProgressTask::operator++(int)
{
    progress();
    return *this;
}

void ProgressTask::operator~()
{
    reset();
}


void ProgressTask::loadTaskWinner()
{
    auto instance = ProgressTask::getInstance();
    *instance << "loading images"
              << "loading texts"
              << "bringing modification to canva"
              << "drawing canva"
              << "saving canva";
}

void ProgressTask::loadTaskBracket()
{
    auto instance = ProgressTask::getInstance();
    *instance << "copying template"
              << "modifying information"
              << "modifying seeding"
              << "saving file";
}

void ProgressTask::loadTaskSeeding()
{
    auto instance = ProgressTask::getInstance();
    *instance << "downloading seeding file"
              << "parsing seeding file"
              << "modifying seeding list";
}

}
