//
//  word.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 7/4/2024.
//

#ifndef word_h
#define word_h

#include "wbase.h"

using namespace std;

class Word
{
private:
    static const int minl = 2;
    static const int maxl = 15;
    int found = 0;
    bool hasHyphon = false;
    vector<int> status;
    set<char> visited;
    
    int randLength(int min = minl, int max = maxl)
    {
        int ran = rand();
        int res = (rand() % (max - min)) + min;
        debug.print("rand()=%d, max=%d, min=%d, rand()mod(max-min)=%d, res=%d\n", ran, max, min, ran%(max-min), res);
        return res;
    }
    
    string fetch(int len)
    {
        string res = cget::httpGet(cget::getUrl(len));
        if (res.size() < 4) // no word found
        {
            return "";
        }
        return cget::parse(res);
    }
    
    bool check()
    {
        for (int i = 0; i < length; i++)
        {
            if (status[i] == 0) return false;
        }
        finished = true;
        return true;
    }
    
public:
    int length;
    bool finished = false;
    string str;
    
    Word() : length(0), str("") {}
    
    Word(int length) : length(length), str("") {}
    
    Word(int length, string str) : length(length), str(str) {}
    
    bool init(bool random, bool offline, int min = minl, int max = maxl)
    {
        printf("Generating word...\n");
        if (!offline)
        {
            if (random)
            {
                int cnt = 0;
                while (str == "")
                {
                    if (cnt > (max - min) * (max - min)) return false;
                    length = randLength(min, max);
                    str = fetch(length);
                    cnt++;
                }
            }
            else
            {
                if (!length) return false;
                str = fetch(length);
                if (str == "") return false;
            }
        }
        else
        {
            if (random)
            {
                int cnt = 0;
                while (str == "")
                {
                    if (cnt > (max - min) * (max - min)) return false;
                    length = randLength(min, max);
                    str = wbase::fetch(length);
                    cnt++;
                }
            }
            else
            {
                str = wbase::fetch(length);
                debug.print("Offline word: %s\n", str.c_str());
                if (str == "") return false;
            }
        }
        status.resize(length, 0);
        for (int i = 0; i < length; i++)
        {
            if (str[i] == '-')
            {
                hasHyphon = true;
                status[i] = 1; // exclude hyphons
            }
        }
        return true;
    }
    
    bool generate(int difficulty, bool offline)
    {
        srand((unsigned int)time(0));
        switch (difficulty) {
            case Easy:
                length = randLength(9, 15);
                break;
            case Medium:
                length = randLength(7, 11);
                break;
            case Hard:
                length = randLength(5, 9);
                break;
            case Paranoid:
                length = randLength(3, 6);
                break;
            default:
                length = randLength(9, 15);
                break;
        }
        debug.print("Random length: %d\n", length);
        return init(false, offline);
    }
    
    bool attempt(char letter)
    {
        visited.insert(letter);
        bool res = false;
        for (int i = 0; i < length; i++)
        {
            if (tolower(str[i]) == tolower(letter))
            {
                status[i] = 1;
                found++;
                res = true;
            }
        }
        check();
        return res;
    }
    
    string visualise(bool print = true)
    {
        string s = "";
        for (int i = 0; i < length; i++)
        {
            if (status[i]) s += str[i];
            else s += '_';
        }
        s += ("(" + to_string(found) + "/" + to_string(length - hasHyphon) + ")");
        s += "\n";
        if (print) printf("%s", s.c_str());
        return s;
    }
    
    bool validateLength(int len)
    {
        return (minl <= len && len <= maxl) || (len == 0);
    }
    
    bool hasVisited(char letter)
    {
        return visited.find(letter) != visited.end();
    }
};

#endif /* word_h */
