
#pragma once

#include <iostream>

namespace MKTG
{

class Player
{
    public:
        Player();
        Player(std::string character, std::string name, std::size_t rank);

        void LoadExcelData();

        void SetCharacter(std::string character);
        void SetName(std::string name);
        void SetRank(std::size_t rank);

        std::string GetCharacter() const;
        std::string GetName() const;
        std::size_t GetRank() const;

    private:
        std::string _character;
        std::string _name;
        std::size_t _rank;
};

typedef std::shared_ptr<Player> SharedPlayer;
typedef std::weak_ptr<Player>   WeakPlayer;


} // namespace MKTG

std::ostream &operator<<(std::ostream &flux, MKTG::Player &player);
