//
//  format.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 14/4/2024.
//

#ifndef format_h
#define format_h

using namespace std;

namespace format
{

const char * RESTORE = "\033[0m";
const char * BRIGHT = "\033[1m";
const char * UNDERLINE = "\033[4m";
const char * FLASH = "\033[5m";
const char * FOREGROUND_BLACK = "\033[30m";
const char * FOREGROUND_RED = "\033[31m";
const char * FOREGROUND_GREEN = "\033[32m";
const char * FOREGROUND_YELLOW = "\033[33m";
const char * FOREGROUND_BLUE = "\033[34m";
const char * FOREGROUND_PURPLE = "\033[35m";
const char * FOREGROUND_CYAN = "\033[36m";
const char * FOREGROUND_WHITE = "\033[37m";
const char * BACKGROUND_BLACK = "\033[40m";
const char * BACKGROUND_RED = "\033[41m";
const char * BACKEGROUND_GREEN = "\033[42m";
const char * BACKGROUND_YELLOW = "\033[43m";
const char * BACKGROUND_BLUE = "\033[44m";
const char * BACKGROUND_PURPLE = "\033[45m";
const char * BACKGROUND_CYAN = "\033[46m";
const char * BACKGROUND_WHITE = "\033[47m";

string error(const string str)
{
    return (string)FOREGROUND_RED + "[error] " + str + (string)RESTORE;
}

//string f(const string str, vector<Colour> colours)
//{
//    string prefix = "\033[";
//    for (int i = 0; i < colours.size() - 1; i++)
//    {
//        prefix += to_string(colours[i]);
//    }
//    prefix += to_string(colours[colours.size() - 1]);
//    prefix += 'm';
//    cout << prefix << endl;
//    return (prefix + str + "\033[0m");
//}

} // namespace format


#endif /* format_h */
