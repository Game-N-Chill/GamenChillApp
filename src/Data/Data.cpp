
#include "Data/Data.hpp"

namespace GNCApp::Data
{

void loadData()
{
    DictBackground::getInstance()->load(&Background::load);
    DictCharacter::getInstance()->load(&Character::load);
    GNCApp::Data::Assets::getInstance();
    GNCApp::Data::Winner::getInstance();
}

} // namespace GNCApp::Data
