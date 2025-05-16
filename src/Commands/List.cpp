
#include "MKTG.hpp"

namespace MKTG::Command
{

static std::vector<std::string> getBackgrounds()
{
    std::vector<std::string> vec;
    std::string path = Utils::getFullPath(PATH_BACKGROUND_DIR);

    for (const auto &entryCup : std::filesystem::recursive_directory_iterator(path)) {
        if (entryCup.is_directory()) {
            std::string pathCup = entryCup.path().string();

            for (const auto &entryTrack : std::filesystem::recursive_directory_iterator(pathCup)) {
                std::string pathTrack = entryTrack.path().string();
                std::string nameTrack = pathTrack.substr(pathCup.size() + 4, pathTrack.size() - (pathCup.size() + 4) - 4);
                vec.push_back(nameTrack);
            }
        }
    }
    return vec;
}

static std::vector<std::string> getCharacters()
{
    std::vector<std::string> vec;
    std::string path = Utils::getFullPath(PATH_CHARACTERS_DIR);

    for (const auto &entry : std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_directory()) {
            std::string pathCharacter = entry.path().string();
            std::string nameCharacter = pathCharacter.substr(path.size());
            vec.push_back(nameCharacter);
        }
    }
    return vec;
}

Result List::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    auto vecBg = getBackgrounds();
    auto vecCh = getCharacters();
    size_t maxSize = std::max(vecBg.size(), vecCh.size());

    std::cout << std::left << std::setw(20) << "Characters" << "| Backgrounds" << std::endl;
    for (size_t i = 0; i < 40; i++)
        std::cout << '-';
    std::cout << std::endl;


    for (size_t i = 0; i < maxSize; i++) {
        std::string background;
        std::string character;

        if (i < vecBg.size())
            background = vecBg[i];
        if (i < vecCh.size())
            character = vecCh[i];
            std::cout << std::left << std::setw(20) << character << "| "<< background << std::endl;
    }

    return Result::CONTINUE;
}

std::string List::getCommand() const
{
    return COMMAND_LIST;
}

} // namespace MKTG::Command
