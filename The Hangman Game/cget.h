//
//  cget.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 7/4/2024.
//

#ifndef cget_h
#define cget_h

using namespace std;

const string url = "https://random-word.ryanrk.com/api/en/word/random/?length=";

string getUrl(int length)
{
    return  url + to_string(length);
}

string parse(string str)
{
    return str.substr(2, str.size() - 4);
}

// Callback function writes data to a ostream
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
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
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

#endif /* cget_h */
