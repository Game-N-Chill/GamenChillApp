
#pragma once

#include <iostream>
#include <vector>

#include "Utils.hpp"
#include "Data/Player.hpp"
#include "Data/Dictionary/Dictionary.hpp"

namespace GNCApp::Data
{

    #define PLAYER_GRAPH_COUNT                      8

    #define DATA_WINNER_DEFAULT_TITLE               "RIFIFI sur le Circuit #00"
    #define DATA_WINNER_DEFAULT_SUBTITLE            "Edition 150cc"
    #define DATA_WINNER_DEFAULT_DATE                "01/01/2000"
    #define DATA_WINNER_DEFAULT_PLAYER_COUNT        16
    #define DATA_WINNER_DEFAULT_OUTPUT_DIR          "result"

    #define DATA_WINNER_GAME_MKWORLD                0
    #define DATA_WINNER_GAME_MK8                    1

    #define PATH_CHARACTERS_DIR                     "Assets\\Images\\Characters\\"

    #define DATA_WINNER_PLAYER_DEFAULT_NAME         "Player"
    #define DATA_WINNER_PLAYER_DEFAULT_CHARACTER    "Mario"
    #define DATA_WINNER_PLAYER_DEFAULT_SKIN         "default"
    #define DATA_WINNER_TEAM_DEFAULT_NAME           "Team"

class Winner : public Utils::Singleton<Winner>
{
    public:
        class Player
        {
            public:
                Player();
                ~Player() = default;

                void setName(std::string name);
                std::string getName() const;

                void setCharacter(size_t index);
                void setCharacter(std::string character);
                Character getCharacter() const;

                void setSkin(std::string name);
                void setSkin(size_t index);
                std::string getSkin() const;
                std::list<std::string> getSkinList() const;
                void parseSkins();
                void randomizeSkin();

                void print(std::ostream &flux = std::cout) const;

            private:
                std::string _name;
                Character _character;

                std::list<std::string> _skins;
                size_t _index;
        };

        template<size_t N>
        class Team
        {
            public:
                Team()
                {
                    this->_name = DATA_WINNER_TEAM_DEFAULT_NAME;
                    for (size_t i = 0; i < N; i++) {
                        this->_players[i].setCharacter(DATA_WINNER_PLAYER_DEFAULT_CHARACTER);
                        this->_players[i].setName(DATA_WINNER_PLAYER_DEFAULT_NAME);
                        this->_players[i].parseSkins();
                    }
                }

                std::string getName() const
                {
                    return this->_name;
                }

                void setName(std::string name)
                {
                    this->_name = name;
                }

                std::string &operator*()
                {
                    return this->_name;
                }

                Player getPlayer(size_t index) const
                {
                    return this->_players[index];
                }

                void setPlayer(Player player, size_t index)
                {
                    this->_players[index] = player;
                }

                Player &atPlayer(size_t index)
                {
                    return this->_players[index];
                }

                Player &operator[](size_t index)
                {
                    return atPlayer(index);
                }

                void print(std::ostream &flux = std::cout) const
                {
                    flux << "Name: " << this->_name << std::endl;
                    for (size_t i = 0; i < N; i++) {
                        flux << "Player " << i + 1 << ": " << std::endl;
                        this->_players[i].print(flux);
                    }
                }

            private:
                std::string _name;
                std::array<Player, N> _players;
        };

        template<size_t N>
        using SharedTeam = std::shared_ptr<Team<N>>;

        typedef Team<1>         Solo;
        typedef Team<2>         Duo;

        typedef SharedTeam<1>   SharedSolo;
        typedef SharedTeam<2>   SharedDuo;


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
        int getGame() const;

        void setTitle(std::string str);
        void setSubtitle(std::string str);
        void setDate(std::string str);
        void setPlayerCount(size_t value);
        void setOutputDir(std::string str);
        template<typename T>
        void setBackground(size_t index)
        {
            static_assert(std::is_base_of<Background, T>::value);

            try {
                this->_background = Data::Dictionary<T>::getInstance()->find(index);
            } catch (std::out_of_range &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        template<typename T>
        void setBackground(std::string str)
        {
            static_assert(std::is_base_of<Background, T>::value);

            try {
                this->_background = Data::Dictionary<T>::getInstance()->find(str);
            } catch (std::out_of_range &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        void setGame(int game);

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
        int _game;

        std::array<Solo, PLAYER_GRAPH_COUNT> _solo;
        std::array<Duo,  PLAYER_GRAPH_COUNT> _duo;
};

} // namespace GNCApp::Data

template<size_t N>
std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Winner::Team<N> team)
{
    team.print(flux);
    return flux;
}

std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Winner &winner);
