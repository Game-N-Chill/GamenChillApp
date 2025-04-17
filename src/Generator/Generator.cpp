
#include "MKTG.hpp"
#include <ctime>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
namespace MKTG
{

Generator::Generator(std::string excelPath)
{
    this->_title = DEFAULT_TITLE;
    this->_subtitle = DEFAULT_SUBTITLE;
    this->_date = DEFAULT_DATE;
    this->_playerCount = DEFAULT_PLAYER_COUNT;
    this->_discordUrl = DEFAULT_DISCORD_URL;

    std::ifstream file(PATH_CHARACTERS_TRACKS_LINK);
    file >> this->_dataLinks;
    file.close();
    setDataLink(DEFAULT_DATA_LINK);

    for (int i = 0; i < this->_players.size(); i++) {
        this->_players[i] = std::make_shared<Player>();
    }

    this->_imageDir = DEFAULT_IMAGE_DIR;
}



void Generator::Load(std::string excelPath)
{
    if (excelPath.empty()) {
        return;
    }

    OpenXLSX::XLDocument file;
    file.open(excelPath);
    if (!file.isOpen()) {
        std::cerr << "ERROR: file " << excelPath << "can't be open" << std::endl;
        return;
    }

    auto sheetNames = file.workbook().worksheetNames();
    auto sheet = file.workbook().worksheet(sheetNames[0]);

    for (int i = 0; i < this->_players.size(); i++) {
        OpenXLSX::XLCell cellCharacter = sheet.cell(OpenXLSX::XLCellReference(COL_CHARACTER + std::to_string(LINE_FIRST + i)));
        OpenXLSX::XLCell cellName = sheet.cell(OpenXLSX::XLCellReference(COL_PLAYER + std::to_string(LINE_FIRST + i)));

        this->_players[i]->SetCharacter(cellCharacter.value().get<std::string>());
        this->_players[i]->SetName(cellName.value().get<std::string>());
        this->_players[i]->SetRank(i + 1);
    }

    file.close();
}



void Generator::setDataLink(std::string characterStr)
{
    json character;
    try {
        character = this->_dataLinks.at(characterStr);
    } catch (const json::type_error &e) {
        std::cerr << e.what() << std::endl;
        return;
    } catch (const json::out_of_range &e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    this->_dataCharacter = characterStr;
    this->_dataTracks = character.get<std::vector<std::string>>();
    size_t index = Utils::getRandom(this->_dataTracks.size());
    this->_dataTrackIt = this->_dataTracks.begin();
    std::advance(this->_dataTrackIt, index);
}

void Generator::nextDataLink()
{
    this->_dataTrackIt++;
    if (this->_dataTrackIt == this->_dataTracks.end()) {
        this->_dataTrackIt = this->_dataTracks.begin();
    }
}

void Generator::prevDataLink()
{
    if (this->_dataTrackIt == this->_dataTracks.begin()) {
        this->_dataTrackIt = this->_dataTracks.end();
    }
    this->_dataTrackIt--;
}

std::string Generator::getDataCharacter() const
{
    return this->_dataCharacter;
}

std::string Generator::getDataTrack() const
{
    return *this->_dataTrackIt;
}



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


void Generator::getTitle(std::string str)
{
    this->_title = str;
}

void Generator::getSubtitle(std::string str)
{
    this->_subtitle = str;
}

void Generator::getDate(std::string str)
{
    this->_date = str;
}

void Generator::getPlayerCount(size_t value)
{
    this->_playerCount = value;
}

void Generator::getDiscordUrl(std::string str)
{
    this->_discordUrl = str;
}



std::string getLocalTime()
{
    std::time_t now = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now), "%Y_%m_%d__%H_%M_%S");
    return oss.str();
}

void Generator::createImage()
{
    float scaleBg = 1.5f;
    std::string pathBg = "Assets\\Images\\Background\\" + *this->_dataTrackIt + ".png";
    SDL_Surface *imgBg = IMG_Load(pathBg.c_str());
    if (imgBg == nullptr) {
        std::cerr << "imgBg is nullptr" << std::endl;
        return;
    }

    SDL_Surface* surface = SDL_CreateSurface(IMAGE_WIDTH, IMAGE_HEIGHT, SDL_PIXELFORMAT_RGBA32);
    if (surface == nullptr) {
        std::cerr << "surface is nullptr" << std::endl;
        return;
    }

    SDL_Rect dst1 = {0, 0, static_cast<int>(imgBg->w * scaleBg), static_cast<int>(imgBg->h * scaleBg)};
    SDL_BlitSurfaceScaled(imgBg, nullptr, surface, &dst1, SDL_SCALEMODE_LINEAR);

    if (!fs::is_directory(this->_imageDir)) {
        fs::create_directory(this->_imageDir);
    }
    std::string imagePath = this->_imageDir + '\\' + getLocalTime() + ".png";
    std::cout << imagePath << std::endl;
    IMG_SavePNG(surface, imagePath.c_str());

    SDL_DestroySurface(imgBg);
    SDL_DestroySurface(surface);
}

void Generator::setImageDir(std::string path)
{
    this->_imageDir = path;
}

std::string Generator::getImageDir() const
{
    return this->_imageDir;
}



} // namespace MKTG
