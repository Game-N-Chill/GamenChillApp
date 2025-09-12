
#pragma once

#include <iostream>
#include <array>
#include <map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Utils.hpp"
#include "Data/Data.hpp"
#include "Render/Canva.hpp"

namespace Generator::Logic
{

void createWinnerSoloImage();
void createWinnerDuoImage();

} // namespace MKTG
