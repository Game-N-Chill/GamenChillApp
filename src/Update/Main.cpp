
#include "Update/Update.hpp"
#include "Utils.hpp"
#include <filesystem>

namespace fs = std::filesystem;

int main(int ac, char **av)
{
    try {
        GNCApp::Update::Manager updater(UPDATE_API_URL);
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

    Utils::createProcess(std::filesystem::current_path().string() + '/' + GNCAPP_NAME + ".exe");
    return EXIT_SUCCESS;
}
