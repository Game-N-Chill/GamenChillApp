
#pragma once

#include <GoGuLib.hpp>

#include "Update.hpp"

#include "Shared/Logic/Generator.hpp"
#include "Shared/Logic/Render.hpp"
#include "Shared/Logic/ProgressTask.hpp"

#include "Shared/Data/Dictionary/Dictionary.hpp"
#include "Shared/Data/Dictionary/Background.hpp"
#include "Shared/Data/Dictionary/Character.hpp"
#include "Shared/Data/Assets.hpp"
#include "Shared/Data/Config.hpp"
#include "Shared/Data/Winner.hpp"
#include "Shared/Data/Seeding.hpp"

namespace GNCApp::Data
{

    void loadData();
    void unloadData();

} // namespace GNCApp::Data
