
#pragma once

#include <iostream>
#include <array>
#include <map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Player.hpp"
#include "Utils.hpp"

namespace MKTG
{

    #define PLAYER_GRAPH_COUNT      8
    #define PATH_BACKGROUND_DIR             "Assets\\Images\\Background\\"

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

        std::string getBackgroundName() const;
        std::string getBackgroundPath() const;
        void setBackground();
        void setBackground(std::string name);

        void setImageDir(std::string path);
        std::string getImageDir() const;


        Solo getSoloInfo(size_t rank);
        Duo getDuoInfo(size_t rank);
        void setSoloInfo(size_t rank, std::string character, std::string name);
        void setDuoInfo(size_t rank, std::string name, std::string character_01, std::string player_01, std::string character_02, std::string player_02);
        void printSolo();
        void printDuo();

        void LoadSolo(std::string excelPath = "");
        void LoadDuo(std::string jsonPath = "");
        void createSolo();
        void createDuo();

    private:
        std::string _title;
        std::string _subtitle;
        std::string _date;
        size_t _playerCount;
        std::string _discordUrl;

        // json _dataLinks;
        // std::string _dataCharacter;
        // std::vector<std::string> _dataTracks;
        // std::vector<std::string>::iterator _dataTrackIt;
        std::map<std::string, std::string> _backgrounds;
        std::map<std::string, std::string>::iterator _backgroundIt;

        std::string _imageDir;

        std::array<Solo, PLAYER_GRAPH_COUNT> _solo;
        std::array<Duo,  PLAYER_GRAPH_COUNT> _duo;
        json _tags;


        template<size_t N>
        SharedTeam<N> getTeamInfo(size_t rank, std::array<SharedTeam<N>, PLAYER_GRAPH_COUNT> &array)
        {
            if (rank < 1 || rank > 8) {
                std::cerr << "ERROR: rank out of range: " << rank << ", must be: [1,8]" << std::endl;
                return nullptr;
            }
            return array[rank - 1];
        }

        template<size_t N>
        void setTeamInfo(size_t rank, std::string name, size_t index, std::string character, std::string player, std::array<SharedTeam<N>, PLAYER_GRAPH_COUNT> &array)
        {
            if (rank < 1 || rank > 8) {
                std::cerr << "ERROR: rank out of range: " << rank << ", must be: [1,8]" << std::endl;
                return;
            }
            if (index >= N) {
                std::cerr << "ERROR: index out of range: " << index << ", must be: [0,N[" << std::endl;
                return;
            }

            SharedTeam<N> team = array[rank - 1];
            if (team == nullptr) {
                std::cerr << "ERROR: can't find team of rank " << rank << std::endl;
                return;
            }

            team->name = name;
            team->rank = rank;
            team->players[index].character = character;
            team->players[index].name = Utils::getCompleteName(player, this->_tags);
            team->players[index].parseSkins(rank);
        }

        template<size_t N>
        void createImage(std::string path, std::array<SharedTeam<N>, PLAYER_GRAPH_COUNT> &array)
        {
            if (path.empty()) {
                throw std::runtime_error("can't open file: " + path);
            }
            Render::Canva canva(path);

            canva.getImage("background")->load(this->_backgroundIt->second);
            canva.getText("title")->load(this->_title);
            canva.getText("titleOutline")->load(this->_title);
            canva.getText("subtitle")->load(this->_subtitle);
            canva.getText("subtitleOutline")->load(this->_subtitle);
            canva.getText("date")->load(this->_date + " - " + std::to_string(this->_playerCount) + " Participants");
            canva.getText("dateOutline")->load(this->_date + " - " + std::to_string(this->_playerCount) + " Participants");
            canva.getText("url")->load(this->_discordUrl);
            canva.getText("urlOutline")->load(this->_discordUrl);

            for (size_t i = 0; i < array.size(); i++) {
                SharedTeam<N> team = array[i];

                if (N > 1) {
                    canva.getText(std::to_string(i + 1) + '_' + "Team")->load(team->name);
                }

                std::string name;
                for (size_t j = 0; j < team->players.size(); j++) {
                    canva.getImage(std::to_string(i + 1) + '_' + std::to_string(j + 1) + '_' + "Character")->load(Utils::getFullPath(PATH_CHARACTERS_DIR) + team->players[j].character + '\\' + team->players[j].getSkin() + ".png");
                    name += team->players[j].name;
                    if (j < team->players.size() - 1) {
                        name += " - ";
                    }
                }
                canva.getText(std::to_string(i + 1) + '_' + "Name")->load(name);
            }

            std::vector<std::string> vec = canva.getOrder();
            for (auto &obj : vec) {
                canva.draw(obj);
            }
            canva.save(this->_imageDir, Utils::getTimeFormat("%Y_%m_%d__%H_%M_%S"));
        }
};

} // namespace MKTG
