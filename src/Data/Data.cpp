
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
    GNCApp::Data::Seeding::getInstance();

    GNCApp::Data::Seeding::getInstance()->addPlayer("Groluche");
    GNCApp::Data::Seeding::getInstance()->addPlayer("Batefimbi");
    GNCApp::Data::Seeding::getInstance()->addPlayer("GoGu");
    GNCApp::Data::Seeding::getInstance()->addPlayer("Supnyus");
    GNCApp::Data::Seeding::getInstance()->addPlayer("SewLink");
}

} // namespace GNCApp::Data
