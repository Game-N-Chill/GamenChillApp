
#include "Shared/Data/Winner.hpp"
#include "Shared/Data/Dictionary/Dictionary.hpp"


namespace GNCApp::Data
{

Winner::Winner()
{
    this->_title = DATA_WINNER_DEFAULT_TITLE;
    this->_subtitle = DATA_WINNER_DEFAULT_SUBTITLE;
    this->_date =  GGL::getTimeFormat("%d/%m/%Y");
    this->_playerCount = DATA_WINNER_DEFAULT_PLAYER_COUNT;
    this->_outputDir =  GGL::getFullPath(DATA_WINNER_DEFAULT_OUTPUT_DIR);
    this->_background = Background();
    this->_game = DATA_WINNER_GAME_MKWORLD;

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

std::array<Winner::Solo, PLAYER_GRAPH_COUNT> &Winner::getSolo()
{
    return this->_solo;
}

Winner::Solo &Winner::getTeamSolo(size_t index)
{
    return this->_solo[index];
}

std::array<Winner::Duo, PLAYER_GRAPH_COUNT> &Winner::getDuo()
{
    return this->_duo;
}

Winner::Duo &Winner::getTeamDuo(size_t index)
{
    return this->_duo[index];
}

int Winner::getGame() const
{
    return this->_game;
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

void Winner::setGame(int game)
{
    this->_game = game;
}


void Winner::print(std::ostream &flux) const
{
    flux << "Title: " << this->_title << GGL::end;
    flux << "SubTitle: " << this->_subtitle << GGL::end;
    flux << "Date: " << this->_date << GGL::end;
    flux << "PlayerCount: " << this->_playerCount << GGL::end;
    flux << "Output Directory: " << this->_outputDir << GGL::end;
    flux << "Background: " << this->_background << GGL::end;

    for (size_t i = 0; i < this->_solo.size(); i++) {
        flux << "Team " << (i + 1) << GGL::end;
        flux << this->_solo[i] << GGL::end;
        flux << GGL::end;
    }
    flux << GGL::end;
    for (size_t i = 0; i < this->_duo.size(); i++) {
        flux << "Team " << (i + 1) << GGL::end;
        flux << this->_duo[i] << GGL::end;
        flux << GGL::end;
    }
}

} // namespace Winner::Data


std::ostream &operator<<(std::ostream &flux, const GNCApp::Data::Winner &winner)
{
    winner.print();
    return flux;
}
