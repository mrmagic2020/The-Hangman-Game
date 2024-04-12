//
//  cget.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 7/4/2024.
//

#ifndef cget_h
#define cget_h

#include <iostream>
#include "json.hpp"
#include "debug.h"

using namespace std;
using json = nlohmann::json;

namespace cget {

const string url = "https://random-word-api.herokuapp.com/word?length=";
const string fetchAllUrl = "https://random-word-api.herokuapp.com/all";

string getUrl(int length)
{
    return  url + to_string(length);
}

string parse(string str)
{
    json j = json::parse(str);
    string res = j[0];
    debug.print("Parsed result: %s\n", res.c_str());
    return res;
//    return str.substr(2, str.size() - 4);
}

// Callback function writes data to a ostream
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

// Function to perform GET request
string httpGet(const string& url) {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // If you're using a site with SSL, you might want to disable peer verification
        // This is not recommended for production code
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return "";
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

string httpGetWithHeader(const string& url) {
    CURL *curl;
    CURLcode res;
    string readBuffer;
    struct curl_slist *headers = nullptr;

    curl = curl_easy_init();
    if(curl) {
        // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Create a list of headers
        headers = curl_slist_append(headers, "User-Agent: The-Hangman-Game");

        // Set the headers for the CURL request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the CURL request
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n';
            return "";
        }

        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return readBuffer;
    } else {
        cerr << "Failed to initialize CURL." << '\n';
        return "";
    }
}

void downloadFile(const std::string& url, const std::string& filename) {
    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename.c_str(), "wb");
        if (fp == nullptr) {
            std::cerr << "File could not be opened." << std::endl;
            curl_easy_cleanup(curl);
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); // Follow redirects

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        fclose(fp);
        curl_easy_cleanup(curl);
    }
}

} // namespace cget


#endif /* cget_h */
