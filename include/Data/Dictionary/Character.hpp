
#pragma once

#include <iostream>
#include <fstream>
#include <list>

namespace Generator::Data
{

    #define PATH_CHARACTER_DIR                  "Assets\\Images\\Characters\\"

    #define DATA_CHARACTER_DEFAULT_NAME         "Mario"
    #define DATA_CHARACTER_DEFAULT_PATH         "Assets\\Images\\Characters\\Mario"

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

} // namespace Generator::Data

std::ostream &operator<<(std::ostream &flux, const Generator::Data::Character &character);
