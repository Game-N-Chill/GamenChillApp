
#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#include <OpenXLSX.hpp>
#pragma warning(pop)

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Utils.hpp"
#include "Commands/Handler.hpp"
#include "Commands/Interface.hpp"
#include "Generator/Generator.hpp"
#include "Render/Canva.hpp"


#define CELL_TITLE      "C2"
#define CELL_SUBTITLE   "D7"
#define CELL_DATE       "I7"
#define LINE_FIRST      15
#define COL_CHARACTER   "H"
#define COL_PLAYER      "I"

#define INDEX_TITLE                     "title"
#define INDEX_SUBTITLE                  "subtitle"
#define INDEX_DATE                      "date"
#define INDEX_COUNT                     "count"
#define INDEX_PLAYERS                   "players"
#define INDEX_TEAM                      "team"
#define INDEX_CHARACTER                 "character"
#define INDEX_NAME                      "name"

#define DEFAULT_TITLE                   "RIFIFI SUR LE CIRCUIT #"
#define DEFAULT_SUBTITLE                "Edition 150cc"
#define DEFAULT_DATE                    "01/01/2025"
#define DEFAULT_PLAYER_COUNT            16
#define DEFAULT_DISCORD_URL             "discord.gg/E5PFehpAkS"
#define DEFAULT_DATA_LINK               "Mario"
#define DEFAULT_IMAGE_DIR               "Result"

#define PATH_CHARACTERS_TRACKS_LINK     "Assets\\Data\\CharactersTracksLinks.json"
#define PATH_NAME_TAGS                  "Assets\\Data\\Tags.json"
#define PATH_HELP                       "Assets\\Data\\Help.txt"
#define IMAGE_WIDTH                     1920
#define IMAGE_HEIGHT                    1080

int doLogic();
std::vector<std::string> lineParser(std::string line);
