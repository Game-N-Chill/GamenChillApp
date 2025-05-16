
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Print::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    if (args.size() < 2) {
        throw std::runtime_error("not enough arguments");
    }

    std::string team = Utils::stringToUpper(args[1]);

    std::cout << "====================[INFORMATION RENDU]====================" << std::endl << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Titre"         << gen.getTitle() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Sous-Titre"    << gen.getSubtitle() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Date"          << gen.getDate() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Participants"  << gen.getPlayerCount() << std::endl;
    std::cout << std::left << "-- " << std::setw(20) << "Lien Discord"  << gen.getDiscordUrl() << std::endl << std::endl;

    if (team == "SOLO") {
        gen.printSolo();
    } else if (team == "DUO") {
        gen.printDuo();
    } else {
        throw std::runtime_error("can't find team name: " + team);
    }

    std::cout << std::left << "-- " << std::setw(20) << "Fond" << gen.getBackgroundName() << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(20) << "Dossier Sauvegarde" << gen.getImageDir() << std::endl;
    return Result::CONTINUE;
}

std::string Print::getCommand() const
{
    return COMMAND_PRINT;
}

} // namespace MKTG::Command
