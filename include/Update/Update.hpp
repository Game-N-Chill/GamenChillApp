
#pragma once

#include <iostream>
#include <exception>
#include <fstream>

#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define GNCAPP_NAME                   "GamenChillApp"
#define GNCAPP_VERSION                "v3.0.0"
#define GNCAPP_API_URL                "https://api.github.com/repos/Game-N-Chill/GamenChillApp/releases/latest"
#define GNCAPP_API_USERAGENT          "GNCApp"
#define GNCAPP_TARGET                 "GamenChillApp_WIN32.zip"
#define GNCAPP_APPDATA_DIR            "\\GamenChill\\"
#define GNCAPP_APPDATA_SAVE_DIR       "Save"

#define GITHUB_API_TAG              "tag_name"
#define GITHUB_API_ASSETS           "assets"
#define GITHUB_API_ASSET_NAME       "name"
#define GITHUB_API_ASSET_URL        "browser_download_url"

namespace GNCApp::Update
{

class Request
{
    public:
        typedef size_t (*Func)(void *, size_t, size_t, void *);

        static size_t WriteToString(void *content, size_t s, size_t n, void *output);
        static size_t WriteToFile(void *content, size_t s, size_t n, void *output);

        Request();
        ~Request();

        std::string Get(std::string url);
        void Download(std::string url, std::string path);

    private:
        CURL *_curl;

        void SetOpt(std::string url, Func func, void *data);
};

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
        Request _req;
        json _json;

        std::string _pathTemp;
        std::string _pathSave;
        std::string _pathFile;
};

}
