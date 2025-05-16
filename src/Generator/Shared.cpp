
#include "MKTG.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace MKTG
{

//  INITIALIZATION
// *****************************************************************************

static void loadBackgrounds(std::map<std::string, std::string> &backgrounds)
{
    std::string path = Utils::getFullPath(PATH_BACKGROUND_DIR);

    for (const auto &entryCup : std::filesystem::recursive_directory_iterator(path)) {
        if (entryCup.is_directory()) {
            std::string pathCup = entryCup.path().string();

            for (const auto &entryTrack : std::filesystem::recursive_directory_iterator(pathCup)) {
                std::string pathTrack = entryTrack.path().string();
                std::string nameTrack = pathTrack.substr(pathCup.size() + 4, pathTrack.size() - (pathCup.size() + 4) - 4);
                backgrounds[nameTrack] = pathTrack;
            }
        }
    }
}

Generator::Generator(std::string excelPath)
{
    this->_title = DEFAULT_TITLE;
    this->_subtitle = DEFAULT_SUBTITLE;
    this->_date = DEFAULT_DATE;
    this->_playerCount = DEFAULT_PLAYER_COUNT;
    this->_discordUrl = DEFAULT_DISCORD_URL;

    // std::ifstream file(PATH_CHARACTERS_TRACKS_LINK);
    // file >> this->_dataLinks;
    // file.close();
    // setDataLink(DEFAULT_DATA_LINK);

    loadBackgrounds(this->_backgrounds);
    setBackground();

    this->_imageDir = DEFAULT_IMAGE_DIR;

    for (int i = 0; i < PLAYER_GRAPH_COUNT; i++) {
        this->_solo[i] = std::make_shared<Team<1>>(i + 1);
        this->_duo[i] = std::make_shared<Team<2>>(i + 1);
    }

    std::ifstream file(Utils::getFullPath(PATH_NAME_TAGS));
    file >> this->_tags;
    file.close();
}

//  SHARED GETTER/SETTER
// *****************************************************************************

std::string Generator::getTitle() const
{
    return this->_title;
}

std::string Generator::getSubtitle() const
{
    return this->_subtitle;
}

std::string Generator::getDate() const
{
    return this->_date;
}

size_t Generator::getPlayerCount() const
{
    return this->_playerCount;
}

std::string Generator::getDiscordUrl() const
{
    return this->_discordUrl;
}


void Generator::setTitle(std::string str)
{
    this->_title = str;
}

void Generator::setSubtitle(std::string str)
{
    this->_subtitle = str;
}

void Generator::setDate(std::string str)
{
    this->_date = str;
}

void Generator::setPlayerCount(size_t value)
{
    this->_playerCount = value;
}

void Generator::setDiscordUrl(std::string str)
{
    this->_discordUrl = str;
}

//  Data Link
// *****************************************************************************

// void Generator::setDataLink(std::string characterStr)
// {
//     json character;
//     try {
//         character = this->_dataLinks.at(characterStr);
//     } catch (const json::type_error &e) {
//         std::cerr << e.what() << std::endl;
//         return;
//     } catch (const json::out_of_range &e) {
//         std::cerr << e.what() << std::endl;
//         return;
//     }

//     this->_dataCharacter = characterStr;
//     this->_dataTracks = character.get<std::vector<std::string>>();
//     size_t index = Utils::getRandom(this->_dataTracks.size());
//     this->_dataTrackIt = this->_dataTracks.begin();
//     std::advance(this->_dataTrackIt, index);
// }

// void Generator::nextDataTrack()
// {
//     this->_dataTrackIt++;
//     if (this->_dataTrackIt == this->_dataTracks.end()) {
//         this->_dataTrackIt = this->_dataTracks.begin();
//     }
// }

// void Generator::prevDataTrack()
// {
//     if (this->_dataTrackIt == this->_dataTracks.begin()) {
//         this->_dataTrackIt = this->_dataTracks.end();
//     }
//     this->_dataTrackIt--;
// }

// std::string Generator::getDataCharacter() const
// {
//     return this->_dataCharacter;
// }

// std::string Generator::getDataTrack() const
// {
//     return *this->_dataTrackIt;
// }

std::string Generator::getBackgroundName() const
{
    return this->_backgroundIt->first;
}

std::string Generator::getBackgroundPath() const
{
    return this->_backgroundIt->second;
}

void Generator::setBackground()
{
    Utils::Randomizer rand;
    this->_backgroundIt = this->_backgrounds.begin();
    std::advance(this->_backgroundIt, rand.GetRandom(this->_backgrounds.size()));
}

void Generator::setBackground(std::string name)
{
    auto it = this->_backgrounds.find(name);
    if (it != this->_backgrounds.end()) {
        this->_backgroundIt = it;
    } else {
        throw std::out_of_range("can't find background " + name);
    }
}


//  Image DIR
// *****************************************************************************

void Generator::setImageDir(std::string path)
{
    this->_imageDir = path;
}

std::string Generator::getImageDir() const
{
    return this->_imageDir;
}

} // namespace MKTG
