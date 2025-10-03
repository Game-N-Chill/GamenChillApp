
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

#include "Utils.hpp"
#include "Render.hpp"

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

void loadExcelFile(std::string path);
void createWinnerSoloImage();
void createWinnerDuoImage();

void createBracketFile();

} // namespace MKTG
