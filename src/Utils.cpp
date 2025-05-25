
#include "Utils.hpp"
#include <ctime>
#include <sstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#if defined(_WIN32)
#include <Windows.h>
#endif

namespace Utils
{

std::string getTimeFormat(std::string format)
{
    std::time_t now = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now), format.c_str());
    return oss.str();
}

std::string stringToUpper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](uint8_t c) {
        return std::toupper(c);
    });
    return str;
}

std::string getCompleteName(std::string name, json &tags)
{
    name = stringToUpper(name);
    for (auto &[key, value] : tags.items()) {
        auto vec = value.get<std::vector<std::string>>();
        for (auto &player : vec) {
            if (name == player) {
                name = key + " | " + name;
                return name;
            }
        }
    }
    return name;
}

std::string getFullPath(std::string path)
{
    return std::filesystem::current_path().string() + "\\" + std::string(path);
}

void createProcess(std::string path)
{
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;

    if (CreateProcessA(
        path.c_str(),           // Application name
        nullptr,                // Command line args
        nullptr,                // Process handle not inheritable
        nullptr,                // Thread handle not inheritable
        false,                  // Don't inherit handles
        CREATE_NEW_CONSOLE,     // New console window
        nullptr,                // Use parent's environment
        nullptr,                // Use parent's current directory
        &si,                    // Pointer to STARTUPINFO
        &pi)                    // Pointer to PROCESS_INFORMATION
    ) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        std::exit(EXIT_SUCCESS);
    } else {
        MessageBoxA(nullptr, "Can't find MarioKartTopGenerator_Updater.exe", "Error", MB_OK | MB_ICONERROR);
    }
}

}
