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

#include "cget.h"
#include "canvas.h"
#include "debug.h"
#include "word.h"
#include "game.h"

using namespace std;

Debug debug(false);

class Body
{
private:
    void welcome()
    {
        printf("Welcome to The Hangman Game! \nabout | About the game \nnew | Start a new game \ncustom | Customise a game \nquit | Exit the game \n");
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
                game.init();
            }
            else if (cmd == "custom")
            {
                Game game;
                game.init(true);
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
public:
    void process(int argc, const char * argv[])
    {
        if (argc == 1) return welcome();
    }
    
    void printAbout()
    {
        printf("The Hangman Game is an open-source command line (CLI) game. It fetches words from https://random-word.ryanrk.com/ - a big thanks for them. \nLicense     | MIT \nGitHub Repo | https://github.com/mrmagic2020/The-Hangman-Game \nSupport me by starring my GitHub repository! \n");
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
