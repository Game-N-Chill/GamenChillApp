
#pragma once

#include <iostream>
#include <array>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Player.hpp"

namespace MKTG
{

    #define PLAYER_GRAPH_COUNT      8

class Generator
{
    public:
        Generator(std::string excelPath = "");
        ~Generator() = default;

        void Load(std::string excelPath = "");

        void setDataLink(std::string character);
        void nextDataLink();
        void prevDataLink();
        std::string getDataCharacter() const;
        std::string getDataTrack() const;

        std::string getTitle() const;
        std::string getSubtitle() const;
        std::string getDate() const;
        size_t getPlayerCount() const;
        std::string getDiscordUrl() const;

        void getTitle(std::string str);
        void getSubtitle(std::string str);
        void getDate(std::string str);
        void getPlayerCount(size_t value);
        void getDiscordUrl(std::string str);

        void createImage();
        void setImageDir(std::string path);
        std::string getImageDir() const;

    private:
        std::string _title;
        std::string _subtitle;
        std::string _date;
        size_t _playerCount;
        std::string _discordUrl;

        json _dataLinks;
        std::string _dataCharacter;
        std::vector<std::string> _dataTracks;
        std::vector<std::string>::iterator _dataTrackIt;

        std::array<SharedPlayer, PLAYER_GRAPH_COUNT> _players;

        std::string _imageDir;
};

} // namespace MKTG

std::ostream &operator<<(std::ostream &flux, MKTG::Player &player);
// std::ostream &operator<<(std::ostream &flux, MKTG::PlayerManager &playerManager);
