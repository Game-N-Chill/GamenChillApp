
#include <sstream>

#include "Data/Dictionary/Background.hpp"
#include "Utils.hpp"

namespace GNCApp::Data
{

Background::Background()
{
    this->game = DATA_BACKGROUND_DEFAULT_GAME;
    this->cup = DATA_BACKGROUND_DEFAULT_CUP;
    this->track = DATA_BACKGROUND_DEFAULT_TRACK;
    this->path = DATA_BACKGROUND_DEFAULT_PATH;
}

Background::Background(std::string path)
{
    std::replace(path.begin(), path.end(), '\\', '/');
    this->path = path;
    this->track = path.substr(path.find_last_of('/') + 4);
    this->track.erase(this->track.size() - 4, this->track.size());
    path = path.substr(0, path.find_last_of('/'));
    this->cup = path.substr(path.find_last_of('/') + 4);
    path = path.substr(0, path.find_last_of('/'));
    this->game = path.substr(path.find_last_of('/') + 1);
}

std::string Background::get() const
{
    return this->game + '/' + this->cup + '/' + this->track;
}

void Background::load(std::list<Background> &list)
{
    for (const auto &entryCup : std::filesystem::recursive_directory_iterator(PATH_BACKGROUND_DIR)) {
        if (entryCup.is_directory()) {
            continue;
        }
        list.push_back(Background(entryCup.path().string()));
    }
}

bool Background::operator==(std::string key)
{
    if (key == track)
        return true;
    if (key == cup + '/' + track)
        return true;
    return false;
}

Background::operator std::string() const
{
    std::ostringstream oss;
    oss << this->get();
    return oss.str();
}

} // namespace GNCApp::Data

std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Background &background)
{
    flux << background.game << "/" << background.cup << "/" << background.track;
    return flux;
}
