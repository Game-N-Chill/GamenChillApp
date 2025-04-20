
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Print::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    std::cout << "====================[INFORMATION RENDU]====================" << std::endl << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Titre"         << gen.getTitle() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Sous-Titre"    << gen.getSubtitle() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Date"          << gen.getDate() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Participants"  << gen.getPlayerCount() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Lien Discord"  << gen.getDiscordUrl() << std::endl << std::endl;

    for (size_t i = 1 ; i <= 8; i++) {
        std::cout << std::left << "-- " << std::setw(20) << "Joueur " << *gen.getPlayerInfo(i) << std::endl;
    }
    std::cout << std::left << "-- " << std::setw(20) << "Fond" << gen.getDataTrack() << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(20) << "Dossier Sauvegarde" << gen.getImageDir() << std::endl;
    return Result::CONTINUE;
}

std::string Print::getCommand() const
{
    return COMMAND_PRINT;
}

} // namespace MKTG::Command
