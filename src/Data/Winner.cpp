
#include "Data/Winner.hpp"
#include "Data/Dictionary/Dictionary.hpp"
#include "Utils.hpp"

namespace GNCApp::Data
{

Winner::Winner()
{
    this->_title = DATA_WINNER_DEFAULT_TITLE;
    this->_subtitle = DATA_WINNER_DEFAULT_SUBTITLE;
    this->_date = Utils::getTimeFormat("%d/%m/%Y");
    this->_playerCount = DATA_WINNER_DEFAULT_PLAYER_COUNT;
    this->_outputDir = Utils::getFullPath(DATA_WINNER_DEFAULT_OUTPUT_DIR);
    this->_background = Background();

    for (int i = 0; i < PLAYER_GRAPH_COUNT; i++) {
        this->_solo[i] = Solo();
        this->_duo[i] = Duo();
    }
}

std::string Winner::getTitle() const
{
    return this->_title;
}

std::string Winner::getSubtitle() const
{
    return this->_subtitle;
}

std::string Winner::getDate() const
{
    return this->_date;
}

size_t Winner::getPlayerCount() const
{
    return this->_playerCount;
}

std::string Winner::getOutputDir() const
{
    return this->_outputDir;
}

Background Winner::getBackground() const
{
    return this->_background;
}

std::array<Solo, PLAYER_GRAPH_COUNT> &Winner::getSolo()
{
    return this->_solo;
}

Solo &Winner::getTeamSolo(size_t index)
{
    return this->_solo[index];
}

std::array<Duo, PLAYER_GRAPH_COUNT> &Winner::getDuo()
{
    return this->_duo;
}

Duo &Winner::getTeamDuo(size_t index)
{
    return this->_duo[index];
}


void Winner::setTitle(std::string str)
{
    this->_title = str;
}

void Winner::setSubtitle(std::string str)
{
    this->_subtitle = str;
}

void Winner::setDate(std::string str)
{
    this->_date = str;
}

void Winner::setPlayerCount(size_t value)
{
    this->_playerCount = value;
}

void Winner::setOutputDir(std::string str)
{
    this->_outputDir = str;
}

void Winner::setBackground(size_t index)
{
    try {
        this->_background = Data::DictBackground::getInstance()->find(index);
    } catch (std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Winner::setBackground(std::string str)
{
    try {
        this->_background = Data::DictBackground::getInstance()->find(str);
    } catch (std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
    }
}



void Winner::randomizeBackground()
{
    Utils::Randomizer rand;
    size_t index = rand.GetRandom(Data::DictBackground::getInstance()->size());
    setBackground(index);
}


void Winner::print(std::ostream &flux) const
{
    flux << "Title: " << this->_title << std::endl;
    flux << "SubTitle: " << this->_subtitle << std::endl;
    flux << "Date: " << this->_date << std::endl;
    flux << "PlayerCount: " << this->_playerCount << std::endl;
    flux << "Output Directory: " << this->_outputDir << std::endl;
    flux << "Background: " << this->_background << std::endl;

    for (size_t i = 0; i < this->_solo.size(); i++) {
        flux << "Team " << (i + 1) << std::endl;
        flux << this->_solo[i] << std::endl;
        flux << std::endl;
    }
    flux << std::endl;
    for (size_t i = 0; i < this->_duo.size(); i++) {
        flux << "Team " << (i + 1) << std::endl;
        flux << this->_duo[i] << std::endl;
        flux << std::endl;
    }
}

} // namespace Winner::Data


std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Winner &winner)
{
    winner.print();
    return flux;
}
