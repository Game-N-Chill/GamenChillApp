
#include "Data/Data.hpp"

namespace Generator::Data
{

void loadData()
{
    DictBackground::getInstance()->load(&Background::load);
    DictCharacter::getInstance()->load(&Character::load);
    Generator::Data::Winner::getInstance();
}

} // namespace Generator::Data
