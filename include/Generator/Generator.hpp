
#pragma once

#include <iostream>
#include <array>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Player.hpp"
#include "Utils.hpp"

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


        void setDataLink(std::string character);
        void nextDataTrack();
        void prevDataTrack();
        std::string getDataCharacter() const;
        std::string getDataTrack() const;


        void setImageDir(std::string path);
        std::string getImageDir() const;


        Solo getSoloInfo(size_t rank);
        Duo getDuoInfo(size_t rank);
        void setSoloInfo(size_t rank, std::string character, std::string name);
        void setDuoInfo(size_t rank, size_t index, std::string character, std::string name);


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

        json _dataLinks;
        std::string _dataCharacter;
        std::vector<std::string> _dataTracks;
        std::vector<std::string>::iterator _dataTrackIt;

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
        void setTeamInfo(size_t rank, size_t index, std::string character, std::string name, std::array<SharedTeam<N>, PLAYER_GRAPH_COUNT> &array)
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

            team->rank = rank;
            team->players[index].character = character;
            team->players[index].name = Utils::getCompleteName(name, this->_tags);

            if (rank == 1) {
                this->setDataLink(character);
            }
        }

        template<size_t N>
        void createImage(std::string path, std::array<SharedTeam<N>, PLAYER_GRAPH_COUNT> &array)
        {
            if (path.empty()) {
                throw std::runtime_error("can't open file: " + path);
            }
            Render::Canva canva(path);

            canva.getImage("background")->load("Assets\\Images\\Background\\" + *this->_dataTrackIt + ".png");
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
                for (size_t j = 0; j < team->players.size(); j++) {
                    canva.getImage(std::to_string(i + 1) + '_' + std::to_string(j + 1) + '_' + "Character")->load("Assets\\Images\\Characters\\" + team->players[j].character + "\\default.png");
                    canva.getText(std::to_string(i + 1) + '_' + std::to_string(j + 1) + '_' + "Name")->load(team->players[j].name);
                }
            }

            std::vector<std::string> vec = canva.getOrder();
            for (auto &obj : vec) {
                canva.draw(obj);
            }
            canva.save(this->_imageDir, Utils::getTimeFormat("%Y_%m_%d__%H_%M_%S"));
        }
};

} // namespace MKTG
