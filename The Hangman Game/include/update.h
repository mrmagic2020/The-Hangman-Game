//
//  update.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 12/4/2024.
//

#ifndef update_h
#define update_h

namespace update {
const string url = "https://api.github.com/repos/mrmagic2020/The-Hangman-Game/releases/latest";
json releaseInfo;

json fetch()
{
    string res = cget::httpGetWithHeader(url);
//    debug.print("%s\n", res.c_str());
    releaseInfo = json::parse(res);
    return releaseInfo;
}

string getLatestVersion()
{
    return releaseInfo["tag_name"];
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
        printf("Latest release downloaded to Downloads folder.");
    }
}
} // namespace update

#endif /* update_h */
