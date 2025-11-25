
#pragma once

#include <iostream>
#include <array>
#include <map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#include <OpenXLSX.hpp>
#pragma warning(pop)

namespace GNCApp::Logic
{
    #define EXCEL_FILE_PATH         "template/rififi_bracket_solo_"
    #define EXCEL_FILE_EXT          ".xlsx"
    #define EXCEL_CELL_SEEDING      "D"
    #define EXCEL_CELL_PRESENCE     "E"

    #define EXCEL_CELL_TITLE        "C2"
    #define EXCEL_CELL_SUBTITLE     "D7"
    #define EXCEL_CELL_DATE         "I7"
    #define EXCEL_LINE_FIRST        15
    #define EXCEL_COL_CHARACTER     "H"
    #define EXCEL_COL_PLAYER        "I"

    //                        ID du fichier : 1YT3Pv215gro_RCfn1742ASNJUSMfRhww
    // https://docs.google.com/spreadsheets/d/1J8oynJao4IbXSkCAJ5WUfhDWekhAy69k/edit?usp=sharing&ouid=117609227211333661518&rtpof=true&sd=true
    #define SEEDING_URL             "https://drive.google.com/uc?export=download&id=1J8oynJao4IbXSkCAJ5WUfhDWekhAy69k"
    #define SEEDING_FILE_NAME       "seeding.xlsx"
    #define SEEDING_WORKSHEET       "Seeding"

    /*
        ^ – Start of the string.
        (.+?) – Captures the team name (lazy match to stop at the first ().
        \s* – Optional whitespace.
        \( – Literal opening parenthesis.
        \s* – Optional whitespace.
        (.+?) – Captures Player01.
        \s*-\s* – Hyphen surrounded by optional whitespace.
        (.+?) – Captures Player02.
        \s*\) – Optional whitespace and closing parenthesis.
        $ – End of string.
    */
    #define REGEX_WEB_DATE          "^(\\d{4})-(\\d{2})-(\\d{2})$"
    #define REGEX_WEB_TEAM_NAME     "^(.+?)\\s*\\(\\s*(.+?)\\s*-\\s*(.+?)\\s*\\)$"

void loadWebFile(std::string url);
void loadWebFile(std::string apiKey, std::string tournamentID);
void loadExcelFile(std::string path);
void createWinnerSoloImage();
void createWinnerDuoImage();

std::vector<std::string> loadPlayerFile(std::string path);
void fetchSeeding();
void createBracketFile();

} // namespace MKTG
