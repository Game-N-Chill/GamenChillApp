
#pragma once

#include <iostream>
#include <vector>

#include "Utils.hpp"
#include "Data/Player.hpp"
#include "Data/Dictionary/Dictionary.hpp"

namespace GNCApp::Data
{

    #define PLAYER_GRAPH_COUNT                  8

    #define DATA_WINNER_DEFAULT_TITLE           "RIFIFI sur le Circuit #00"
    #define DATA_WINNER_DEFAULT_SUBTITLE        "Edition 150cc"
    #define DATA_WINNER_DEFAULT_DATE            "01/01/2000"
    #define DATA_WINNER_DEFAULT_PLAYER_COUNT    16
    #define DATA_WINNER_DEFAULT_OUTPUT_DIR      "result"

class Winner : public Utils::Singleton<Winner>
{
    public:
        ~Winner() = default;

        std::string getTitle() const;
        std::string getSubtitle() const;
        std::string getDate() const;
        size_t getPlayerCount() const;
        std::string getOutputDir() const;
        Background getBackground() const;
        std::array<Solo, PLAYER_GRAPH_COUNT> &getSolo();
        Solo &getTeamSolo(size_t index);
        std::array<Duo, PLAYER_GRAPH_COUNT> &getDuo();
        Duo &getTeamDuo(size_t index);

        void setTitle(std::string str);
        void setSubtitle(std::string str);
        void setDate(std::string str);
        void setPlayerCount(size_t value);
        void setOutputDir(std::string str);
        void setBackground(size_t index);
        void setBackground(std::string str);

        void randomizeBackground();

        void print(std::ostream &flux = std::cout) const;

    private:
        friend class Utils::Singleton<Winner>;
        Winner();

        std::string _title;
        std::string _subtitle;
        std::string _date;
        size_t _playerCount;
        std::string _outputDir;
        Background _background;

        std::array<Solo, PLAYER_GRAPH_COUNT> _solo;
        std::array<Duo,  PLAYER_GRAPH_COUNT> _duo;
};

} // namespace GNCApp::Data

std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Winner &winner);
