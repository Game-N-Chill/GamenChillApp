
#include "Data/Data.hpp"

namespace GNCApp::Data
{

void loadData()
{
    DictBackgroundMKWorld::getInstance()->load(&BackgroundMKWorld::load);
    DictBackgroundMK8::getInstance()->load(&BackgroundMK8::load);
    DictCharacter::getInstance()->load(&Character::load);
    GNCApp::Data::Assets::getInstance();
    GNCApp::Data::Config::getInstance();
    GNCApp::Data::Winner::getInstance();
    GNCApp::Data::Seeding::getInstance();
}

void unloadData()
{
    DictBackgroundMKWorld::destroyInstance();
    DictBackgroundMK8::destroyInstance();
    DictCharacter::destroyInstance();
    GNCApp::Data::Assets::destroyInstance();
    GNCApp::Data::Config::destroyInstance();
    GNCApp::Data::Winner::destroyInstance();
    GNCApp::Data::Seeding::destroyInstance();
}

} // namespace GNCApp::Data
