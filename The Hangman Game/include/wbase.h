//
//  wbase.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 10/4/2024.
//

#ifndef wbase_h
#define wbase_h

#include <fstream>
#include <cstdio>

#include "json.hpp"
#include "db.h"

namespace wbase {

vector<string> tmp;
vector<vector<string>> words(20);

bool init()
{
    string res;
    if (!filesystem::exists(db::homeDir + db::wbasePath))
    {
        debug.print("wbasePath=%s\n", db::wbasePath.c_str());
        printf("Initializing offline word base...\n");
        res = cget::httpGet(cget::fetchAllUrl);
        if (res == "")
        {
            printf("Cannot connect to server. Check your internet connection.\n");
            return false;
        }
        filesystem::create_directory(db::homeDir + db::dir); // creates a new directory, as ofstream cannot do so
        ofstream wb("./" + db::wbasePath); // creates a file in the user's home directory
        wb << res; // writes in the data
        wb.close();
//        filesystem::rename(db::homeDir + "/wbase.txt", db::homeDir + db::wbasePath); // move the file to the deisgnated resource path
        printf("Done.\n");
    }
    ifstream wb;
    wb.open("./" + db::wbasePath);
    if (!wb.is_open())
    {
        printf("Error: failed to open offline word base.\n");
        return false;
    }
    json data = json::parse(wb);
    tmp = data.get<vector<string>>();
    for (string &w : tmp)
    {
        words[w.size()].emplace_back(w);
    }
    vector<string>().swap(tmp); // free up memory
    return true;
}

string fetch(int length)
{
    if (words[length].empty()) return "";
    return words[length][rand() % words[length].size()];
}

void dlete()
{
    string path = "./" + db::wbasePath;
    int res = remove(path.c_str());
    if (res == 0)
    {
        printf("File deleted successfully.\n");
    }
    else
    {
        printf("An error occured deleting the file.\n");
    }
}

void reset()
{
    dlete();
    init();
}

} // namespace wbase

#endif /* wbase_h */
