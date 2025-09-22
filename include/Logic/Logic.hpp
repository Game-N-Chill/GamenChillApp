
#pragma once

#include <iostream>
#include <array>
#include <map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Utils.hpp"
#include "Render.hpp"

namespace GNCApp::Logic
{

void createWinnerSoloImage();
void createWinnerDuoImage();

} // namespace MKTG
