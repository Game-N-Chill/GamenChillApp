
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
        this->_players[i] = std::make_shared<Player>("Mario", "Player", i);
    }

    this->_imageDir = DEFAULT_IMAGE_DIR;
}


static std::string getTimeFormat(std::string format)
{
    std::time_t now = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now), format.c_str());
    return oss.str();
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

    OpenXLSX::XLCell cellTitle = sheet.cell(OpenXLSX::XLCellReference(CELL_TITLE));
    this->setTitle(cellTitle.value().get<std::string>());

    this->setDate(getTimeFormat("%d/%m/%Y"));

    size_t count = 0;
    for (int i = 0; i < 48; i++) {
        OpenXLSX::XLCell cellName = sheet.cell(OpenXLSX::XLCellReference(COL_PLAYER + std::to_string(LINE_FIRST + i)));
        std::string name = cellName.value().get<std::string>();

        if (name.empty()) {
            break;
        }

        if (i < 8) {
            this->setPlayerInfo(i + 1, sheet.cell(OpenXLSX::XLCellReference(COL_CHARACTER + std::to_string(LINE_FIRST + i))).value().get<std::string>(), name);
        }

        if (name != "-") {
            count++;
        }
    }
    this->setPlayerCount(count);

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



void Generator::setPlayerInfo(size_t rank, std::string character, std::string name)
{
    if (rank < 1 || rank > 8) {
        std::cerr << "ERROR: rank out of range: " << rank << ", must be: [1,8]" << std::endl;
        return;
    }

    SharedPlayer player = this->_players[rank - 1];
    if (player == nullptr) {
        std::cerr << "ERROR: can't find player of rank " << rank << std::endl;
        return;
    }

    player->SetRank(rank);
    player->SetCharacter(character);
    player->SetName(name);
}

SharedPlayer Generator::getPlayerInfo(size_t rank) const
{
    if (rank < 1 || rank > 8) {
        std::cerr << "ERROR: rank out of range: " << rank << ", must be: [1,8]" << std::endl;
        return nullptr;
    }
    return this->_players[rank - 1];
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
    std::string imagePath = this->_imageDir + '\\' + getTimeFormat("%Y_%m_%d__%H_%M_%S") + ".png";
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
