
#include "Data/Seeding.hpp"

namespace GNCApp::Data
{

Seeding::Player::Player()
{
    this->_name = "";
    this->_seeding = 0.0f;
}

Seeding::Player::Player(std::string name, float seeding)
{
    this->_name = name;
    this->_seeding = seeding;
}


std::string Seeding::Player::getName() const
{
    return this->_name;
}

void Seeding::Player::setName(std::string name)
{
    this->_name = name;
}


float Seeding::Player::getSeeding() const
{
    return this->_seeding;
}

void Seeding::Player::setSeeding(float value)
{
    this->_seeding = value;
}

bool Seeding::Player::operator==(const Seeding::Player &other) const
{
    return (this->_name == other._name);
}

bool Seeding::Player::operator==(const std::string &name) const
{
    return (this->_name == name);
}

bool Seeding::Player::operator!=(const Seeding::Player &other) const
{
    return !(*this == other);
}

bool Seeding::Player::operator!=(const std::string &name) const
{
    return !(*this == name);
}

bool Seeding::Player::operator>(const Seeding::Player &other) const
{
    return (this->getSeeding() > other.getSeeding());
}

bool Seeding::Player::operator<(const Seeding::Player &other) const
{
    return (this->getSeeding() < other.getSeeding());
}

}
