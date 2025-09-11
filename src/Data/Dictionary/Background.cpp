
#include <sstream>

#include "Data/Dictionary/Background.hpp"
#include "Utils.hpp"

namespace Generator::Data
{

Background::Background()
{
    this->cup = DATA_BACKGROUND_DEFAULT_CUP;
    this->track = DATA_BACKGROUND_DEFAULT_TRACK;
    this->path = DATA_BACKGROUND_DEFAULT_PATH;
}

Background::Background(std::string pathCup, std::string pathTrack)
{
    this->cup = pathCup.substr(pathCup.find_last_of('\\') + 4);
    this->track = pathTrack.substr(pathCup.size() + 4, pathTrack.size() - (pathCup.size() + 4) - 4);
    this->path = pathTrack;
}

std::string Background::get() const
{
    return this->cup + '/' + this->track;
}

void Background::load(std::list<Background> &list)
{
    std::string path = Utils::getFullPath(PATH_BACKGROUND_DIR);

    for (const auto &entryCup : std::filesystem::recursive_directory_iterator(path)) {
        if (entryCup.is_directory()) {
            std::string pathCup = entryCup.path().string();
            for (const auto &entryTrack : std::filesystem::recursive_directory_iterator(pathCup)) {
                std::string pathTrack = entryTrack.path().string();
                list.push_back(Background(pathCup, pathTrack));
            }
        }
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

} // namespace Generator::Data

std::ostream &operator<<(std::ostream &flux, const Generator::Data::Background &background)
{
    flux << background.cup << "/" << background.track;
    return flux;
}
