
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

        std::string getTitle() const;
        std::string getSubtitle() const;
        std::string getDate() const;
        size_t getPlayerCount() const;
        std::string getDiscordUrl() const;

        void setTitle(std::string str);
        void setSubtitle(std::string str);
        void setDate(std::string str);
        void setPlayerCount(size_t value);
        void setDiscordUrl(std::string str);

        void Load(std::string excelPath = "");

        void setDataLink(std::string character);
        void nextDataTrack();
        void prevDataTrack();
        std::string getDataCharacter() const;
        std::string getDataTrack() const;

        void setPlayerInfo(size_t rank, std::string character, std::string name);
        SharedPlayer getPlayerInfo(size_t rank) const;

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
        json _tags;

        std::string _imageDir;
};

} // namespace MKTG

std::ostream &operator<<(std::ostream &flux, MKTG::Player &player);
// std::ostream &operator<<(std::ostream &flux, MKTG::PlayerManager &playerManager);
