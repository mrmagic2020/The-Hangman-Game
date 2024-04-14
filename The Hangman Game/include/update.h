//
//  update.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 12/4/2024.
//

#ifndef update_h
#define update_h

namespace update {
vector<int> version;
const string url = "https://api.github.com/repos/mrmagic2020/The-Hangman-Game/releases/latest";
json releaseInfo = NULL;

vector<int> parseVersionStr(string v)
{
    vector<int> res;
    for (char &ch : v)
    {
        if (ch != 'v' && ch != '.')
        {
            res.emplace_back(ch);
        }
    }
    return res;
}

json fetch()
{
    string res = cget::httpGetWithHeader(url);
    if (res == "")
    {
        return NULL;
    }
//    debug.print("%s\n", res.c_str());
    releaseInfo = json::parse(res);
    return releaseInfo;
}

bool init(string v)
{
    version = parseVersionStr(v);
    fetch();
    if (releaseInfo == NULL)
    {
        cget::noConnectionMsg();
        return false;
    }
    return true;
}

string getLatestVersion()
{
    return releaseInfo["tag_name"];
}

bool hasNewerVersion()
{
    vector<int> latestv = parseVersionStr(getLatestVersion());
    for (int i = 0; i < 3; i++)
    {
        if (latestv[i] > version[i]) return true;
    }
    return false;
}

string getDownloadURL()
{
    return releaseInfo["assets"][0]["browser_download_url"];
}

void downloadRelease(bool dmg = true)
{
    if (dmg)
    {
        cget::downloadFile(getDownloadURL(), "./Downloads/The-Hangman-Game.dmg");
        printf("Latest release downloaded to Downloads folder.\n");
    }
}
} // namespace update

#endif /* update_h */
