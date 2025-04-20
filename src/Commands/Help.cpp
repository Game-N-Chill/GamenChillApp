
#include "MKTG.hpp"

namespace MKTG::Command
{

Result Help::run(MKTG::Generator &gen, std::vector<std::string> &args)
{
    std::cout << "====================[LISTE DES COMMANDES]====================" << std::endl << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "help"     << std::setw(30) << ""                          << "Affiche ce message" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "quit"     << std::setw(30) << ""                          << "Quitte le programme" << std::endl << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "title"    << std::setw(30) << "<str>"                     << "Change le titre" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "subtitle" << std::setw(30) << "<str>"                     << "Change le sous-titre" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "date"     << std::setw(30) << "<str>"                     << "Change la date (format XX/XX/XXXX)" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "count"    << std::setw(30) << "<value>"                   << "Change le nombre de participants" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "url"      << std::setw(30) << "<str>"                     << "Change le lien d'invitation discord" << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(10) << "load"     << std::setw(30) << "<path>"                    << "Charge le fichier excel du bracket" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "player"   << std::setw(30) << "<rank> <character> <name>" << "Change les informations d'un joueur" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "random"   << std::setw(30) << ""                          << "Change le fond du rendu" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "print"    << std::setw(30) << ""                          << "Affiche toutes les informations concernant le rendu" << std::endl << std::endl;

    std::cout << std::left << "-- " << std::setw(10) << "dir"      << std::setw(30) << "<path>"                    << "Change le dossier où les rendus seront créés" << std::endl;
    std::cout << std::left << "-- " << std::setw(10) << "create"   << std::setw(30) << ""                          << "Créer le rendu" << std::endl;

    return Result::CONTINUE;
}

std::string Help::getCommand() const
{
    return COMMAND_HELP;
}

} // namespace MKTG::Command
