
#pragma once

#include <iostream>
#include <exception>
#include <fstream>

#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Utils.hpp"

#define UPDATE_API_URL                  "https://api.github.com/repos/Game-N-Chill/GamenChillApp/releases/latest"
#define UPDATE_API_TARGET               "GamenChillApp_WIN32.zip"

#define GITHUB_API_TAG                  "tag_name"
#define GITHUB_API_ASSETS               "assets"
#define GITHUB_API_ASSET_NAME           "name"
#define GITHUB_API_ASSET_URL            "browser_download_url"

namespace GNCApp::Update
{

class Manager
{
    public:
        Manager(std::string url);
        ~Manager();

        bool needsUpdate();
        void downloadUpdate();
        void saveApp();
        void clearApp();
        void installUpdate();
        void installSave();

    private:
        Utils::Request _req;
        json _json;

        std::string _pathCurr;
        std::string _pathTemp;
        std::string _pathSave;
        std::string _pathFile;
};

}
