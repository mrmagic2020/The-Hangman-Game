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
    bool success = true;
    Canvas canvas;
    Word word;
    
    void setDifficulty()
    {
        printf("Select a difficulty: \n0 | Easy \n1 | Medium \n2 | Hard \n3 | Paranoid \n");
        Difficulty difficulty;
        scanf("%d", &difficulty);
        canvas = Canvas(difficulty);
    }
    
    void setWordLength(bool lastFailed = false)
    {
        if (lastFailed)
        {
            printf("Word length invalid. ");
        }
        printf("Speficy word length: ");
        int len;
        scanf("%d", &len);
        word.length = len;
        bool res = word.init(false);
        if (!res)
        {
            setWordLength(true);
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
            usleep(1000000);
            char letter = requestLetter();
            bool has = word.attempt(letter);
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
    
    void init(bool custom = false)
    {
        if (custom)
        {
            printf("We are still working on this...Check for updates at: https://github.com/mrmagic2020/The-Hangman-Game\n");
        }
        else
        {
            setDifficulty();
//            setWordLength();
            bool res = word.generate(canvas.getDifficulty());
            if (!res)
            {
                printf("An error has occured. We couldn't find any words.\n");
                return;
            }
            debug.print("%s\n", word.str.c_str());
            start();
        }
    }
};

#endif /* body_h */
