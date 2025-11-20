
#include <GoGuLib.hpp>
#include "Update.hpp"

int main(int ac, char **av)
{
    #if defined(_WIN32)
    GGL::setTerminalColor();
    #endif

    GGL::Updater updater(GNCAPP_NAME, GNCAPP_VERSION, GNCAPP_TARGET);

    updater.save("assets");
    updater.save("data");
    updater.save("template");
    updater.save("themes");

    if (updater(GNCAPP_GITHUB_URL) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    GGL::createProcess(GGL::getFullPath("GamenChillApp_GUI.exe"));
    return EXIT_SUCCESS;
}
