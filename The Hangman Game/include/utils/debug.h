//
//  debug.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 7/4/2024.
//

#ifndef debug_h
#define debug_h

class Debug
{
private:
    bool status = false;
public:
    Debug(bool status = true)
    {
        this->status = status;
    }
    
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
        vprintf(("[debug] " + (std::string)content).c_str(), args);
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

extern Debug debug;

#endif /* debug_h */
