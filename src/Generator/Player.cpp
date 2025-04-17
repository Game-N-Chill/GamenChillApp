
#include "MKTG.hpp"

namespace MKTG
{

Player::Player()
{
    this->_character = "";
    this->_name = "";
    this->_rank = 0;
}

Player::Player(std::string character, std::string name, std::size_t rank)
{
    this->_character = character;
    this->_name = name;
    this->_rank = rank;
}

void Player::SetCharacter(std::string character)
{
    this->_character = character;
}

void Player::SetName(std::string name)
{
    this->_name = name;
}

void Player::SetRank(std::size_t rank)
{
    this->_rank = rank;
}

std::string Player::GetCharacter() const
{
    return this->_character;
}

std::string Player::GetName() const
{
    return this->_name;
}

std::size_t Player::GetRank() const
{
    return this->_rank;
}

} // namespace MKTG

std::ostream &operator<<(std::ostream &flux, MKTG::Player &player)
{
    flux << std::left << '#' << std::setw(3) << player.GetRank() << std::setw(22) << player.GetCharacter() << player.GetName();
    return flux;
}
