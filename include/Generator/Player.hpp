
#pragma once

#include <iostream>
#include <filesystem>

namespace MKTG
{

    #define PATH_CHARACTERS_DIR             "Assets\\Images\\Characters\\"
    #define CHARACTER_DEFAULT_NAME          "default"

struct Player
{
    private:
    std::vector<std::string> skins;
    std::vector<std::string>::iterator skin;

    public:
    std::string character;
    std::string name;

    void parseSkins(size_t rank)
    {
        skins.clear();
        skin = skins.end();

        std::string pathDir = Utils::getFullPath(PATH_CHARACTERS_DIR) + character;
        if (!std::filesystem::is_directory(pathDir)) {
            std::cerr << "ERROR: " << pathDir << " is not a directory, can't setup skins" << std::endl;
            return;
        }

        for (const auto &entry : std::filesystem::recursive_directory_iterator(pathDir)) {
            if (entry.is_regular_file()) {
                std::string path = entry.path().string();
                std::string name = path.substr(pathDir.size() + 1, path.size() - (pathDir.size() + 1) - 4);
                if (name != CHARACTER_DEFAULT_NAME) {
                    skins.push_back(name);
                }
            }
        }

        if (rank == 1) {
            setSkin();
        } else {
            skin = skins.end();
        }
    }

    std::string getSkin() const
    {
        if (skin == skins.end()) {
            return CHARACTER_DEFAULT_NAME;
        } else {
            return *skin;
        }
    }

    void setSkin()
    {
        if (skins.empty()) {
            skin = skins.end();
            return;
        }

        Utils::Randomizer rand;
        this->skin = this->skins.begin();
        std::advance(this->skin, rand.GetRandom(this->skins.size()));
    }

    void setSkin(std::string name)
    {
        if (name.empty()) {
            setSkin();
            return;
        }

        if (skins.empty()) {
            skin = skins.end();
            return;
        }

        auto it = std::find(skins.begin(), skins.end(), name);
        if (it != this->skins.end()) {
            this->skin = it;
        } else {
            throw std::out_of_range("can't find skin " + name);
        }
    }
};

template<size_t N>
struct Team
{
    std::array<Player, N> players;
    std::size_t rank;
    std::string name;

    Team(size_t rank)
    {
        this->rank = rank;
        this->name = "Team";
        for (size_t i = 0; i < N; i++) {
            this->players[i].character = "Mario";
            this->players[i].name = "Player";
            this->players[i].parseSkins(this->rank);
        }
    }
};

template<size_t N>
using SharedTeam = std::shared_ptr<Team<N>>;

typedef SharedTeam<1>   Solo;
typedef SharedTeam<2>   Duo;

} // namespace MKTG
