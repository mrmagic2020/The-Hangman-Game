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
            if (cmd == "about")
            {
                printAbout();
            }
            else if (cmd == "new")
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
            else if (cmd == "update")
            {
                printUpdate();
            }
            else if (cmd == "settings")
            {
                
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
    
    void printAbout()
    {
        printf("The Hangman Game is an open-source command line (CLI) game. It fetches words from https://random-word-api.herokuapp.com/ - a big thanks to them. \nAuthor      | %s \nVersion     | %s \nLicense     | MIT \nGitHub Repo | https://github.com/mrmagic2020/The-Hangman-Game \nSupport me by starring my GitHub repository! \n", AUTHOR, VERSION);
    }
    
    void printCmds()
    {
        printf("List of commands: \nabout  | About the game \nnew    | Start a new game \ncustom | Customise a game \nupdate | View instructions on how to update the game \nquit   | Exit the game \n");
    }
    
    void printUpdate()
    {
        printf("Get the latest version of The Hangman Game at https://github.com/mrmagic2020/The-Hangman-Game/releases/latest\n");
    }
public:
    int process(int argc, const char * argv[])
    {
        CLI::App app{"The classic Hangman game implemented in the commandline."};
        bool game = false;
        bool offline = false;
        app.add_flag("-g,--game", game, "Start the game!");
        app.add_flag("-o,--offline", offline, "Toggle offline mode.");
        if (argc == 1)
        {
            printf("%s", app.help(argv[0], CLI::AppFormatMode::All).c_str());
            return 0;
        };
        CLI11_PARSE(app, argc, argv);
        if (offline)
        {
            bool res = wbase::init();
            if (!res)
            {
                printf("Cannot connect to server. Check you internet connection.\n");
                return 1;
            }
        }
        if (game)
        {
            welcome(offline);
        }
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
