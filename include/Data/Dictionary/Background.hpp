
#pragma once

#include <iostream>
#include <list>

namespace GNCApp::Data
{

    #define PATH_BACKGROUND_DIR                 "assets/Images/Winner/Background/"

    #define DATA_BACKGROUND_GAME_MK8            "MK8"
    #define DATA_BACKGROUND_GAME_MKWORLD        "MKWorld"

    #define DATA_BACKGROUND_DEFAULT_GAME        DATA_BACKGROUND_GAME_MKWORLD
    #define DATA_BACKGROUND_DEFAULT_CUP         "Champignon"
    #define DATA_BACKGROUND_DEFAULT_TRACK       "Champidrome"
    #define DATA_BACKGROUND_DEFAULT_PATH        "assets/Images/Winner/Background/MKWorld/01_Champignon/01_Champidrome.png"

struct Background
{
    std::string game;
    std::string cup;
    std::string track;
    std::string path;

    Background();
    Background(std::string path);

    std::string get() const;

    bool operator==(std::string key);
    explicit operator std::string() const;

    static void load(std::list<Background> &list);
};

} // namespace GNCApp::Data

std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Background &background);
