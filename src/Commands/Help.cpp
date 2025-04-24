
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Help::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    std::cout << "====================[LISTE DES COMMANDES]====================" << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(10) << "help"     << std::setw(50) << ""                                             << "Affiche ce message"                                  << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "quit"     << std::setw(50) << ""                                             << "Quitte le programme"                                 << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(10) << "title"    << std::setw(50) << "<str>"                                        << "Change le titre"                                     << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "subtitle" << std::setw(50) << "<str>"                                        << "Change le sous-titre"                                << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "date"     << std::setw(50) << "<str>"                                        << "Change la date (format XX/XX/XXXX)"                  << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "count"    << std::setw(50) << "<value>"                                      << "Change le nombre de participants"                    << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "url"      << std::setw(50) << "<str>"                                        << "Change le lien d'invitation discord"                 << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(10) << "load"     << std::setw(50) << "<path/to/file>"                               << "Charge le fichier excel du bracket"                  << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "player"   << std::setw(50) << "[solo/duo] <rank> <index> <character> <name>" << "Change les informations d'un joueur"                 << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "random"   << std::setw(50) << ""                                             << "Change le fond du rendu"                             << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "print"    << std::setw(50) << "[solo/duo]"                                   << "Affiche toutes les informations concernant le rendu" << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(10) << "dir"      << std::setw(50) << "<path/to/dir>"                                << "Change le dossier où les rendus seront créés"        << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "create"   << std::setw(50) << "[solo/duo]"                                   << "Créer le rendu"                                      << std::endl;

    return Result::CONTINUE;
}

std::string Help::getCommand() const
{
    return COMMAND_HELP;
}

} // namespace MKTG::Command
