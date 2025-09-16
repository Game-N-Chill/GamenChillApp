
#pragma once

#include <iostream>
#include <fstream>
#include <list>

namespace GNCApp::Data
{

    #define PATH_CHARACTER_DIR                  "Assets/Images/Winner/Characters/"

    #define DATA_CHARACTER_DEFAULT_NAME         "Mario"
    #define DATA_CHARACTER_DEFAULT_PATH         "Assets/Images/Winner/Characters/Mario/"

struct Character
{
    std::string name;
    std::string path;

    Character();
    Character(std::string str);

    bool operator==(std::string key);
    explicit operator std::string() const;

    static void load(std::list<Character> &list);
};

} // namespace GNCApp::Data

std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Character &character);
