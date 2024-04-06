//
//  main.cpp
//  The Hangman Game
//
//  Created by Arnold Zhou on 6/4/2024.
//

#include <iostream>
#include <cstdarg>

using namespace std;

class Debug
{
private:
    bool status = false;
public:
    void setStatus(bool s, bool notify = true)
    {
        status = s;
        if (!notify) return;
        if (status)
        {
            printf("Debug mode enabled.");
        }
        else
        {
            printf("Debug mode disabled.");
        }
    }
    
    void print(const char * content, ...)
    {
        if (!status) return;
        
        va_list args;
        va_start(args, content);
        vprintf(content, args);
        va_end(args);
    }
    
    void printArgs(int argc, const char * argv[])
    {
        if (!status) return;
        
        printf("argc=%d\n", argc);
        printf("argv=[");
        for (int i = 0; i < argc; i++)
        {
            printf("%s, ", argv[i]);
        }
        printf("]\n");
    }
};

Debug debug;

class Body
{
private:
    void welcome()
    {
        printf("Welcome to The Hangman Game! \nnew | Start a new game \nquit | Exit the game \nhelp | View command list \n");
        char ccmd[101];
        string cmd = ccmd;
        while (cmd != "quit")
        {
            scanf("%s", ccmd);
            debug.print("Input cmd=\"%s\"\n", ccmd);
            cmd = ccmd;
            if (cmd == "new")
            {
                
            }
            else if (cmd == "help")
            {
                printHelp();
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
    
    void printHelp()
    {
        
    }
};

class Game
{
private:
public:
    
};

Debug initDebug(bool status = true)
{
    Debug debug;
    debug.setStatus(status, false);
    return debug;
}

Body initBody()
{
    Body body;
    return body;
}

int main(int argc, const char * argv[]) {
    debug = initDebug(false);
    Body body = initBody();
    body.process(argc, argv);
    return 0;
}
