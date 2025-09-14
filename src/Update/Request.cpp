
#include "Update/Update.hpp"

namespace Generator::Update
{

size_t Request::WriteToString(void *contents, size_t size, size_t nmemb, void *output)
{
    std::string *str = static_cast<std::string*>(output);
    size_t totalSize = size * nmemb;
    str->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

size_t Request::WriteToFile(void *contents, size_t size, size_t nmemb, void *output)
{
    std::ofstream *file = static_cast<std::ofstream *>(output);
    size_t totalSize = size * nmemb;
    file->write(static_cast<char *>(contents), totalSize);
    return totalSize;
}


Request::Request()
{
    this->_curl = curl_easy_init();
    if (!this->_curl) {
        std::cerr << "ERROR: failed to initialize curl" << std::endl;
        return;
    }
}

Request::~Request()
{
    curl_easy_cleanup(this->_curl);
}


void Request::SetOpt(std::string url, Func func, void *data)
{
    curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(this->_curl, CURLOPT_USERAGENT, MKTG_API_USERAGENT); // GitHub requires a User-Agent
    curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, func);
    curl_easy_setopt(this->_curl, CURLOPT_WRITEDATA, data);

    CURLcode result = curl_easy_perform(this->_curl);
    if (result != CURLE_OK) {
        throw std::runtime_error(std::string("curl failed to perform (") + curl_easy_strerror(result) + ")");
    }
}

std::string Request::Get(std::string url)
{
    std::string data;
    this->SetOpt(url, &Request::WriteToString, &data);
    return data;
}

void Request::Download(std::string url, std::string path)
{
    std::ofstream file(path, std::ios::binary);
    this->SetOpt(url, &Request::WriteToFile, &file);
    file.close();
}


} // namespace MKTG
