
#pragma once

#include <iostream>
#include <list>

#include "Utils.hpp"

namespace GNCApp::Data
{

    #define DATA_BRACKET_DEFAULT_OUTPUT_DIR          "result"

class Seeding : public Utils::Singleton<Seeding>
{
    public:
        class Player
        {
            public:
                Player();
                Player(std::string name, float seeding);
                ~Player() = default;

                std::string getName() const;
                void setName(std::string name);

                float getSeeding() const;
                void setSeeding(float value);

                bool operator==(const Player &other) const;
                bool operator==(const std::string &name) const;
                bool operator!=(const Player &other) const;
                bool operator!=(const std::string &name) const;
                bool operator>(const Player &other) const;
                bool operator<(const Player &other) const;

            private:
                std::string _name;
                float _seeding;
        };

        ~Seeding() = default;

        std::string getOutputPath() const;
        void setOutputPath(std::string path);

        size_t getEdition() const;
        void setEdition(size_t value);

        void addPlayer(size_t pos = std::string::npos);
        void addPlayer(const Player &player, size_t pos = std::string::npos);
        void addPlayer(std::string name, float seeding, size_t pos = std::string::npos);
        void removePlayer(size_t index);
        void removePlayer(std::string name);
        void removePlayer(const Player &player);
        void clear();
        Player getPlayer(size_t index) const;
        Player getPlayer(std::string name) const;
        Player &atPlayer(size_t index);
        Player &atPlayer(std::string name);
        Player &operator[](size_t index);
        Player &operator[](std::string name);
        size_t getSize() const;
        void move(int indexSrc, int indexDest);
        void sort();

        void loadFromFile();

    private:
        friend class Utils::Singleton<Seeding>;
        Seeding();

        std::string _pathOutput;
        size_t _edition;
        std::list<Player> _list;
};

}

// bool operator==(const GNCApp::Data::Seeding::Player &left, const GNCApp::Data::Seeding::Player &right)
// {
//     return true;
//     // return (left.getName() == right.getName());
// }
