
#include "Data/Data.hpp"

namespace GNCApp::Data
{

void loadData()
{
    DictBackgroundMKWorld::getInstance()->load(&BackgroundMKWorld::load);
    DictBackgroundMK8::getInstance()->load(&BackgroundMK8::load);
    DictCharacter::getInstance()->load(&Character::load);
    GNCApp::Data::Assets::getInstance();
    GNCApp::Data::Winner::getInstance();
}

} // namespace GNCApp::Data
