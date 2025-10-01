
#include "Utils.hpp"
#include <sstream>
#include <fstream>

namespace Utils
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
        throw std::runtime_error("ERROR: failed to initialize curl");
    }

    curl_easy_setopt(this->_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(this->_curl, CURLOPT_MAXREDIRS, 10L);
    curl_easy_setopt(this->_curl, CURLOPT_USERAGENT, GNCAPP_API_USERAGENT);
    curl_easy_setopt(this->_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(this->_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(this->_curl, CURLOPT_CONNECTTIMEOUT, 15L);
    curl_easy_setopt(this->_curl, CURLOPT_TIMEOUT, 0L);
}

Request::~Request()
{
    curl_easy_cleanup(this->_curl);
}


void Request::SetFetchOpt(std::string url, Func func, void *data)
{
    curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, func);
    curl_easy_setopt(this->_curl, CURLOPT_WRITEDATA, data);

    CURLcode responseCode = curl_easy_perform(this->_curl);
    if (responseCode != CURLE_OK) {
        throw std::runtime_error(std::string("curl failed to perform (") + curl_easy_strerror(responseCode) + ")");
    }
}

void Request::SetOpt(CURLoption key, std::string value)
{
    curl_easy_setopt(this->_curl, key, value.c_str());
}

void Request::SetHeader(std::vector<std::string> vec)
{
    struct curl_slist *headers = NULL;
    for (auto str : vec) {
        headers = curl_slist_append(headers, str.c_str());
    }
    curl_easy_setopt(this->_curl, CURLOPT_HTTPHEADER, headers);
}

std::string Request::Get(std::string url)
{
    std::string data;
    this->SetFetchOpt(url, &Request::WriteToString, &data);
    return data;
}

void Request::Download(std::string url, std::string path)
{
    std::ofstream file(path, std::ios::binary);
    this->SetFetchOpt(url, &Request::WriteToFile, &file);
    file.close();
}


} // namespace MKTG
