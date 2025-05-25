
#include "Update.hpp"
#include <filesystem>

namespace fs = std::filesystem;

int main(int ac, char **av)
{
    try {
        MKTG::Updater updater(MKTG_API_URL);

        std::cout << "-- Checking latest version..." << std::endl;
        if (!updater.needsUpdate()) {
            std::cout << "-- Actuel version matches latest, no need to update, leaving..." << std::endl;
            return EXIT_SUCCESS;
        }

        updater.downloadUpdate();
        updater.saveApp();
        updater.clearApp();
        updater.installUpdate();
        updater.installSave();
    } catch (const fs::filesystem_error &e) {
        std::cerr << "ERROR: filesystem: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
