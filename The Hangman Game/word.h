//
//  word.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 7/4/2024.
//

#ifndef word_h
#define word_h

//#include "cget.h"

using namespace std;

class Word
{
private:
    int found = 0;
    bool hasHyphon = false;
    vector<int> status;
    
    int randLength(int min = 2, int max = 45)
    {
        return rand() % (max - min) + min;
    }
    
    string fetch(int len)
    {
        string res = httpGet(getUrl(len));
        if (res.size() < 4) // no word found
        {
            return "";
        }
        return parse(res);
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
    
    bool init(bool random, int min = 2, int max = 45)
    {
        printf("Generating word...\n");
        srand((unsigned int)time(0));
        if (random)
        {
            int cnt = 0;
            while (str == "")
            {
                if (cnt > (max - min) * (max - min)) return false;
                length = randLength(min, max);
                str = fetch(length);
            }
        }
        else
        {
            if (!length) return false;
            str = fetch(length);
            if (str == "") return false;
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
    
    bool generate(int difficulty)
    {
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
        return init(false);
    }
    
    bool attempt(char letter)
    {
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
};

#endif /* word_h */
