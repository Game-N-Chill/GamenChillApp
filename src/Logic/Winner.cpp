
#include "Logic/Logic.hpp"
#include "Data/Data.hpp"

#include <regex>

namespace GNCApp::Logic
{

static std::string getDateFromAmericanFormat(std::string date)
{
    std::regex pattern(REGEX_WEB_DATE);

    std::smatch matches;
    if (std::regex_match(date, matches, pattern)) {
        std::string year = matches[1];
        std::string mounth = matches[2];
        std::string day = matches[3];

        return day + '/' + mounth + '/' + year;
    } else {
        return date;
    }
}

static void getRealRank(int &rank, bool &firstTime)
{
    if (!firstTime) {
        firstTime = true;
    } else {
        rank++;
    }
}

void loadWebFile(std::string apiKey, std::string tournamentID)
{
    if (apiKey.empty())
        return;
    if (apiKey.size() != 40)
        return;
    if (tournamentID.empty())
        return;

    Data::Winner *dataWinner = Data::Winner::getInstance();
    // https://api.challonge.com/v1/tournaments/rififitest.json?api_key=p4JQGpIhptA3whwueKIFUicDejSf4e55ZMN1Pt6I&state=all&include_participants=1
    std::string url = "https://api.challonge.com/v1/tournaments/" + tournamentID + ".json?api_key=" + apiKey + "&state=all&include_participants=1";
    std::string pathTemp = Utils::getTempDir() + '/' + GNCAPP_TEMP_DIR + "/challonge.json";
    Utils::Request req;
    json data;

    req.ResetOpt();
    req.SetOpt(CURLOPT_SSL_VERIFYPEER, 1L);
    req.SetOpt(CURLOPT_SSL_VERIFYHOST, 2L);
    req.SetOpt(CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    req.SetOpt(CURLOPT_USERAGENT, "curl/8.0");

    try {
        std::string str = req.Get(url);
        data = json::parse(str);
        data = data["tournament"];
    } catch (std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return;
    } catch (json::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return;
    }
    std::cout << "SUCCESS: data fully downloaded" << std::endl;

    std::string title = data["name"];
    dataWinner->setTitle(title);

    std::string subtitle = data["description"];
    dataWinner->setSubtitle(subtitle);

    std::string date = getDateFromAmericanFormat(std::string(data["started_at"]).substr(0, 10));
    dataWinner->setDate(date);

    int count = data["participants_count"];
    dataWinner->setPlayerCount(count * 2);

    std::string game = data["game_name"];
    if (game == "Mario Kart World") {
        dataWinner->setGame(0);
    } else {
        dataWinner->setGame(1);
    }

    bool doublonFifth = false;
    bool doublonSeventh = false;
    std::regex pattern(REGEX_WEB_TEAM_NAME);
    for (auto &it : data["participants"]) {
        json participant = it["participant"];
        std::string name = participant["name"];
        int rank = participant["final_rank"];

        if (rank >= 1 && rank <= 8) {
            if (rank == 5)
                getRealRank(rank, doublonFifth);
            if (rank == 7)
                getRealRank(rank, doublonSeventh);

            std::smatch matches;
            if (std::regex_match(name, matches, pattern)) {
                std::string team = matches[1];
                std::string player01 = matches[2];
                std::string player02 = matches[3];

                GNCApp::Data::Winner::Duo &duo = dataWinner->getTeamDuo(rank - 1);

                duo.setName(team);
                duo[0].setName(player01);
                duo[1].setName(player02);
            } else {
                std::cerr << "WARNING: can't match regex for " << name << std::endl;
            }
        }
    }
}

void loadExcelFile(std::string path)
{
    if (path.empty()) {
        std::cerr << "ERROR: path empty" << std::endl;
        return;
    }

    OpenXLSX::XLDocument file;
    file.open(path);
    if (!file.isOpen()) {
        std::cerr << "ERROR: file at " << path << " can't be open" << std::endl;
        return;
    }


    Data::Winner *dataWinner = Data::Winner::getInstance();
    std::string sheetName = file.workbook().worksheetNames()[0];
    OpenXLSX::XLWorksheet sheet = file.workbook().worksheet(sheetName);

    try {
        OpenXLSX::XLCell cellTitle = sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_TITLE));
        dataWinner->setTitle(cellTitle.value().get<std::string>());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: title format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        OpenXLSX::XLCell cellSubTitle = sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_SUBTITLE));
        dataWinner->setSubtitle(cellSubTitle.value().get<std::string>());
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: subtitle format is incorrect (" << e.what() << ")" << std::endl;
    }

    try {
        OpenXLSX::XLCell cellDate = sheet.cell(OpenXLSX::XLCellReference(EXCEL_CELL_DATE));
        std::string date = cellDate.value().get<std::string>();
        if (date.empty()) {
            dataWinner->setDate(Utils::getTimeFormat("%d/%m/%Y"));
        } else {
            dataWinner->setDate(date);
        }
    } catch (const OpenXLSX::XLValueTypeError &e) {
        std::cerr << "WARNING: date format is incorrect (" << e.what() << ")" << std::endl;
    }

    size_t count = 0;
    for (int i = 0; i < 48; i++) {
        OpenXLSX::XLCell cellName = sheet.cell(OpenXLSX::XLCellReference(EXCEL_COL_PLAYER + std::to_string(EXCEL_LINE_FIRST + i)));
        std::string name = cellName.value().get<std::string>();

        if (name.empty()) {
            break;
        }

        // register top 8
        if (i < 8) {
            GNCApp::Data::Winner::Solo &solo = dataWinner->getTeamSolo(i);

            std::string character = sheet.cell(OpenXLSX::XLCellReference(EXCEL_COL_CHARACTER + std::to_string(EXCEL_LINE_FIRST + i))).value().get<std::string>();
            solo[0].setName(name);
            solo[0].setCharacter(character);
            solo[0].randomizeSkin();
        }

        if (name != "-") {
            count++;
        }
    }
    dataWinner->setPlayerCount(count);

    file.close();
}


template<size_t N>
static void createWinnerShared(std::string path, const std::array<Data::Winner::Team<N>, PLAYER_GRAPH_COUNT> &array)
{
    if (path.empty()) {
        RESET_PROGRESS_TASK;
        std::cerr << "can't open file: " << path << std::endl;
        return;
    }

    Canva canva(path);
    Data::Winner *dataWinner = Data::Winner::getInstance();

    canva.getImage("background").image.load(dataWinner->getBackground().path.c_str());
    canva.getText("title").str = dataWinner->getTitle().c_str();
    canva.getText("subtitle").str = dataWinner->getSubtitle().c_str();
    canva.getText("date").str = (dataWinner->getDate()).c_str();
    canva.getText("playerCount").str = (std::to_string(dataWinner->getPlayerCount()) + " Participants").c_str();

    for (size_t i = 0; i < array.size(); i++) {
        Data::Winner::Team<N> team = array[i];

        if (N > 1) {
            canva.getText(std::to_string(i + 1) + '_' + "Team").str = team.getName().c_str();
        }

        std::string name;
        for (size_t j = 0; j < N; j++) {
            canva.getImage(std::to_string(i + 1) + '_' + std::to_string(j + 1) + '_' + "Character").image.load((team.getPlayer(j).getCharacter().path + '/' + team.getPlayer(j).getSkin() + ".png").c_str());
            name += team.getPlayer(j).getName();
            if (j < N - 1) {
                name += " - ";
            }
        }
        canva.getText(std::to_string(i + 1) + '_' + "Name").str = name.c_str();
    }
    DO_PROGRESS_TASK;

    canva.draw();
    DO_PROGRESS_TASK;
    canva.save(dataWinner->getOutputDir(), Utils::getTimeFormat("%Y_%m_%d__%H_%M_%S"));
    DO_PROGRESS_TASK;
}

static std::string getCanvaPath(std::string pathFile)
{
    std::vector<std::string> map = {
        "MKWorld",
        "MK8"
    };

    return CANVA_PATH + map[Data::Winner::getInstance()->getGame()] + '/' + pathFile;
}

void createWinnerSoloImage()
{
    createWinnerShared(getCanvaPath(CANVA_SOLO_PATH), Data::Winner::getInstance()->getSolo());
}

void createWinnerDuoImage()
{
    createWinnerShared(getCanvaPath(CANVA_DUO_PATH), Data::Winner::getInstance()->getDuo());
}

}
