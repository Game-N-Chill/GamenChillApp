
#pragma once

#include <iostream>
#include <list>
#include <GoGuLib.hpp>

namespace GNCApp::Data
{

    #define DATA_BRACKET_DEFAULT_OUTPUT_DIR          "result"

class Seeding : public  GGL::Singleton<Seeding>
{
    public:
        class Player
        {
            public:
                Player();
                Player(std::string name, double seeding);
                ~Player() = default;

                std::string getName() const;
                void setName(std::string name);

                double getSeeding() const;
                void setSeeding(double value);

                bool operator==(const Player &other) const;
                bool operator==(const std::string &name) const;
                bool operator!=(const Player &other) const;
                bool operator!=(const std::string &name) const;
                bool operator>(const Player &other) const;
                bool operator<(const Player &other) const;

            private:
                std::string _name;
                double _seeding;
        };

        ~Seeding() = default;

        std::string getOutputPath() const;
        void setOutputPath(std::string path);

        size_t getNumber() const;
        void setNumber(size_t value);

        std::string getEdition() const;
        void setEdition(std::string value);

        void addPlayer(size_t pos = std::string::npos);
        void addPlayer(const Player &player, size_t pos = std::string::npos);
        void addPlayer(std::string name, double seeding = std::numeric_limits<double>::infinity(), size_t pos = std::string::npos);
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
        void sort(const std::map<std::string, double> &map);

    private:
        friend class  GGL::Singleton<Seeding>;
        Seeding();

        std::string _pathOutput;
        size_t _number;
        std::string _edition;
        std::list<Player> _list;
};

}
