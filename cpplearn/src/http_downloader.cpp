#include "http_downloader.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>

namespace cpplearn {
    using namespace std;

    http_downloader::http_downloader() {
        this->curl = curl_easy_init();
    }

    http_downloader::~http_downloader() {
        curl_easy_cleanup(this->curl);
    }

    auto http_downloader::write_data(void* ptr, size_t size, size_t nmemb, void* strm) -> size_t {
        string data((const char*)ptr, (size_t)size*nmemb);
        *((stringstream*)strm) << data << endl;
        return size * nmemb;
    }

    auto http_downloader::download(const string& url) -> string {
        curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(this->curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(this->curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(this->curl, CURLOPT_ACCEPT_ENCODING, "delete");

        stringstream out;

        curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, this->write_data);
        curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &out);

        CURLcode res = curl_easy_perform(this->curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }

        return out.str();
    }
};
