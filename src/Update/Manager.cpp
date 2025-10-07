
#include "Update/Update.hpp"
#include <curl/curl.h>
#include <filesystem>
#include <minizip/unzip.h>

namespace fs = std::filesystem;
namespace GNCApp::Update
{

Manager::Manager(std::string url)
{
    std::string response = this->_req.Get(url);
    this->_json = json::parse(response);

    this->_pathTemp = Utils::getTempDir() + '/' + GNCAPP_TEMP_DIR + '/';
    this->_pathSave = this->_pathTemp + GNCAPP_TEMP_DIR_SAVE;
    if (!fs::exists(this->_pathTemp)) {
        fs::create_directory(this->_pathTemp);
    }
    if (!fs::exists(this->_pathSave)) {
        fs::create_directory(this->_pathSave);
    }

    this->_pathCurr = fs::current_path().string();
    std::replace(this->_pathCurr.begin(), this->_pathCurr.end(), '\\', '/');
}

Manager::~Manager()
{
}

bool Manager::needsUpdate()
{
    return (this->_json[GITHUB_API_TAG] != GNCAPP_VERSION);
}

void Manager::downloadUpdate()
{
    std::cout << "-- Update found, downloading latest version..." << std::endl;

    for (json &release : this->_json[GITHUB_API_ASSETS]) {
        std::string name = release[GITHUB_API_ASSET_NAME].get<std::string>();
        std::string url = release[GITHUB_API_ASSET_URL].get<std::string>();
        if (name == UPDATE_API_TARGET) {
            this->_pathFile = this->_pathTemp + name;
            try {
                this->_req.Download(url, this->_pathFile);
            } catch (std::runtime_error &e) {
                std::cerr << "ERROR: " << e.what() << std::endl;
            }
            return;
        }
    }

    throw std::runtime_error(std::string("could not find target ") + UPDATE_API_TARGET);

}

void Manager::saveApp()
{
    std::cout << "-- Saving data from current version..." << std::endl;

    std::vector<std::string> toSave = {
        "/assets",
        "/data",
        "/template",
        "/themes"
    };

    for (const auto &entry : std::filesystem::directory_iterator(this->_pathCurr)) {
        if (entry.is_directory()) {
            std::string path = entry.path().string();
            std::replace(path.begin(), path.end(), '\\', '/');
            std::string name = path.substr(path.find_last_of('/'));

            if (std::find(toSave.begin(), toSave.end(), name) == toSave.end())
                continue;

            fs::copy(path, this->_pathSave + name, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            std::cout << "-- copied " << path << " into " << this->_pathSave << std::endl;
        }
    }
}

void Manager::clearApp()
{
    std::cout << "-- Clearing current application..." << std::endl;

    for (const auto &entry : std::filesystem::directory_iterator(this->_pathCurr)) {
        try {
            std::string path = entry.path().string();
            std::replace(path.begin(), path.end(), '\\', '/');

            if (entry.is_directory()) {
                fs::remove_all(path);
            } else {
                fs::remove(path);
            }
            std::cout << "-- Successfully deleted " << path << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cerr << "WARNING: " << e.what() << std::endl;
        }
    }
}

void Manager::installUpdate()
{
    std::cout << "-- Installing update..." << std::endl;

    std::string fileName = _pathFile.substr(_pathFile.find_last_of('/'));

    fs::copy(this->_pathFile, this->_pathCurr + fileName);
    fs::remove(this->_pathFile);
    std::cout << "-- moved " << this->_pathFile << " to " << this->_pathCurr + fileName << std::endl;
    this->_pathFile = this->_pathCurr + fileName;

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
        std::replace(path.begin(), path.end(), '\\', '/');
        std::string name = path.substr(path.find_last_of('/'));

        fs::copy(path, this->_pathCurr + name, fs::copy_options::recursive | fs::copy_options::update_existing);
        fs::remove_all(path);

        std::cout << "-- moved " << path << " to " << this->_pathCurr + name << std::endl;
    }
}


}
