//
//  body.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 7/4/2024.
//

#ifndef body_h
#define body_h

class Game
{
private:
    int attemptCount = 0;
    bool isOffline;
    bool success = true;
    Canvas canvas;
    Word word;
    
    void setDifficulty()
    {
        printf("0 | Easy \n1 | Medium \n2 | Hard \n3 | Paranoid \nSelect a difficulty: ");
        Difficulty difficulty;
        scanf("%d", &difficulty);
        canvas = Canvas(difficulty);
    }
    
    void setWordLength(bool offline, bool lastFailed = false)
    {
        if (lastFailed)
        {
            printf("Word length invalid. ");
        }
        printf("Speficy word length (2~15, enter 0 for random length): ");
        int len;
        scanf("%d", &len);
        if (!word.validateLength(len))
        {
            return setWordLength(offline, true);
        }
        word.length = len;
        bool res = word.init(!len, offline);
        if (!res)
        {
            setWordLength(offline, true);
        }
    }
    
    void start()
    {
        while (!word.finished)
        {
            attemptCount++;
            canvas.print();
            printGameStatus();
            word.visualise();
//            usleep(1000000);
            char letter = requestLetter();
            if (word.hasVisited(letter))
            {
                printf("You've tried this letter before!\n");
                attemptCount--;
                usleep(1000000);
                continue;
            }
            bool has = word.attempt(letter);
//            system("clear");
            if (has)
            {
                printf("Congratulations! You found letter \"%c\".\n", letter);
            }
            else
            {
                printf("Oopsies! Letter \"%c\" does not exist in this word.\n", letter);
                success = !canvas.strike();
                if (!success) break;
            }
            usleep(1000000);
        }
        usleep(1000000);
        printSummary();
        usleep(3000000);
    }
    
    void printGameStatus()
    {
        printf("Attempt #%d. You have %d strikes left.\n", attemptCount, canvas.attemptsLeft());
    }
    
    char requestLetter()
    {
        char ch;
        printf("Guess a letter: ");
        scanf(" %c", &ch);
        debug.print("Guessed letter: %c\n", ch);
        return ch;
    }
    
    void printSummary()
    {
        if (success)
        {
            printf("Success! You found the word \"%s\" in %d attempts. Well done.\n", word.str.c_str(), attemptCount);
        }
        else
        {
            canvas.print();
            printf("Sorry, but the man has died and you haven't found the word. \nThe word was \"%s\" - didn't expect that, did you?\n", word.str.c_str());
        }
    }
public:
    Game(Difficulty difficulty = Easy, int wordLength = NULL) : canvas(difficulty), word(wordLength)
    {
        
    }
    
    void init(bool offline, bool custom = false)
    {
        isOffline = offline;
        setDifficulty();
        if (custom)
        {
//            printf("We are still working on this...Check for updates at: https://github.com/mrmagic2020/The-Hangman-Game/releases/latest\n");
//            usleep(3000000);
            setWordLength(offline);
        }
        else
        {
//            setWordLength();
            bool res = word.generate(canvas.getDifficulty(), isOffline);
            if (!res)
            {
                printf("An error has occured. We couldn't find any words.\n");
                return;
            }
        }
        start();
    }
};

#endif /* body_h */
