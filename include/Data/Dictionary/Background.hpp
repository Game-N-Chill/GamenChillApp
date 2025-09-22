
#pragma once

#include <iostream>
#include <list>
#include <filesystem>

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
    bool operator==(Background key);
    explicit operator std::string() const;

    template<typename T>
    static void load(std::list<T> &list, std::string game)
    {
        static_assert(std::is_base_of<Background, T>::value);

        std::string pathDir = PATH_BACKGROUND_DIR + game + '/';
        for (const auto &entry : std::filesystem::recursive_directory_iterator(pathDir)) {
            if (entry.is_regular_file()) {
                list.push_back(T(entry.path().string()));
            }
        }
    }
};

struct BackgroundMKWorld : public Background
{
    BackgroundMKWorld() = default;
    BackgroundMKWorld(std::string path);

    static void load(std::list<BackgroundMKWorld> &list);
};

struct BackgroundMK8 : public Background
{
    BackgroundMK8() = default;
    BackgroundMK8(std::string path);

    static void load(std::list<BackgroundMK8> &list);
};

} // namespace GNCApp::Data

std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Background &background);
