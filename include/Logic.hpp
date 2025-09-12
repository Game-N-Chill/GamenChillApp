
#pragma once

#include <iostream>

#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#include <OpenXLSX.hpp>
#pragma warning(pop)

namespace Generator::Logic
{

    #define CELL_TITLE      "C2"
    #define CELL_SUBTITLE   "D7"
    #define CELL_DATE       "I7"
    #define LINE_FIRST      15
    #define COL_CHARACTER   "H"
    #define COL_PLAYER      "I"

}
