
#include "Update.hpp"
#include <curl/curl.h>
#include <filesystem>
#include <minizip/unzip.h>

namespace fs = std::filesystem;
namespace Generator::Update
{

Manager::Manager(std::string url)
{
    try {
        std::string response = this->_req.Get(url);
        this->_json = json::parse(response);
    } catch (std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return;
    }

    try {
        std::string path = std::getenv("LOCALAPPDATA");
        if (path.empty()) {
            throw std::runtime_error("can't find envrionment variable LOCALAPPDATA");
        }

        if (!fs::exists(path)) {
            throw std::runtime_error(path + " path doesn't exist");
        }

        this->_pathTemp = path + MKTG_APPDATA_DIR;
        this->_pathSave = this->_pathTemp + MKTG_APPDATA_SAVE_DIR;
        if (!fs::exists(this->_pathTemp)) {
            fs::create_directory(this->_pathTemp);
        }
        if (!fs::exists(this->_pathSave)) {
            fs::create_directory(this->_pathSave);
        }
    } catch (std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}

Manager::~Manager()
{
}

bool Manager::needsUpdate()
{
    return (this->_json[GITHUB_API_TAG] != MKTG_VERSION);
}

void Manager::downloadUpdate()
{
    std::cout << "-- Update found, downloading latest version..." << std::endl;

    for (json &release : this->_json[GITHUB_API_ASSETS]) {
        std::string name = release[GITHUB_API_ASSET_NAME].get<std::string>();
        std::string url = release[GITHUB_API_ASSET_URL].get<std::string>();
        if (name == MKTG_TARGET) {
            this->_pathFile = this->_pathTemp + name;
            this->_req.Download(url, this->_pathFile);
            return;
        }
    }

    throw std::runtime_error(std::string("could not find target ") + MKTG_TARGET);

}

void Manager::saveApp()
{
    std::cout << "-- Saving data from current version..." << std::endl;

    for (const auto &entry : std::filesystem::directory_iterator(fs::current_path())) {
        if (entry.is_directory()) {
            std::string path = entry.path().string();
            std::string name = path.substr(path.find_last_of('\\'));
            if (name == "\\Assets" || name == "\\Template")
                continue;

            fs::copy(path, this->_pathSave + name, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            std::cout << "-- copied " << path << " into " << this->_pathSave << std::endl;
        }
    }
}

void Manager::clearApp()
{
    std::cout << "-- Clearing current application..." << std::endl;

    for (const auto &entry : std::filesystem::directory_iterator(fs::current_path())) {
        try {
            if (entry.is_directory()) {
                fs::remove_all(entry.path());
            } else {
                fs::remove(entry.path());
            }
            std::cout << "-- Successfully deleted " << entry.path() << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cerr << "WARNING: " << e.what() << std::endl;
        }
    }
}

void Manager::installUpdate()
{
    std::cout << "-- Installing update..." << std::endl;

    std::string fileName = _pathFile.substr(_pathFile.find_last_of('\\'));

    fs::copy(this->_pathFile, fs::current_path().string() + fileName);
    fs::remove(this->_pathFile);
    std::cout << "-- moved " << this->_pathFile << " to " << fs::current_path().string() + fileName << std::endl;
    this->_pathFile = fs::current_path().string() + fileName;

    std::cout << "-- extracting " << this->_pathFile << std::endl;
    unzFile zip = unzOpen(this->_pathFile.c_str());
    unzGoToFirstFile(zip);

    do {
        // Get current file name
        char bufferName[256];
        unzGetCurrentFileInfo(zip, nullptr, bufferName, sizeof(bufferName), nullptr, 0, nullptr, 0);
        std::string extractName(bufferName);

        // Create directories of the extracted files if they don't exists
        size_t hasDir = extractName.find_last_of('/');
        if (hasDir != std::string::npos) {
            std::string dir = extractName.substr(0, hasDir);
            if (!fs::exists(dir)) {
                fs::create_directories(dir);
            }
        }

        // Opening current file
        unzOpenCurrentFile(zip);
        std::ofstream extractFile(extractName, std::ios::binary);

        // Reading in current zip file and write in normal file
        char buffer[4096];
        int bytes;
        while ((bytes = unzReadCurrentFile(zip, buffer, sizeof(buffer))) > 0) {
            extractFile.write(buffer, bytes);
        }

        // Closing all
        extractFile.close();
        unzCloseCurrentFile(zip);

        std::cout << "-- Successfully extracted " << extractName << std::endl;
    } while (unzGoToNextFile(zip) == UNZ_OK);

    unzClose(zip);
    fs::remove(this->_pathFile);
}

void Manager::installSave()
{
    std::cout << "-- Installing save..." << std::endl;

    for (const auto &entry : std::filesystem::directory_iterator(this->_pathSave)) {
        std::string path = entry.path().string();
        std::string name = path.substr(path.find_last_of('\\'));

        fs::copy(path, fs::current_path().string() + name, fs::copy_options::recursive);
        fs::remove_all(path);

        std::cout << "-- moved " << entry.path() << " to " << fs::current_path().string() + name << std::endl;
    }
}


}
