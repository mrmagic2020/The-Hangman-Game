//
//  main.cpp
//  The Hangman Game
//
//  Created by Arnold Zhou on 6/4/2024.
//

#include <iostream>
#include <vector>
#include <cstdarg>
#include <cstdlib>
#include <unistd.h>
#include <curl/curl.h>

#include "include/CLI11.hpp"

#include "include/cget.h"
#include "include/canvas.h"
#include "include/debug.h"
#include "include/word.h"
#include "include/wbase.h"
#include "include/game.h"
#include "include/update.h"
//#include "include/config.h"

#define AUTHOR "mrmagic2020"
#define VERSION "v1.1.0"

using namespace std;

Debug debug(false);

class Body
{
private:
    void welcome(bool offline)
    {
        printf("Welcome to The Hangman Game!\n");
        printCmds();
        char ccmd[101];
        string cmd = ccmd;
        while (cmd != "quit")
        {
            scanf("%s", ccmd);
            debug.print("Input cmd=\"%s\"\n", ccmd);
            cmd = ccmd;
            if (cmd == "new")
            {
                Game game;
                game.init(offline);
                printCmds();
            }
            else if (cmd == "custom")
            {
                Game game;
                game.init(offline, true);
                printCmds();
            }
            else if (cmd == "help")
            {
                printCmds();
            }
            else if (cmd == "quit")
            {
                return;
            }
            else
            {
                printf("Command unrecognised.\n");
            }
        }
    }
    
    static void printAbout(int n)
    {
        printf("The Hangman Game is an open-source command line (CLI) game. It fetches words from https://random-word-api.herokuapp.com/ - a big thanks to them. \nAuthor      | %s \nVersion     | %s \nLicense     | MIT \nGitHub Repo | https://github.com/mrmagic2020/The-Hangman-Game \nSupport me by starring my GitHub repository! \n", AUTHOR, VERSION);
    }
    
    static void printCmds()
    {
        printf("new    | Start a new game \ncustom | Customise a game \nquit   | Exit the game \n");
    }
    
    static void printUpdate(int n)
    {
        printf("Get the latest version of The Hangman Game at https://github.com/mrmagic2020/The-Hangman-Game/releases/latest\n");
    }
    
    static void printVersion(int n)
    {
        printf("The Hangman Game Version %s\n", VERSION);
    }
public:
    int process(int argc, const char * argv[])
    {
        CLI::App app{"The classic Hangman game implemented in the commandline."};
        
        CLI::App* gameCmd = app.add_subcommand("game", "Start the game!");
        bool offline = false;
        gameCmd->add_flag("-o,--offline", offline, "Toggle offline mode.");
        gameCmd->callback([&]() {
            if (offline)
            {
                bool res = wbase::init();
                if (!res)
                {
                    return;
                }
                else
                {
                    printf("Starting offline mode...\n");
                }
            }
            welcome(offline);
        });
        
        CLI::App* wbaseCmd = app.add_subcommand("wbase", "Offline word base manipulation.");
        bool init;
        wbaseCmd->add_flag("-i,--init", init, "Initialize offline word base. Requires internet connection.");
        bool dlete;
        wbaseCmd->add_flag("-d,--delete", dlete, "Delete offline word base.");
        bool reset;
        wbaseCmd->add_flag("-r,--reset", reset, "Reset offline word base.");
        bool path;
        wbaseCmd->add_flag("-p,--path", path, "Show path to offline word base.");
        wbaseCmd->callback([&]() {
            if (init)
            {
                wbase::init();
            }
            else if (dlete)
            {
                wbase::dlete();
            }
            else if (reset)
            {
                wbase::reset();
            }
            else if (path)
            {
                printf("Path to offline word base: %s\n", (db::homeDir + db::wbasePath).c_str());
            }
            else
            {
                printf("%s", app.help().c_str());
            }
        });
        
        CLI::App* updateCmd = app.add_subcommand("update", "Update to the latest version.");
        updateCmd->callback([&]() {
            update::fetch();
            string latestv = update::getLatestVersion();
            printf("Latest release: %s\n", latestv.c_str());
            if (latestv == VERSION)
            {
                printf("The Hangman Game is up to date!\n");
//                return;
            }
            debug.print("Download URL: %s\n", update::getDownloadURL().c_str());
            update::downloadRelease();
        });
        
//        app.add_flag("-g,--game", game, "Start the game!");
//        app.add_flag("-o,--offline", offline, "Toggle offline mode. Use with -g/--game.");
        app.add_flag("--about", printAbout, "View game info.");
        app.add_flag("-v,--version", printVersion, "View current game version.");
        app.add_flag("-u,--update", printUpdate, "View update instructions.");
        if (argc == 1)
        {
            printf("%s", app.help(argv[0]).c_str());
            return 0;
        };
        CLI11_PARSE(app, argc, argv);
//        if (offline)
//        {
//            bool res = wbase::init();
//            if (!res)
//            {
//                printf("Cannot connect to server. Check you internet connection.\n");
//                return 1;
//            }
//        }
//        if (game)
//        {
//            welcome(offline);
//        }
        return 0;
    }
};

int main(int argc, const char * argv[]) {
    Body body;
    body.process(argc, argv);
    
//    Word word(0);
//    word.init();
//    debug.print("word=%s\n", word.str.c_str());
    
//    Canvas canvas(Easy);
//    canvas.setStage(10);
//    canvas.print();
    return 0;
}
